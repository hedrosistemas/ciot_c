/**
 * @file ciot_httpc_data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_HTTPC_DATA__H__
#define __CIOT_HTTPC_DATA__H__

#include <inttypes.h>

#include "ciot_config.h"
#include "ciot_common_types.h"

#define CIOT_HTTPC_URL_LEN 64
#define CIOT_HTTPC_METHOD_LEN 8
#define CIOT_HTTPC_BODY_LEN 256
#define CIOT_HTTPC_HEADER_LEN 48
#define CIOT_HTTPC_HEADER_VAL 48

typedef enum __attribute__((packed))
{
    CIOT_HTTPC_STATE_IDLE,
    CIOT_HTTPC_STATE_STARTED,
    CIOT_HTTPC_STATE_CONNECTING,
    CIOT_HTTPC_STATE_CONNECTED,
    CIOT_HTTPC_STATE_DATA_RECEIVED,
    CIOT_HTTPC_STATE_TIMEOUT,
    CIOT_HTTPC_STATE_ERROR,
} ciot_httpc_state_t;

typedef enum __attribute__((packed))
{
    CIOT_HTTPC_REQ_UNKNOWN,
    CIOT_HTTPC_REQ_SEND_DATA,
    CIOT_HTTPC_REQ_SET_HEADER,
} ciot_httpc_req_id_t;

typedef enum {
    CIOT_HTTPC_METHOD_GET = 0,
    CIOT_HTTPC_METHOD_POST,
    CIOT_HTTPC_METHOD_PUT,
    CIOT_HTTPC_METHOD_PATCH,
    CIOT_HTTPC_METHOD_DELETE,
    CIOT_HTTPC_METHOD_HEAD,
    CIOT_HTTPC_METHOD_NOTIFY,
    CIOT_HTTPC_METHOD_SUBSCRIBE,
    CIOT_HTTPC_METHOD_UNSUBSCRIBE,
    CIOT_HTTPC_METHOD_OPTIONS,
    CIOT_HTTPC_METHOD_COPY,
    CIOT_HTTPC_METHOD_MOVE,
    CIOT_HTTPC_METHOD_LOCK,
    CIOT_HTTPC_METHOD_UNLOCK,
    CIOT_HTTPC_METHOD_PROPFIND,
    CIOT_HTTPC_METHOD_PROPPATCH,
    CIOT_HTTPC_METHOD_MKCOL,
    CIOT_HTTPC_METHOD_MAX,
} ciot_httpc_method_t;

typedef enum __attribute__((packed))
{
    CIOT_HTTPC_TRANSPORT_UNKNOWN,
    CIOT_HTTPC_TRANSPORT_TCP,
    CIOT_HTTPC_TRANSPORT_SSL,
} ciot_httpc_transport_type_t;

typedef struct __attribute__((packed))
{
    char url[CIOT_HTTPC_URL_LEN];
    ciot_httpc_method_t method;
    ciot_httpc_transport_type_t transport;
    uint16_t timeout;
} ciot_httpc_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_httpc_state_t state;
} ciot_httpc_status_t;

typedef struct __attribute__((packed))
{
    ciot_httpc_cfg_t cfg;
    uint8_t body[CIOT_HTTPC_BODY_LEN];
    int content_length;
} ciot_httpc_req_send_t;

// typedef struct __attribute__((packed))
// {
//     char header[CIOT_HTTPC_HEADER_LEN];
//     char value[CIOT_HTTPC_HEADER_VAL];
// } ciot_httpc_req_set_header_t;

// typedef union ciot_httpc_req_data
// {
//     ciot_httpc_req_send_t send;
//     ciot_httpc_req_set_header_t set_header;
// } ciot_httpc_req_data_u;

typedef struct __attribute__((packed))
{
    // ciot_httpc_req_id_t id;
    // ciot_httpc_req_data_u data;
} ciot_httpc_req_t;

typedef struct ciot_httpc_event_data
{
    ciot_event_data_t body;
    char *url;
} ciot_httpc_event_data_t;

typedef union ciot_httpc_event
{
    ciot_httpc_event_data_t data;
} ciot_httpc_event_data_u;

typedef union ciot_httpc_data
{
    #if CIOT_CONFIG_FEATURE_HTTPC
    ciot_httpc_cfg_t config;
    ciot_httpc_status_t status;
    ciot_httpc_req_t request;
    ciot_httpc_event_data_u event;
    #endif
} ciot_httpc_data_u;

#endif  //!__CIOT_HTTPC_DATA__H__