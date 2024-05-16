/**
 * @file ciot_types.h
 * @brief Defines types and structures for CIOT functionality.
 * @version 0.1
 * @date 2023-12-07
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_TYPES__H__
#define __CIOT_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT states.
 */
typedef enum __attribute__((packed))
{
    CIOT_STATE_ERROR = -1, /**< Error state */
    CIOT_STATE_IDLE, /**< Idle state */
    CIOT_STATE_BUSY, /**< Busy state */
} ciot_state_t;

/**
 * @brief Enumeration for CIOT request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_REQ_UNKNOWN, /**< Unknown request type */
    CIOT_REQ_SAVE_IFACE_CFG, /**< Save interface configuration request */
    CIOT_REQ_DELETE_IFACE_CFG, /**< Delete interface configuration request */
    CIOT_REQ_PROXY_MSG, /**< Proxy message request */
} ciot_req_type_t;

/**
 * @brief Structure for CIOT interface configuration.
 */
typedef struct __attribute__((packed))
{

} ciot_iface_cfg_t;

/**
 * @brief Structure for CIOT information.
 */
typedef struct __attribute__((packed))
{
    uint8_t version[3]; /**< Version information */
} ciot_info_t;

/**
 * @brief Structure for CIOT status.
 */
typedef struct __attribute__((packed))
{
    ciot_state_t state; /**< CIOT state */
    ciot_info_t info; /**< CIOT information */
} ciot_status_t;

/**
 * @brief Structure for CIOT save interface configuration request.
 */
typedef struct __attribute__((packed))
{
    uint8_t iface_id; /**< Interface ID */
} ciot_req_save_iface_cfg_t;

/**
 * @brief Structure for CIOT delete interface configuration request.
 */
typedef struct __attribute__((packed))
{
    uint8_t iface_id; /**< Interface ID */
} ciot_req_delete_iface_cfg_t;

/**
 * @brief Structure for CIOT request result.
 */
typedef struct __attribute__((packed))
{
    uint8_t iface_id; /**< Interface ID */
    uint32_t err; /**< Error code */
} ciot_req_result_t;

/**
 * @brief Structure for CIOT proxy message request.
 */
typedef struct __attribute__((packed))
{
    uint8_t iface; /**< Interface */
    uint16_t size; /**< Message size */
    uint8_t data[256]; /**< Message data */
} ciot_req_proxy_msg_t;

/**
 * @brief Union for CIOT request data.
 */
typedef union __attribute__((packed))
{
    ciot_req_save_iface_cfg_t save_iface_cfg; /**< Save interface configuration request data */
    ciot_req_delete_iface_cfg_t delete_iface_cfg; /**< Delete interface configuration request data */
    ciot_req_proxy_msg_t proxy_msg; /**< Proxy message request data */
    ciot_req_result_t result; /**< Request result data */
} ciot_req_data_u;

/**
 * @brief Structure for CIOT request.
 */
typedef struct __attribute__((packed))
{
    ciot_req_type_t type; /**< Request type */
    ciot_req_data_u data; /**< Request data */
} ciot_req_t;

/**
 * @brief Union for CIOT data.
 */
typedef union __attribute__((packed))
{
    ciot_iface_cfg_t config; /**< Configuration data */
    ciot_status_t status; /**< Status data */
    ciot_req_t request; /**< Request data */
} ciot_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_TYPES__H__
