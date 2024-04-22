/**
 * @file ciot_https_data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_HTTPS_DATA__H__
#define __CIOT_HTTPS_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "ciot_common_types.h"

#define CIOT_HTTPS_ADDRESS_LEN 64
#define CIOT_HTTPS_ROUTE_LEN 32
#define CIOT_HTTPS_METHOD_LEN 8

typedef enum __attribute__((packed))
{
    CIOT_HTTPS_STATE_STOPPED,
    CIOT_HTTPS_STATE_STARTED,
    CIOT_HTTPS_STATE_ERROR,
} ciot_https_state_t;

typedef enum __attribute__((packed))
{
    CIOT_HTTPS_REQ_UNKNOWN,
} ciot_https_req_type_t;

typedef struct __attribute__((packed))
{
    char address[CIOT_HTTPS_ADDRESS_LEN];
    char route[CIOT_HTTPS_ROUTE_LEN];
    int port;
} ciot_https_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_https_state_t state;
    int error;
} ciot_https_status_t;

typedef union __attribute__((packed))
{

} ciot_https_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_https_req_type_t type;
} ciot_https_req_t;

typedef struct ciot_https_event_data
{
    ciot_event_data_t body;
    ciot_event_data_t url;
    ciot_event_data_t method;
} ciot_https_event_data_t;

typedef struct ciot_https_event
{
    ciot_https_event_data_t data;
} ciot_https_event_u;

typedef union __attribute__((packed))
{
    ciot_https_cfg_t config;
    ciot_https_status_t status;
    ciot_https_req_t request;
    ciot_https_event_u event;
} ciot_https_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_HTTPS_DATA__H__