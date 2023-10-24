/**
 * @file ciot_ble_data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_BLE_DATA__H__
#define __CIOT_BLE_DATA__H__

#include <inttypes.h>

#include "ciot_config.h"

typedef enum __attribute__((packed))
{
    CIOT_BLE_STATE_IDLE,
} ciot_ble_state_t;

typedef enum __attribute__((packed))
{
    CIOT_BLE_REQ_UNKNOWN,
} ciot_ble_req_id_t;

typedef struct __attribute__((packed))
{

} ciot_ble_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_ble_state_t state;
} ciot_ble_status_t;

typedef union __attribute__((packed))
{

} ciot_ble_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_ble_req_id_t id;
    ciot_ble_req_data_u data;
} ciot_ble_req_t;

typedef union __attribute__((packed))
{
    #if CIOT_CONFIG_FEATURE_ble
    ciot_ble_cfg_t config;
    ciot_ble_status_t status;
    ciot_ble_req_t request;
    #endif
} ciot_ble_data_u;

#endif  //!__CIOT_BLE_DATA__H__