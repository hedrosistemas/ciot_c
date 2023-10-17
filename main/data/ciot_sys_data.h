/**
 * @file ciot_sys_data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_SYS_DATA__H__
#define __CIOT_SYS_DATA__H__

#include <inttypes.h>
#include "ciot_config.h"

typedef enum __attribute__((packed))
{
    CIOT_SYS_REQ_UNKNONW,
    CIOT_SYS_REQ_RESTART,
} ciot_sys_req_id_t;

typedef enum __attribute__((packed))
{
    CIOT_SYS_FEATURE_FLAGS_NONE = 0,
    CIOT_SYS_FEATURE_FLAGS_SERIAL = 1 << 0,
    CIOT_SYS_FEATURE_FLAGS_HTTP_CLIENT = 1 << 1,
    CIOT_SYS_FEATURE_FLAGS_HTTP_SERVER = 1 << 2,
    CIOT_SYS_FEATURE_FLAGS_MQTT_CLIENT = 1 << 3,
    CIOT_SYS_FEATURE_FLAGS_MQTT_SERVER = 1 << 4,
} ciot_sys_feature_flags_t;

typedef struct __attribute__((packed))
{
    unsigned serial :1;
    unsigned http_client :1;
    unsigned http_server :1;
    unsigned mqtt_client :1;
    unsigned mqtt_server :1;
} ciot_sys_features_t;

int s  = sizeof(ciot_sys_features_t);

typedef struct __attribute__((packed))
{
    char hardware_name[16];
    uint8_t firmware_version[3];
    ciot_sys_features_t features;
} ciot_sys_info_t;

typedef struct __attribute__((packed))
{
    int rst_reason;
    int rst_count;
    uint32_t free_memory;
    uint32_t lifetime;
    ciot_sys_info_t info;
} ciot_sys_status_t;

typedef struct __attribute__((packed))
{

} ciot_sys_cfg_t;

typedef union ciot_sys_req_data
{

} ciot_sys_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_sys_req_id_t id;
    ciot_sys_req_data_u data;
} ciot_sys_req_t;

typedef union ciot_sys_data
{
    ciot_sys_cfg_t config;
    ciot_sys_status_t status;
    ciot_sys_req_t request;
} ciot_sys_data_u;

#endif  //!__CIOT_SYS_DATA__H__