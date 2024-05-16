/**
 * @file ciot_uart.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_UART__H__
#define __CIOT_UART__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_uart_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"
#include "ciot_s.h"

typedef struct ciot_uart *ciot_uart_t;

typedef enum ciot_uart_event_id
{
    CIOT_UART_EVENT_DATA = CIOT_IFACE_EVENT_CUSTOM,
} ciot_uart_event_id_t;

typedef struct ciot_uart_base
{
    ciot_iface_t iface;
    ciot_uart_cfg_t cfg;
    ciot_uart_status_t status;
    ciot_s_t s;
} ciot_uart_base_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_uart_status_t status;
} ciot_uart_status_msg_t;

ciot_uart_t ciot_uart_new(void *handle);
ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg);
ciot_err_t ciot_uart_stop(ciot_uart_t self);
ciot_err_t ciot_uart_process_req(ciot_uart_t self, ciot_uart_req_t *req);
ciot_err_t ciot_uart_send_data(ciot_uart_t self, uint8_t *data, int size);
ciot_err_t ciot_uart_send_bytes(ciot_iface_t *self, uint8_t *bytes, int size);
ciot_err_t ciot_uart_set_bridge_mode(ciot_uart_t self, bool mode);
ciot_err_t ciot_uart_task(ciot_uart_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_UART__H__