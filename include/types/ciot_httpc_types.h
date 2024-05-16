/**
 * @file ciot_httpc_types.h
 * @ingroup software_types
 * @brief Defines data types and structures for CIOT HTTP client.
 * @version 0.1
 * @date 2023-10-11
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_HTTPC_DATA__H__
#define __CIOT_HTTPC_DATA__H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <inttypes.h>

#include "ciot_common_types.h"

/** Maximum length of URL */
#define CIOT_HTTPC_URL_LEN 64
/** Maximum length of HTTP method */
#define CIOT_HTTPC_METHOD_LEN 8
/** Maximum length of HTTP request body */
#define CIOT_HTTPC_BODY_LEN 256
/** Maximum length of HTTP header */
#define CIOT_HTTPC_HEADER_LEN 48
/** Maximum length of HTTP header value */
#define CIOT_HTTPC_HEADER_VAL 48

/**
 * @brief Enumeration for CIOT HTTP client states.
 */
typedef enum __attribute__((packed))
{
    CIOT_HTTPC_STATE_ERROR = -1, /**< Error state */
    CIOT_HTTPC_STATE_IDLE, /**< Idle state */
    CIOT_HTTPC_STATE_STARTED, /**< Started state */
    CIOT_HTTPC_STATE_CONNECTING, /**< Connecting state */
    CIOT_HTTPC_STATE_CONNECTED, /**< Connected state */
    CIOT_HTTPC_STATE_DATA_RECEIVED, /**< Data received state */
    CIOT_HTTPC_STATE_TIMEOUT, /**< Timeout state */
} ciot_httpc_state_t;

/**
 * @brief Enumeration for CIOT HTTP client request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_HTTPC_REQ_UNKNOWN, /**< Unknown request type */
    CIOT_HTTPC_REQ_SEND_DATA, /**< Send data request type */
    CIOT_HTTPC_REQ_SET_HEADER, /**< Set header request type */
} ciot_httpc_req_type_t;

/**
 * @brief Enumeration for HTTP methods.
 */
typedef enum __attribute__((packed))
{
    CIOT_HTTPC_METHOD_GET = 0, /**< GET method */
    CIOT_HTTPC_METHOD_POST, /**< POST method */
    CIOT_HTTPC_METHOD_PUT, /**< PUT method */
    CIOT_HTTPC_METHOD_PATCH, /**< PATCH method */
    CIOT_HTTPC_METHOD_DELETE, /**< DELETE method */
    CIOT_HTTPC_METHOD_HEAD, /**< HEAD method */
    CIOT_HTTPC_METHOD_NOTIFY, /**< NOTIFY method */
    CIOT_HTTPC_METHOD_SUBSCRIBE, /**< SUBSCRIBE method */
    CIOT_HTTPC_METHOD_UNSUBSCRIBE, /**< UNSUBSCRIBE method */
    CIOT_HTTPC_METHOD_OPTIONS, /**< OPTIONS method */
    CIOT_HTTPC_METHOD_COPY, /**< COPY method */
    CIOT_HTTPC_METHOD_MOVE, /**< MOVE method */
    CIOT_HTTPC_METHOD_LOCK, /**< LOCK method */
    CIOT_HTTPC_METHOD_UNLOCK, /**< UNLOCK method */
    CIOT_HTTPC_METHOD_PROPFIND, /**< PROPFIND method */
    CIOT_HTTPC_METHOD_PROPPATCH, /**< PROPPATCH method */
    CIOT_HTTPC_METHOD_MKCOL, /**< MKCOL method */
    CIOT_HTTPC_METHOD_MAX, /**< Max method */
} ciot_httpc_method_t;

/**
 * @brief Enumeration for HTTP client transport types.
 */
typedef enum __attribute__((packed))
{
    CIOT_HTTPC_TRANSPORT_UNKNOWN, /**< Unknown transport type */
    CIOT_HTTPC_TRANSPORT_TCP, /**< TCP transport type */
    CIOT_HTTPC_TRANSPORT_SSL, /**< SSL transport type */
} ciot_httpc_transport_type_t;

/**
 * @brief Structure for CIOT HTTP client configuration.
 */
typedef struct __attribute__((packed))
{
    char url[CIOT_HTTPC_URL_LEN]; /**< URL */
    ciot_httpc_method_t method; /**< HTTP method */
    ciot_httpc_transport_type_t transport; /**< Transport type */
    uint16_t timeout; /**< Timeout */
} ciot_httpc_cfg_t;

/**
 * @brief Structure for CIOT HTTP client status.
 */
typedef struct __attribute__((packed))
{
    ciot_httpc_state_t state; /**< State */
    int error; /**< Error */
} ciot_httpc_status_t;

/**
 * @brief Structure for CIOT HTTP client send data request.
 */
typedef struct __attribute__((packed))
{
    ciot_httpc_cfg_t cfg; /**< Configuration */
    uint8_t body[CIOT_HTTPC_BODY_LEN]; /**< Body */
    int content_length; /**< Content length */
} ciot_httpc_req_send_t;

/**
 * @brief Structure for CIOT HTTP client set header request.
 */
typedef struct __attribute__((packed))
{
    char header[CIOT_HTTPC_HEADER_LEN]; /**< Header */
    char value[CIOT_HTTPC_HEADER_VAL]; /**< Value */
} ciot_httpc_req_set_header_t;

/**
 * @brief Union for CIOT HTTP client request data.
 */
typedef union ciot_httpc_req_data
{
    ciot_httpc_req_send_t send; /**< Send data request */
    ciot_httpc_req_set_header_t set_header; /**< Set header request */
} ciot_httpc_req_data_u;

/**
 * @brief Structure for CIOT HTTP client request.
 */
typedef struct __attribute__((packed))
{
    ciot_httpc_req_type_t type; /**< Request type */
    ciot_httpc_req_data_u data; /**< Request data */
} ciot_httpc_req_t;

/**
 * @brief Structure for CIOT HTTP client event data.
 */
typedef struct ciot_httpc_event_data
{
    ciot_event_data_t body; /**< Event body */
    char *url; /**< URL */
} ciot_httpc_event_data_t;

/**
 * @brief Union for CIOT HTTP client event.
 */
typedef union ciot_httpc_event
{
    ciot_httpc_event_data_t data; /**< Event data */
} ciot_httpc_event_u;

/**
 * @brief Union for CIOT HTTP client data.
 */
typedef union __attribute__((packed))
{
    ciot_httpc_cfg_t config; /**< Configuration */
    ciot_httpc_status_t status; /**< Status */
    ciot_httpc_req_t request; /**< Request */
    ciot_httpc_event_u event; /**< Event */
} ciot_httpc_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_HTTPC_DATA__H__
