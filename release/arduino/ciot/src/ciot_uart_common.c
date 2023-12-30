/**
 * @file ciot_uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_uart.h"

#if (CIOT_CONFIG_FEATURE_UART)

#include <string.h>

ciot_err_t ciot_uart_process_req(ciot_uart_t self, ciot_uart_req_t *req)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(req);
    switch (req->id)
    {
        case CIOT_UART_REQ_UNKNOWN:
            return CIOT_ERR_INVALID_ID;
        case CIOT_UART_REQ_SEND_DATA:
            return ciot_uart_send_data(self, req->data.send_data.data, req->data.send_data.size);
        case CIOT_UART_REQ_SEND_BYTES:
            return ciot_uart_send_bytes((ciot_iface_t*)self, req->data.send_data.data, req->data.send_data.size);
        case CIOT_UART_REQ_ENABLE_BRIDGE_MODE:
            return ciot_uart_set_bridge_mode(self, true);
    }
    return CIOT_ERR_INVALID_ID;
}

ciot_err_t ciot_uart_on_message(ciot_iface_t *iface, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(iface);
    CIOT_NULL_CHECK(data);
    CIOT_NULL_CHECK(iface->event_handler);
    ciot_uart_base_t *self = (ciot_uart_base_t*)iface;
    ciot_iface_event_t ciot_evt = { 0 };
    
    ciot_evt.id = self->cfg.bridge_mode ? CIOT_IFACE_EVENT_DATA : CIOT_IFACE_EVENT_REQUEST;
    ciot_evt.data = (ciot_iface_event_data_u*)data;
    ciot_evt.size = size;
    return iface->event_handler(iface, &ciot_evt, iface->event_args);
}

#endif
