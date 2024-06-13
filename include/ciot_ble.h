/**
 * @file ciot_ble.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_BLE__H__
#define __CIOT_BLE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/ble.pb-c.h"

typedef struct ciot_ble *ciot_ble_t;
typedef Ciot__BleCfg ciot_ble_cfg_t;
typedef Ciot__BleReq ciot_ble_req_t;
typedef Ciot__BleStatus ciot_ble_status_t;
typedef Ciot__BleInfo ciot_ble_info_t;
typedef Ciot__BleReq ciot_ble_req_t;
typedef Ciot__BleData ciot_ble_data_t;

typedef struct ciot_ble_base
{
    ciot_iface_t iface;
    ciot_ble_cfg_t cfg;
    ciot_ble_status_t status;
    ciot_ble_info_t info;
    ciot_ble_req_t req;
    ciot_msg_data_t msg;
    ciot_ble_data_t data;
} ciot_ble_base_t;

ciot_ble_t ciot_ble_new(void *handle);
ciot_err_t ciot_ble_init(ciot_ble_t self);
ciot_err_t ciot_ble_start(ciot_ble_t self, ciot_ble_cfg_t *cfg);
ciot_err_t ciot_ble_stop(ciot_ble_t self);
ciot_err_t ciot_ble_process_req(ciot_ble_t self, ciot_ble_req_t *req);
ciot_err_t ciot_ble_get_cfg(ciot_ble_t self, ciot_ble_cfg_t *cfg);
ciot_err_t ciot_ble_get_status(ciot_ble_t self, ciot_ble_status_t *status);
ciot_err_t ciot_ble_get_info(ciot_ble_t self, ciot_ble_info_t *info);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_BLE__H__
