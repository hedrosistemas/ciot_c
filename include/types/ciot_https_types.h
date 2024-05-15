/**
 * @file ciot_https_types.h
 * @ingroup software_types
 * @brief Defines data types and structures for CIOT HTTP server.
 * @version 0.1
 * @date 2023-10-10
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_HTTPS_DATA__H__
#define __CIOT_HTTPS_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "ciot_common_types.h"

/** Maximum length of HTTPS address */
#define CIOT_HTTPS_ADDRESS_LEN 64
/** Maximum length of HTTPS route */
#define CIOT_HTTPS_ROUTE_LEN 32
/** Maximum length of HTTPS method */
#define CIOT_HTTPS_METHOD_LEN 8

/**
 * @brief Enumeration for CIOT HTTP server states.
 */
typedef enum __attribute__((packed))
{
    CIOT_HTTPS_STATE_STOPPED, /**< Stopped state */
    CIOT_HTTPS_STATE_STARTED, /**< Started state */
    CIOT_HTTPS_STATE_ERROR, /**< Error state */
} ciot_https_state_t;

/**
 * @brief Enumeration for CIOT HTTP server request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_HTTPS_REQ_UNKNOWN, /**< Unknown request type */
} ciot_https_req_type_t;

/**
 * @brief Structure for CIOT HTTP server configuration.
 */
typedef struct __attribute__((packed))
{
    char address[CIOT_HTTPS_ADDRESS_LEN]; /**< Address */
    char route[CIOT_HTTPS_ROUTE_LEN]; /**< Route */
    int port; /**< Port */
} ciot_https_cfg_t;

/**
 * @brief Structure for CIOT HTTP server status.
 */
typedef struct __attribute__((packed))
{
    ciot_https_state_t state; /**< State */
    int error; /**< Error */
} ciot_https_status_t;

/**
 * @brief Union for CIOT HTTP server request data.
 */
typedef union __attribute__((packed))
{

} ciot_https_req_data_u;

/**
 * @brief Structure for CIOT HTTP server request.
 */
typedef struct __attribute__((packed))
{
    ciot_https_req_type_t type; /**< Request type */
} ciot_https_req_t;

/**
 * @brief Structure for CIOT HTTP server event data.
 */
typedef struct ciot_https_event_data
{
    ciot_event_data_t body; /**< Event body */
    ciot_event_data_t url; /**< URL */
    ciot_event_data_t method; /**< Method */
} ciot_https_event_data_t;

/**
 * @brief Union for CIOT HTTP server event.
 */
typedef struct ciot_https_event
{
    ciot_https_event_data_t data; /**< Event data */
} ciot_https_event_u;

/**
 * @brief Union for CIOT HTTP server data.
 */
typedef union __attribute__((packed))
{
    ciot_https_cfg_t config; /**< Configuration */
    ciot_https_status_t status; /**< Status */
    ciot_https_req_t request; /**< Request */
    ciot_https_event_u event; /**< Event */
} ciot_https_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_HTTPS_DATA__H__
