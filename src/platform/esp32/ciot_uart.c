/**
 * @file ciot_uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_uart.h"

#if CIOT_CONFIG_FEATURE_UART && defined(CIOT_TARGET_ESP)

#include <string.h>

#include "esp_log.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "ciot_s.h"

struct ciot_uart
{
    ciot_iface_t iface;
    ciot_uart_cfg_t cfg;
    ciot_uart_status_t status;
    ciot_s_t s;
    QueueHandle_t queue;
    TaskHandle_t task;
    uart_event_t event;
};

static ciot_err_t ciot_uart_on_message(ciot_iface_t *iface, uint8_t *data, int size);
static void ciot_uart_event_handler(void *args);

static const char *TAG = "ciot_uart";

ciot_uart_t ciot_uart_new(void *handle)
{
    ciot_uart_t self = calloc(1, sizeof(struct ciot_uart));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_uart_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_uart_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_uart_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_uart_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_UART;

    ciot_s_cfg_t s_cfg = { 
        .on_message_cb = ciot_uart_on_message,
        .send_bytes = ciot_uart_send_bytes,
        .iface = &self->iface
    };
    self->s = ciot_s_new(&s_cfg);

    return self;
}

ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    self->cfg = *cfg;
    int num = self->cfg.num;
    const uart_config_t uart_cfg = {
        .flow_ctrl = self->cfg.flow_control,
        .parity = self->cfg.parity,
        .baud_rate = self->cfg.baud_rate,
        .source_clk = UART_SCLK_DEFAULT,
    };
    ESP_ERROR_CHECK(uart_param_config(num, &uart_cfg));
    ESP_ERROR_CHECK(uart_set_pin(num, self->cfg.tx_pin, self->cfg.rx_pin, self->cfg.rts_pin, self->cfg.cts_pin));
    ESP_ERROR_CHECK(uart_driver_install(num, CIOT_CONFIG_UART_RX_BUF_SIZE, CIOT_CONFIG_UART_TX_BUF_SIZE, CIOT_CONFIG_UART_QUEUE_SIZE, &self->queue, 0));
    xTaskCreatePinnedToCore(ciot_uart_event_handler, "ciot_uart_task", CIOT_CONFIG_UART_TASK_SIZE, self, CIOT_CONFIG_UART_TASK_PRIO, &self->task, CIOT_CONFIG_UART_TASK_CORE);
    return CIOT_OK;
}

ciot_err_t ciot_uart_stop(ciot_uart_t self)
{
    CIOT_NULL_CHECK(self);
    uart_driver_delete(self->cfg.num);
    vTaskDelete(self->task);
    return CIOT_OK;
}

ciot_err_t ciot_uart_process_req(ciot_uart_t self, ciot_uart_req_t *req)
{
    CIOT_NULL_CHECK(self);
    switch (req->id)
    {
    case CIOT_UART_REQ_SEND_DATA:
        uart_write_bytes(self->cfg.num, req->data.send_data.data, req->data.send_data.size);
        return CIOT_OK;
    case CIOT_UART_REQ_ENABLE_BRIDGE_MODE:
        return ciot_s_set_bridge_mode(self->s, true);  
    case CIOT_UART_REQ_UNKNOWN:
        return CIOT_ERR_INVALID_ID;
    }
    return CIOT_ERR_INVALID_ID;
}

ciot_err_t ciot_uart_send_data(ciot_uart_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    return ciot_s_send(self->s, data, size);
}

ciot_err_t ciot_uart_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size)
{
    ciot_uart_t self = (ciot_uart_t)iface;
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(bytes);
    uart_write_bytes(self->cfg.num, bytes, size);
    return CIOT_OK;
}

ciot_err_t ciot_uart_task(ciot_uart_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

static ciot_err_t ciot_uart_on_message(ciot_iface_t *iface, uint8_t *data, int size)
{
    ciot_uart_t self = (ciot_uart_t)iface;
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    CIOT_NULL_CHECK(self->iface.event_handler);
    ciot_iface_event_t event = { 0 };
    event.id = CIOT_IFACE_EVENT_DATA;
    memcpy(&event.msg, data, size);
    event.size = size;
    return self->iface.event_handler(&self->iface, &event, self->iface.event_args);
}

static void ciot_uart_event_handler(void *args)
{
    ciot_uart_t self = (ciot_uart_t)args;
    ciot_iface_event_t event = { 0 };

    event.msg.type = CIOT_MSG_TYPE_EVENT;
    event.msg.iface = self->iface.info;

    while (true)
    {
        if(xQueueReceive(self->queue, (void*)&self->event, portMAX_DELAY))
        {
            switch (self->event.type)
            {
            case UART_DATA:
                while (self->event.size)
                {
                    uint8_t byte;
                    uart_read_bytes(self->cfg.num, &byte, 1, portMAX_DELAY);
                    self->event.size--;              
                    ciot_err_t err = ciot_s_process_byte(self->s, byte);
                    if(err != CIOT_OK) {
                        ESP_LOGE(TAG, "Process byte error: %d", err);
                    }
                }
                return;
            case UART_FIFO_OVF:
                ESP_LOGE(TAG, "hw fifo overflow");
                event.msg.data.uart.status.error = CIOT_UART_ERR_FIFO_OVERFLOW;
                uart_flush_input(self->cfg.num);
                xQueueReset(self->queue);
                break;
            case UART_BUFFER_FULL:
                ESP_LOGE(TAG, "ring buffer full: %d", self->event.size);
                event.msg.data.uart.status.error = CIOT_UART_ERR_BUFFER_FULL;
                uart_flush_input(self->cfg.num);
                xQueueReset(self->queue);
                break;
            case UART_BREAK:
                ESP_LOGE(TAG, "self rx break");
                event.msg.data.uart.status.error = CIOT_UART_ERR_BREAK;
                break;
            case UART_FRAME_ERR:
                ESP_LOGE(TAG, "self frame error");
                event.msg.data.uart.status.error = CIOT_UART_ERR_FRAME;
                break;
            default:
                ESP_LOGW(TAG, "unhandled self event: %d", self->event.type);
                event.msg.data.uart.status.error = CIOT_UART_ERR_UNKNOWN_EVENT;
                break;
            }

            if(self->iface.event_handler)
            {
                event.id = self->event.type != UART_DATA ? CIOT_IFACE_EVENT_ERROR : CIOT_IFACE_EVENT_DATA;
                self->iface.event_handler(&self->iface, &event, self->iface.event_args);
            }
        }
    }
}

#endif
