/**
 * @file ciot_uart.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_UART__H__
#define __CIOT_UART__H__

#include "ciot_uart_data.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_uart *ciot_uart_t;

ciot_uart_t ciot_uart_new(void *handle);
ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg);
ciot_err_t ciot_uart_stop(ciot_uart_t self);
ciot_err_t ciot_uart_process_req(ciot_uart_t self, ciot_uart_req_t *req);
ciot_err_t ciot_uart_send_data(ciot_uart_t self, uint8_t *data, int size);
ciot_err_t ciot_uart_send_bytes(void *user_ctx, uint8_t *bytes, int size);
ciot_err_t ciot_uart_task(ciot_uart_t self);

#endif  //!__CIOT_UART__H__