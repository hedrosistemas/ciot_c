/**
 * @file ciot_tcp_data.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_TCP_DATA__H__
#define __CIOT_TCP_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "ciot_config.h"

typedef enum __attribute__((packed))
{
    CIOT_TCP_STATE_ERROR = -1,
    CIOT_TCP_STATE_STOPPED,
    CIOT_TCP_STATE_STARTED,
    CIOT_TCP_STATE_CONNECTING,
    CIOT_TCP_STATE_CONNECTED,
} ciot_tcp_state_t;

typedef enum __attribute__((packed))
{
    CIOT_TCP_DHCP_STATE_IDLE,
    CIOT_TCP_DHCP_STATE_STARTED,
    CIOT_TCP_DHCP_STATE_STOPPED,
} ciot_tcp_dhcp_state_t;

typedef enum __attribute__((packed))
{
    CIOT_TCP_DHCP_CFG_NO_CHANGE,
    CIOT_TCP_DHCP_CFG_CLIENT,
    CIOT_TCP_DHCP_CFG_SERVER,
    CIOT_TCP_DHCP_CFG_DISABLED,
} ciot_tcp_dhcp_cfg_t;

typedef enum __attribute__((packed))
{
    CIOT_TCP_REQ_UNKNOWN,
} ciot_tcp_req_type_t;

typedef struct __attribute__((packed))
{
    ciot_tcp_dhcp_cfg_t dhcp;
    uint8_t ip[4];
    uint8_t gateway[4];
    uint8_t mask[4];
    uint8_t dns[4];
} ciot_tcp_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_tcp_dhcp_state_t client;
    ciot_tcp_dhcp_state_t server;
} ciot_tcp_dhcp_status_t;

typedef struct __attribute__((packed))
{
    uint8_t mac[6];
    uint8_t ip[4];
} ciot_tcp_info_t;

typedef struct __attribute__((packed))
{
    ciot_tcp_state_t state;
    uint8_t conn_count;
    ciot_tcp_dhcp_status_t dhcp;
    ciot_tcp_info_t info;
} ciot_tcp_status_t;

typedef union ciot_tcp_req_data
{

} ciot_tcp_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_tcp_req_type_t type;
    ciot_tcp_req_data_u data;
} ciot_tcp_req_t;

typedef union ciot_tcp_data
{
    #if CIOT_CONFIG_FEATURE_WIFI || CIOT_CONFIG_FEATURE_ETHERNET
    ciot_tcp_cfg_t config;
    ciot_tcp_status_t status;
    ciot_tcp_req_t request;
    #endif
} ciot_tcp_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_TCP_DATA__H__