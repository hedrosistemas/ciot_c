/**
 * @file ciot_uart.h
 * @ingroup hardware_interfaces
 * @brief Header file for CIOT UART module.
 * @version 0.1
 * @date 2023-10-17
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_UART__H__
#define __CIOT_UART__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_uart_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"
#include "ciot_s.h"

/**
 * @brief Default configuration values for CIOT UART module.
 */
#ifndef CIOT_CONFIG_UART_RX_BUF_SIZE
#define CIOT_CONFIG_UART_RX_BUF_SIZE 256
#endif
#ifndef CIOT_CONFIG_UART_TX_BUF_SIZE
#define CIOT_CONFIG_UART_TX_BUF_SIZE 256
#endif
#ifndef CIOT_CONFIG_UART_QUEUE_SIZE
#define CIOT_CONFIG_UART_QUEUE_SIZE 20
#endif
#ifndef CIOT_CONFIG_UART_TASK_SIZE
#define CIOT_CONFIG_UART_TASK_SIZE 4096
#endif
#ifndef CIOT_CONFIG_UART_TASK_PRIO
#define CIOT_CONFIG_UART_TASK_PRIO (tskIDLE_PRIORITY + 1)
#endif
#ifndef CIOT_CONFIG_UART_TASK_CORE
#define CIOT_CONFIG_UART_TASK_CORE 1
#endif

/**
 * @brief Handle type for CIOT UART module.
 */
typedef struct ciot_uart *ciot_uart_t;

/**
 * @brief Event ID enumeration for CIOT UART module.
 */
typedef enum ciot_uart_event_id
{
    CIOT_UART_EVENT_DATA = CIOT_IFACE_EVENT_CUSTOM, /*!< Custom event for UART data */
} ciot_uart_event_id_t;

/**
 * @brief Base structure for CIOT UART module.
 */
typedef struct ciot_uart_base
{
    ciot_iface_t iface;         /*!< CIOT interface instance */
    ciot_uart_cfg_t cfg;        /*!< Configuration for UART module */
    ciot_uart_status_t status;  /*!< Status information for UART module */
    ciot_s_t s;                 /*!< CIOT S module instance */
} ciot_uart_base_t;

/**
 * @brief Status message structure for CIOT UART module.
 */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;   /*!< Message header */
    ciot_uart_status_t status;  /*!< Status information */
} ciot_uart_status_msg_t;

/**
 * @brief Create a new instance of CIOT UART module.
 *
 * @param handle Unused parameter (can be NULL).
 * @return Pointer to the new CIOT UART instance.
 */
ciot_uart_t ciot_uart_new(void *handle);

/**
 * @brief Start the CIOT UART module with the given configuration.
 *
 * @param self Pointer to the CIOT UART instance.
 * @param cfg Configuration for the UART module.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg);

/**
 * @brief Stop the CIOT UART module.
 *
 * @param self Pointer to the CIOT UART instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_uart_stop(ciot_uart_t self);

/**
 * @brief Process a request in the CIOT UART module.
 *
 * @param self Pointer to the CIOT UART instance.
 * @param req Pointer to the UART request structure.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_uart_process_req(ciot_uart_t self, ciot_uart_req_t *req);

/**
 * @brief Send data through the CIOT UART module.
 *
 * @param self Pointer to the CIOT UART instance.
 * @param data Pointer to the data buffer.
 * @param size Size of the data buffer.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_uart_send_data(ciot_uart_t self, uint8_t *data, int size);

/**
 * @brief Send bytes through the CIOT UART interface.
 *
 * @param self Pointer to the CIOT interface instance.
 * @param bytes Pointer to the byte buffer to send.
 * @param size Size of the byte buffer.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_uart_send_bytes(ciot_iface_t *self, uint8_t *bytes, int size);

/**
 * @brief Set bridge mode for the CIOT UART module.
 *
 * @param self Pointer to the CIOT UART instance.
 * @param mode Bridge mode flag (true for enabled, false for disabled).
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_uart_set_bridge_mode(ciot_uart_t self, bool mode);

/**
 * @brief Task function for the CIOT UART module.
 *
 * @param self Pointer to the CIOT UART instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_uart_task(ciot_uart_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_UART__H__
