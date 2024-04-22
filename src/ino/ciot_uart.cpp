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

#if CIOT_CONFIG_FEATURE_UART && defined(CIOT_TARGET_ARDUINO)

#include <string.h>

#include <HardwareSerial.h>

struct ciot_uart
{
    ciot_uart_base_t uart;
    HardwareSerial *serial;
};

#ifdef __cplusplus
extern "C" {
#endif

ciot_err_t ciot_uart_on_message(ciot_iface_t *iface, uint8_t *data, int size);
ciot_err_t ciot_uart_task_internal(ciot_iface_t *iface, ciot_s_t ciot_s);

#ifdef __cplusplus
}
#endif

static const char *TAG = "ciot_uart";

ciot_uart_t ciot_uart_new(void *handle)
{
    ciot_uart_t self = (ciot_uart_t)calloc(1, sizeof(struct ciot_uart));
    self->uart.iface.base.ptr = self;
    self->uart.iface.base.start = (ciot_iface_start_fn *)ciot_uart_start;
    self->uart.iface.base.stop = (ciot_iface_stop_fn *)ciot_uart_stop;
    self->uart.iface.base.process_req = (ciot_iface_process_req_fn *)ciot_uart_process_req;
    self->uart.iface.base.send_data = (ciot_iface_send_data_fn *)ciot_uart_send_data;
    self->uart.iface.base.cfg.ptr = &self->uart.cfg;
    self->uart.iface.base.cfg.size = sizeof(self->uart.cfg);
    self->uart.iface.base.status.ptr = &self->uart.status;
    self->uart.iface.base.status.size = sizeof(self->uart.status);
    self->uart.iface.info.type = CIOT_IFACE_TYPE_UART;
    self->serial = (HardwareSerial*)handle;

    ciot_s_cfg_t s_cfg = { 
        .send_bytes = ciot_uart_send_bytes,
        .on_message_cb = ciot_uart_on_message,
        .iface = &self->uart.iface
    };
    self->uart.s = ciot_s_new(&s_cfg);
    
    return self;
}

ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    self->uart.cfg = *cfg;
    ciot_s_set_bridge_mode(self->uart.s, self->uart.cfg.bridge_mode);
    self->serial->begin(cfg->baud_rate);
    return CIOT_OK;
}

ciot_err_t ciot_uart_stop(ciot_uart_t self)
{
    CIOT_NULL_CHECK(self);
    
    return CIOT_OK;
}

ciot_err_t ciot_uart_send_data(ciot_uart_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    return ciot_s_send(self->uart.s, data, size);
}

ciot_err_t ciot_uart_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size)
{
    ciot_uart_t self = (ciot_uart_t)iface;
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(bytes);
    self->serial->write(bytes, size);
    return CIOT_OK;
}

ciot_err_t ciot_uart_set_bridge_mode(ciot_uart_t self, bool mode)
{
    CIOT_NULL_CHECK(self);
    return ciot_s_set_bridge_mode(self->uart.s, mode);
}

ciot_err_t ciot_uart_task(ciot_uart_t self)
{
    if(self->serial->available() > 0) {
        uint8_t byte = self->serial->read();
        ciot_err_t err = ciot_s_process_byte(self->uart.s, byte);
        if(err != CIOT_OK) {
            CIOT_LOGE(TAG, "Process byte error: %d", err);
        }
    }
    return ciot_uart_task_internal(&self->uart.iface, self->uart.s);
}

#endif
