/**
 * @file ciot_wifi_data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_WIFI_DATA__H__
#define __CIOT_WIFI_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "ciot_config.h"
#include "ciot_tcp_types.h"

typedef enum __attribute__((packed))
{
    CIOT_WIFI_IF_STA,
    CIOT_WIFI_IF_AP,
} ciot_wifi_type_t;

typedef enum __attribute__((packed))
{
    CIOT_WIFI_SCAN_STATE_ERROR = -1,
    CIOT_WIFI_SCAN_STATE_IDLE,
    CIOT_WIFI_SCAN_STATE_SCANNING,
    CIOT_WIFI_SCAN_STATE_SCANNED,
} ciot_wifi_scan_state_t;

typedef enum __attribute__((packed))
{
    CIOT_WIFI_STATE_IDLE,
} ciot_wifi_state_t;

typedef enum __attribute__((packed))
{
    CIOT_WIFI_REQ_UNKNOWN,
    CIOT_WIFI_REQ_SCAN,
} ciot_wifi_req_type_t;

typedef struct __attribute__((packed))
{
    uint8_t bssid[6];
    char ssid[33];
    int8_t rssi;
    uint8_t authmode;
} ciot_wifi_ap_info_t;

typedef struct __attribute__((packed))
{
    char ssid[32];
    char password[64];
    ciot_tcp_cfg_t tcp;
    ciot_wifi_type_t type;
} ciot_wifi_cfg_t;

typedef struct __attribute__((packed))
{
    uint8_t disconnect_reason;
    ciot_wifi_ap_info_t info;
    ciot_tcp_status_t tcp;
} ciot_wifi_status_t;

typedef struct __attribute__((packed))
{
    uint8_t count;
    ciot_wifi_ap_info_t ap_list[8];
} ciot_wifi_scan_result_t;

typedef union __attribute__((packed))
{
    ciot_wifi_scan_result_t scan_result;
} ciot_wifi_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_wifi_req_type_t type;
    ciot_wifi_req_data_u data;
} ciot_wifi_req_t;

typedef union __attribute__((packed))
{
    #if CIOT_CONFIG_FEATURE_WIFI
    ciot_wifi_cfg_t config;
    ciot_wifi_status_t status;
    ciot_wifi_req_t request;
    #endif
} ciot_wifi_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_WIFI_DATA__H__