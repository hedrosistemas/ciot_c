/**
 * @file ciot_dfu_types.h
 * @ingroup software_types
 * @brief Defines data types and structures for CIOT DFU (Device Firmware Update).
 * @version 0.1
 * @date 2023-10-10
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_DFU_TYPES__H__
#define __CIOT_DFU_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT DFU states.
 */
typedef enum __attribute__((packed))
{
    CIOT_DFU_STATE_ERROR = -1, /**< Error state */
    CIOT_DFU_STATE_IDLE, /**< Idle state */
    CIOT_DFU_STATE_IN_PROGRESS, /**< In progress state */
    CIOT_DFU_STATE_COMPLETED, /**< Completed state */
} ciot_dfu_state_t;

/**
 * @brief Enumeration for CIOT DFU request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_DFU_REQ_UNKNOWN, /**< Unknown request type */
    CIOT_DFU_REQ_SEND_FIRMWARE, /**< Send firmware request type */
} ciot_dfu_req_type_t;

/**
 * @brief Enumeration for CIOT DFU types.
 */
typedef enum __attribute__((packed))
{
    CIOT_DFU_TYPE_UNKNOWN, /**< Unknown DFU type */
    CIOT_DFU_TYPE_UART, /**< UART DFU type */
    CIOT_DFU_TYPE_USB, /**< USB DFU type */
    CIOT_DFU_TYPE_BLE, /**< BLE DFU type */
} ciot_dfu_type_t;

/**
 * @brief Structure for CIOT DFU configuration.
 */
typedef struct
{
    ciot_dfu_type_t type; /**< DFU type */
} ciot_dfu_cfg_t;

/**
 * @brief Structure for CIOT DFU status.
 */
typedef struct __attribute__((packed))
{
    ciot_dfu_state_t state; /**< State */
    int code; /**< Code */
    int error; /**< Error */
    uint32_t image_size; /**< Image size */
    uint32_t image_read; /**< Image read */
} ciot_dfu_status_t;

/**
 * @brief Union for CIOT DFU request data.
 */
typedef union __attribute__((packed))
{
    
} ciot_dfu_req_data_u;

/**
 * @brief Structure for CIOT DFU request.
 */
typedef struct __attribute__((packed))
{
    ciot_dfu_req_type_t type; /**< Request type */
    ciot_dfu_req_data_u data; /**< Request data */
} ciot_dfu_req_t;

/**
 * @brief Union for CIOT DFU data.
 */
typedef union __attribute__((packed))
{
    ciot_dfu_cfg_t config; /**< Configuration */
    ciot_dfu_status_t status; /**< Status */
    ciot_dfu_req_t request; /**< Request */
} ciot_dfu_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_DFU_TYPES__H__
