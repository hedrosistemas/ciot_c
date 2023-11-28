/**
 * @file ciot_ble_scn_types.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_BLE_SCN_TYPES__H__
#define __CIOT_BLE_SCN_TYPES__H__

#include <inttypes.h>

#include "ciot_config.h"

typedef enum __attribute__((packed))
{
    CIOT_BLE_SCN_STATE_IDLE,
    CIOT_BLE_SCN_STATE_PASSIVE,
    CIOT_BLE_SCN_STATE_ACTIVE,
} ciot_ble_scn_state_t;

typedef enum __attribute__((packed))
{
    CIOT_BLE_SCN_REQ_UNKNOWN,
} ciot_ble_scn_req_id_t;

typedef struct __attribute__((packed))
{
    uint16_t interval;
    uint16_t window;
    uint16_t timeout;
    bool active;
    bool brigde_mode;
} ciot_ble_scn_cfg_t;

typedef struct __attribute__((packed))
{
    int8_t rssi;
    uint8_t mac[6];
} ciot_ble_scn_adv_report_t;

typedef struct __attribute__((packed))
{
    ciot_ble_scn_state_t state;
    ciot_ble_scn_adv_report_t adv_report;
    int err_code;
} ciot_ble_scn_status_t;

typedef union __attribute__((packed))
{

} ciot_ble_scn_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_ble_scn_req_id_t id;
    ciot_ble_scn_req_data_u data;
} ciot_ble_scn_req_t;

typedef union __attribute__((packed))
{
    // #if CIOT_CONFIG_FEATURE_ble
    ciot_ble_scn_cfg_t config;
    ciot_ble_scn_status_t status;
    ciot_ble_scn_req_t request;
    // #endif
} ciot_ble_scn_data_u;

#endif  //!__CIOT_BLE_SCN_TYPES__H__