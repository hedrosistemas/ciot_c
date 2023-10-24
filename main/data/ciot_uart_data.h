/**
 * @file ciot_uart.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_UART__H__
#define __CIOT_UART__H__

#include <inttypes.h>

#include "ciot_config.h"

typedef enum __attribute__((packed))
{
    CIOT_UART_STATE_IDLE,
} ciot_uart_state_t;

typedef enum __attribute__((packed))
{
    CIOT_UART_REQ_UNKNOWN,
} ciot_uart_req_id_t;

typedef struct __attribute__((packed))
{

} ciot_uart_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_uart_state_t state;
} ciot_uart_status_t;

typedef union __attribute__((packed))
{

} ciot_uart_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_uart_req_id_t id;
    ciot_uart_req_data_u data;
} ciot_uart_req_t;

typedef union __attribute__((packed))
{
    #if CIOT_CONFIG_FEATURE_uart
    ciot_uart_cfg_t config;
    ciot_uart_status_t status;
    ciot_uart_req_t request;
    #endif
} ciot_uart_data_u;

#endif //!__CIOT_UART__H__