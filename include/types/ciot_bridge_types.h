/**
 * @file ciot_bridge_types.h
 * @ingroup software_types
 * @brief Defines data types and structures for CIOT bridge.
 * @version 0.1
 * @date 2023-11-13
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_BRIDGE_TYPES__H__
#define __CIOT_BRIDGE_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT bridge states.
 */
typedef enum __attribute__((packed))
{
    CIOT_BRIDGE_STATE_IDLE, /**< Idle state */
    CIOT_BRIDGE_STATE_STARTED, /**< Started state */
    CIOT_BRIDGE_STATE_ERROR, /**< Error state */
} ciot_bridge_state_t;

/**
 * @brief Enumeration for CIOT bridge request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_BRIDGE_REQ_UNKNOWN, /**< Unknown request type */
} ciot_bridge_req_type_t;

/**
 * @brief Structure for CIOT bridge configuration.
 */
typedef struct __attribute__((packed))
{
    uint8_t ifaces_id[2]; /**< Interface IDs */
} ciot_bridge_cfg_t;

/**
 * @brief Structure for CIOT bridge status.
 */
typedef struct __attribute__((packed))
{
    ciot_bridge_state_t state; /**< State */
} ciot_bridge_status_t;

/**
 * @brief Union for CIOT bridge request data.
 */
typedef union __attribute__((packed))
{

} ciot_bridge_req_data_u;

/**
 * @brief Structure for CIOT bridge request.
 */
typedef struct __attribute__((packed))
{
    ciot_bridge_req_type_t type; /**< Request type */
    ciot_bridge_req_data_u data; /**< Request data */
} ciot_bridge_req_t;

/**
 * @brief Union for CIOT bridge data.
 */
typedef union __attribute__((packed))
{
    ciot_bridge_cfg_t config; /**< Configuration */
    ciot_bridge_status_t status; /**< Status */
    ciot_bridge_req_t request; /**< Request */
} ciot_bridge_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_BRIDGE_TYPES__H__
