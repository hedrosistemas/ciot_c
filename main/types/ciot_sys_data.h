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

typedef struct __attribute__((packed))
{
    uint32_t storage : 1;
    uint32_t system : 1;
    uint32_t uart : 1;
    uint32_t usb: 1;
    uint32_t ethernet : 1;
    uint32_t wifi : 1;
    uint32_t bluetooth : 1;
    uint32_t reserved : 25;
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
    uint8_t fw_ver[3];
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