/**
 * @file ciot_sys_data.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_SYS_DATA__H__
#define __CIOT_SYS_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "ciot_config.h"

typedef enum __attribute__((packed))
{
    CIOT_SYS_REQ_UNKNONW,
    CIOT_SYS_REQ_RESTART,
} ciot_sys_req_type_t;

typedef struct __attribute__((packed))
{
    uint32_t storage : 1;
    uint32_t system : 1;
    uint32_t uart : 1;
    uint32_t usb: 1;
    uint32_t ethernet : 1;
    uint32_t wifi : 1;
    uint32_t ble_scn : 1;
    uint32_t reserved : 24;
} ciot_sys_hw_features_t;

typedef struct __attribute__((packed))
{
    uint32_t ntp : 1;
    uint32_t ota: 1;
    uint32_t http_client : 1;
    uint32_t http_server : 1;
    uint32_t mqtt_client : 1;
    uint32_t reserved : 27;
} ciot_sys_sw_features_t;

typedef struct __attribute__((packed))
{
    ciot_sys_hw_features_t hw;
    ciot_sys_sw_features_t sw;
} ciot_sys_features_t;

typedef struct __attribute__((packed))
{
    char hw_name[16];
    uint8_t app_ver[3];
    ciot_sys_features_t features;
} ciot_sys_info_t;

typedef struct __attribute__((packed))
{
    uint8_t rst_reason;
    uint16_t rst_count;
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
    ciot_sys_req_type_t id;
    ciot_sys_req_data_u data;
} ciot_sys_req_t;

typedef union ciot_sys_data
{
    #if CIOT_CONFIG_FEATURE_SYSTEM
    ciot_sys_cfg_t config;
    ciot_sys_status_t status;
    ciot_sys_req_t request;
    #endif
} ciot_sys_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_SYS_DATA__H__