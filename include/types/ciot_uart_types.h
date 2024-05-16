/**
 * @file ciot_uart_types.h
 * @ingroup hardware_types
 * @brief Defines data structures and types for CIOT UART functionality.
 * @version 0.1
 * @date 2023-10-10
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_UART_DATA__H__
#define __CIOT_UART_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdbool.h>

#include "ciot_common_types.h"

/**
 * @brief Enumeration for CIOT UART states.
 */
typedef enum __attribute__((packed))
{
    CIOT_UART_STATE_CLOSED, /**< UART closed state */
    CIOT_UART_STATE_STARTED, /**< UART started state */
    CIOT_UART_STATE_INTERNAL_ERROR, /**< Internal UART error state */
    CIOT_UART_STATE_CIOT_S_ERROR, /**< CIOT-specific UART error state */
} ciot_uart_state_t;

/**
 * @brief Enumeration for CIOT UART errors.
 */
typedef enum __attribute__((packed))
{
    CIOT_UART_ERR_NONE, /**< No error */
    CIOT_UART_ERR_BREAK, /**< Break error */
    CIOT_UART_ERR_BUFFER_FULL, /**< Buffer full error */
    CIOT_UART_ERR_FIFO_OVERFLOW, /**< FIFO overflow error */
    CIOT_UART_ERR_FRAME, /**< Frame error */
    CIOT_UART_ERR_PARITY, /**< Parity error */
    CIOT_UART_ERR_DATA_BREAK, /**< Data break error */
    CIOT_UART_ERR_UNKNOWN_EVENT, /**< Unknown event error */
    CIOT_UART_ERR_OPEN, /**< Open error */
} ciot_uart_error_t;

/**
 * @brief Enumeration for CIOT UART request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_UART_REQ_UNKNOWN, /**< Unknown request type */
    CIOT_UART_REQ_SEND_DATA, /**< Send data request */
    CIOT_UART_REQ_SEND_BYTES, /**< Send bytes request */
    CIOT_UART_REQ_ENABLE_BRIDGE_MODE, /**< Enable bridge mode request */
} ciot_uart_req_type_t;

/**
 * @brief Structure for CIOT UART configuration.
 */
typedef struct __attribute__((packed))
{
    uint32_t baud_rate; /**< Baud rate */
    uint8_t num; /**< UART number */
    int8_t rx_pin; /**< RX pin */
    int8_t tx_pin; /**< TX pin */
    int8_t rts_pin; /**< RTS pin */
    int8_t cts_pin; /**< CTS pin */
    uint16_t parity; /**< Parity */
    uint8_t flow_control : 1; /**< Flow control flag */
    uint8_t dtr : 1; /**< DTR flag */
    uint8_t bridge_mode : 1; /**< Bridge mode flag */
    uint8_t reserved : 5; /**< Reserved bits */
} ciot_uart_cfg_t;

/**
 * @brief Structure for CIOT UART status.
 */
typedef struct __attribute__((packed))
{
    ciot_uart_state_t state; /**< UART state */
    ciot_uart_error_t error; /**< UART error */
} ciot_uart_status_t;

/**
 * @brief Structure for CIOT UART send data request.
 */
typedef struct __attribute__((packed))
{
    uint8_t size; /**< Data size */
    uint8_t data[255]; /**< Data buffer */
} ciot_uart_req_send_data_t;

/**
 * @brief Union for CIOT UART request data.
 */
typedef union __attribute__((packed))
{
    ciot_uart_req_send_data_t send_data; /**< Send data request data */
} ciot_uart_req_data_u;

/**
 * @brief Structure for CIOT UART request.
 */
typedef struct __attribute__((packed))
{
    ciot_uart_req_type_t type; /**< Request type */
    ciot_uart_req_data_u data; /**< Request data */
} ciot_uart_req_t;

/**
 * @brief Union for CIOT UART event.
 */
typedef union ciot_uart_event
{
    ciot_event_data_t data; /**< Event data */
} ciot_uart_event_u;

/**
 * @brief Union for CIOT UART data.
 */
typedef union __attribute__((packed))
{
    ciot_uart_cfg_t config; /**< Configuration data */
    ciot_uart_status_t status; /**< Status data */
    ciot_uart_req_t request; /**< Request data */
    ciot_uart_event_u event; /**< Event data */
} ciot_uart_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_UART_DATA__H__
