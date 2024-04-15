/**
 * @file ciot_ble_types.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_BLE_TYPES__H__
#define __CIOT_BLE_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

typedef enum __attribute__((packed))
{
    CIOT_BLE_STATE_IDLE,
    CIOT_BLE_STATE_STARTED,
} ciot_ble_state_t;

typedef enum __attribute__((packed))
{
    CIOT_BLE_REQ_UNKNOWN,
    CIOT_BLE_REQ_SET_MAC,
} ciot_ble_req_type_t;

typedef struct __attribute__((packed))
{
    uint8_t mac[6];
} ciot_ble_cfg_t;

typedef struct __attribute__((packed))
{
    uint8_t hw_mac[6];
    uint8_t sw_mac[6];
} ciot_ble_info_t;

typedef struct __attribute__((packed))
{
    ciot_ble_state_t state;
    int err_code;
    ciot_ble_info_t info;
} ciot_ble_status_t;

typedef union __attribute__((packed))
{
    uint8_t set_mac[6];
} ciot_ble_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_ble_req_type_t type;
    ciot_ble_req_data_u data;
} ciot_ble_req_t;

typedef union __attribute__((packed))
{
    ciot_ble_cfg_t config;
    ciot_ble_status_t status;
    ciot_ble_req_t request;
} ciot_ble_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_BLE_TYPES__H__