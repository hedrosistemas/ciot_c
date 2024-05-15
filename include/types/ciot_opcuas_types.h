/**
 * @file ciot_opcuas_types.h
 * @ingroup software_types
 * @brief Defines data types and structures for CIOT OPC UA Server functionality.
 * @version 0.1
 * @date 2024-04-21
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2024
 */

#ifndef __CIOT_OPCUAS_TYPES__H__
#define __CIOT_OPCUAS_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT OPC UA Server state.
 */
typedef enum __attribute__((packed))
{
    CIOT_OPCUAS_STATE_ERROR = -1, /**< OPC UA Server state: error */
    CIOT_OPCUAS_STATE_IDLE, /**< OPC UA Server state: idle */
    CIOT_OPCUAS_STATE_RUNNING, /**< OPC UA Server state: running */
} ciot_opcuas_state_t;

/**
 * @brief Enumeration for CIOT OPC UA Server request type.
 */
typedef enum __attribute__((packed))
{
    CIOT_OPCUAS_REQ_UNKNOWN, /**< Unknown OPC UA Server request type */
    CIOT_OPCUAS_REQ_ADD_NODE, /**< Add node request */
    CIOT_OPCUAS_REQ_RUN, /**< Run request */
} ciot_opcuas_req_type_t;

/**
 * @brief Structure for CIOT OPC UA Server configuration.
 */
typedef struct __attribute__((packed))
{
    uint32_t port; /**< Port number */
} ciot_opcuas_cfg_t;

/**
 * @brief Structure for CIOT OPC UA Server status.
 */
typedef struct __attribute__((packed))
{
    ciot_opcuas_state_t state; /**< OPC UA Server state */
} ciot_opcuas_status_t;

/**
 * @brief Structure for CIOT OPC UA Server add node request.
 */
typedef struct __attribute__((packed))
{
    uint16_t type; /**< Node type */
    char localization[8]; /**< Localization */
    char display_name[32]; /**< Display name */
    char node_id[64]; /**< Node ID */
} ciot_opcuas_req_add_node_t;

/**
 * @brief Union for CIOT OPC UA Server request data.
 */
typedef union __attribute__((packed))
{
    ciot_opcuas_req_add_node_t add_node; /**< Add node request data */
} ciot_opcuas_req_data_u;

/**
 * @brief Structure for CIOT OPC UA Server request.
 */
typedef struct __attribute__((packed))
{
    ciot_opcuas_req_type_t type; /**< Request type */
    ciot_opcuas_req_data_u data; /**< Request data */
} ciot_opcuas_req_t;

/**
 * @brief Union for CIOT OPC UA Server data.
 */
typedef union __attribute__((packed))
{
    ciot_opcuas_cfg_t config; /**< OPC UA Server configuration */
    ciot_opcuas_status_t status; /**< OPC UA Server status */
    ciot_opcuas_req_t request; /**< OPC UA Server request */
} ciot_opcuas_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_OPCUAS_TYPES__H__
