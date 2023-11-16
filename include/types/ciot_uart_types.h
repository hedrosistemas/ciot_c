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

#ifndef __CIOT_UART_DATA__H__
#define __CIOT_UART_DATA__H__

#include <inttypes.h>
#include <stdbool.h>

#include "ciot_common_types.h"
#include "ciot_config.h"

typedef enum __attribute__((packed))
{
    CIOT_UART_STATE_CLOSED,
    CIOT_UART_STATE_STARTED,
    CIOT_UART_STATE_INTERNAL_ERROR,
    CIOT_UART_STATE_CIOT_S_ERROR,
} ciot_uart_state_t;

typedef enum __attribute__((packed))
{
    CIOT_UART_ERR_NONE,
    CIOT_UART_ERR_BREAK,
    CIOT_UART_ERR_BUFFER_FULL,
    CIOT_UART_ERR_FIFO_OVERFLOW,
    CIOT_UART_ERR_FRAME,
    CIOT_UART_ERR_PARITY,
    CIOT_UART_ERR_DATA_BREAK,
    CIOT_UART_ERR_UNKNOWN_EVENT,
} ciot_uart_error_t;

typedef enum __attribute__((packed))
{
    CIOT_UART_REQ_UNKNOWN,
    CIOT_UART_REQ_SEND_DATA,
    CIOT_UART_REQ_SEND_BYTES,
    CIOT_UART_REQ_ENABLE_BRIDGE_MODE,
} ciot_uart_req_id_t;

typedef struct __attribute__((packed))
{
    uint32_t baud_rate;
    uint32_t num;
    uint32_t rx_pin;
    uint32_t tx_pin;
    uint32_t rts_pin;
    uint32_t cts_pin;
    uint32_t flow_control;
    uint32_t parity;
    bool dtr;
    bool bridge_mode;
} ciot_uart_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_uart_state_t state;
    ciot_uart_error_t error;
} ciot_uart_status_t;

typedef struct __attribute__((packed))
{
    uint8_t data[64];
    uint8_t size;
} ciot_uart_req_send_data_t;

typedef union __attribute__((packed))
{
    ciot_uart_req_send_data_t send_data;
} ciot_uart_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_uart_req_id_t id;
    ciot_uart_req_data_u data;
} ciot_uart_req_t;

typedef union ciot_uart_event
{
    ciot_event_data_t data;
} ciot_uart_event_u;

typedef union __attribute__((packed))
{
    #if CIOT_CONFIG_FEATURE_UART
    ciot_uart_cfg_t config;
    ciot_uart_status_t status;
    ciot_uart_req_t request;
    ciot_uart_event_u event;
    #endif
} ciot_uart_data_u;

#endif //!__CIOT_UART_DATA__H__