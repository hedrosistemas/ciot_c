/**
 * @file ciot_uart.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_UART__H__
#define __CIOT_UART__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"
#include "ciot_decoder.h"
#include "ciot_config.h"

#include "ciot/proto/v1/uart.pb-c.h"

#ifndef CIOT_CONFIG_UART_TX_BUF_SIZE
#define CIOT_CONFIG_UART_TX_BUF_SIZE 256
#endif 

typedef struct ciot_uart *ciot_uart_t;
typedef Ciot__UartCfg ciot_uart_cfg_t;
typedef Ciot__UartReq ciot_uart_req_t;
typedef Ciot__UartStatus ciot_uart_status_t;
typedef Ciot__UartReq ciot_uart_req_t;
typedef Ciot__UartData ciot_uart_data_t;

typedef struct ciot_uart_base
{
    ciot_iface_t iface;
    ciot_uart_cfg_t cfg;
    ciot_uart_status_t status;
    ciot_uart_req_t req;
    ciot_msg_data_t msg;
    ciot_uart_data_t data;
    ciot_decoder_t decoder;
} ciot_uart_base_t;

ciot_uart_t ciot_uart_new(void *handle);
ciot_err_t ciot_uart_init(ciot_uart_t self);
ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg);
ciot_err_t ciot_uart_stop(ciot_uart_t self);
ciot_err_t ciot_uart_task(ciot_uart_t self);
ciot_err_t ciot_uart_process_req(ciot_uart_t self, ciot_uart_req_t *req);
ciot_err_t ciot_uart_get_cfg(ciot_uart_t self, ciot_uart_cfg_t *cfg);
ciot_err_t ciot_uart_get_status(ciot_uart_t self, ciot_uart_status_t *status);
ciot_err_t ciot_uart_send_bytes(ciot_uart_t self, uint8_t *bytes, int size);
ciot_err_t ciot_uart_set_decoder(ciot_uart_t self, ciot_decoder_t decoder);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_uart__H__
