/**
 * @file ciot_uart.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-31
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>

#include "sdk_common.h"
#include "nrf_drv_uart.h"
#include "app_util_platform.h"

#include "ciot_uart.h"
#include "ciot_s.h"

#define UART_PIN_DISCONNECTED 0xFFFFFFFF /**< Value indicating that no pin is connected to this UART register. */

struct ciot_uart
{
    ciot_iface_t iface;
    ciot_uart_cfg_t cfg;
    ciot_uart_status_t status;
    ciot_s_t s;
    nrf_drv_uart_t uart;
};

static void ciot_uart_event_handler(nrf_drv_uart_event_t *event, void *context);

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
        // .on_message_cb = ciot_uart_on_message,
        .handler = self};
    self->s = ciot_s_new(&s_cfg);
    return self;
}

ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg)
{
    self->cfg = *cfg;

    nrf_drv_uart_config_t config = NRF_DRV_UART_DEFAULT_CONFIG;
    config.baudrate = self->cfg.baud_rate;
    config.hwfc = self->cfg.flow_control;
    config.interrupt_priority = APP_IRQ_PRIORITY_LOWEST;
    config.parity = self->cfg.parity;
    config.pselcts = self->cfg.cts_pin;
    config.pselrts = self->cfg.rts_pin;
    config.pselrxd = self->cfg.rx_pin;
    config.pseltxd = self->cfg.tx_pin;
    config.p_context = self;

    if(self->cfg.num == 0)
    {
        nrf_drv_uart_t uart = NRF_DRV_UART_INSTANCE(0);
        self->uart = uart;
    }
    #if NRFX_UARTE1_ENABLED
    else if(self->cfg.num == 1)
    {
        nrf_drv_uart_t uart = NRF_DRV_UART_INSTANCE(1);
        self->uart = uart;
    }
    #endif  //NRFX_UARTE1_ENABLED
    else 
    {
        return CIOT_ERR_INVALID_ARG;
    }

    uint32_t err_code = nrf_drv_uart_init(&self->uart, &config, ciot_uart_event_handler);
    VERIFY_SUCCESS(err_code);

    if (self->cfg.rx_pin != UART_PIN_DISCONNECTED)
    {
        uint8_t rx_buffer[1];
        return nrf_drv_uart_rx(&self->uart, rx_buffer, 1);
    }
    else
    {
        return NRF_SUCCESS;
    }
}

ciot_err_t ciot_uart_stop(ciot_uart_t self)
{
    nrf_drv_uart_uninit(&self->uart);
    return NRF_SUCCESS;
}

ciot_err_t ciot_uart_process_req(ciot_uart_t self, ciot_uart_req_t *req)
{
    CIOT_NULL_CHECK(self);

    ret_code_t ret;

    switch (req->id)
    {
    case CIOT_UART_REQ_SEND_DATA:
        ret = nrf_drv_uart_tx(&self->uart, req->data.send_data.data, req->data.send_data.size);
        if (NRF_ERROR_BUSY == ret)
        {
            return CIOT_ERR_NO_MEMORY;
        }
        else if (ret != NRF_SUCCESS)
        {
            return CIOT_FAIL;
        }
        else
        {
            return CIOT_OK;
        }
        return CIOT_OK;
    case CIOT_UART_REQ_UNKNOWN:
        return CIOT_ERR_INVALID_ID;
    }
    return CIOT_ERR_INVALID_ID;
}

ciot_err_t ciot_s_write_bytes(ciot_s_t s, char *bytes, int size)
{
    ciot_uart_t self;
    ciot_s_get_handler(s, &self);
    ret_code_t ret = nrf_drv_uart_tx(&self->uart, (uint8_t *)bytes, size);
    if (NRF_ERROR_BUSY == ret)
    {
        return CIOT_ERR_NO_MEMORY;
    }
    else if (ret != NRF_SUCCESS)
    {
        return CIOT_FAIL;
    }
    else
    {
        return CIOT_OK;
    }
}

ciot_err_t ciot_uart_send_data(ciot_uart_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    return ciot_s_send(self->s, (char*)data, size);
}

static void ciot_uart_event_handler(nrf_drv_uart_event_t *event, void *context)
{
    ciot_uart_t self = (ciot_uart_t)context;
    ciot_iface_event_t ciot_evt = { 0 };

    ciot_evt.msg.type = CIOT_MSG_TYPE_EVENT;
    ciot_evt.msg.iface = self->iface.info;

    switch (event->type)
    {
        case NRF_DRV_UART_EVT_TX_DONE:
            ciot_evt.id = CIOT_IFACE_EVENT_CUSTOM;
            break;
        case NRF_DRV_UART_EVT_RX_DONE:
            while (event->data.rxtx.bytes)
            {
                uint8_t byte;
                uint32_t ret = nrf_drv_uart_rx(&self->uart, &byte, 1);
                if (NRF_ERROR_BUSY == ret)
                {
                    self->status.error = CIOT_ERR_NO_MEMORY;
                    self->status.state = CIOT_UART_STATE_INTERNAL_ERROR;
                    break;
                }
                else if (ret != NRF_SUCCESS)
                {
                    self->status.error = CIOT_FAIL;
                    self->status.state = CIOT_UART_STATE_INTERNAL_ERROR;
                    break;
                }
                ret = ciot_s_process_byte(self->s, byte);
                if(ret != CIOT_OK) {
                    self->status.error = ret;
                    self->status.state = CIOT_UART_STATE_CIOT_S_ERROR;
                }
                event->data.rxtx.bytes--;
                return;
            }
            
            break;
        case NRF_DRV_UART_EVT_ERROR:
            self->status.error = event->data.error.error_mask;
            self->status.state = CIOT_UART_STATE_INTERNAL_ERROR;
            ciot_evt.msg.data.uart.status = self->status;
            ciot_evt.id = CIOT_IFACE_EVENT_ERROR;
            break;
    default:
        break;
    }

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(self, &ciot_evt, self->iface.event_args);
    }
}
