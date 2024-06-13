/**
 * @file ciot_ble_scn.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_BLE_SCN__H__
#define __CIOT_BLE_SCN__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/ble_scn.pb-c.h"

typedef struct ciot_ble_scn *ciot_ble_scn_t;
typedef Ciot__BleScnCfg ciot_ble_scn_cfg_t;
typedef Ciot__BleScnReq ciot_ble_scn_req_t;
typedef Ciot__BleScnStatus ciot_ble_scn_status_t;
typedef Ciot__BleScnReq ciot_ble_scn_req_t;
typedef Ciot__BleScnData ciot_ble_scn_data_t;

typedef struct ciot_ble_scn_base
{
    ciot_iface_t iface;
    ciot_ble_scn_cfg_t cfg;
    ciot_ble_scn_status_t status;
    ciot_ble_scn_req_t req;
    ciot_msg_data_t msg;
    ciot_ble_scn_data_t data;
} ciot_ble_scn_base_t;

ciot_ble_scn_t ciot_ble_scn_new(void *handle);
ciot_err_t ciot_ble_scn_init(ciot_ble_scn_t self);
ciot_err_t ciot_ble_scn_start(ciot_ble_scn_t self, ciot_ble_scn_cfg_t *cfg);
ciot_err_t ciot_ble_scn_stop(ciot_ble_scn_t self);
ciot_err_t ciot_ble_scn_process_req(ciot_ble_scn_t self, ciot_ble_scn_req_t *req);
ciot_err_t ciot_ble_scn_get_cfg(ciot_ble_scn_t self, ciot_ble_scn_cfg_t *cfg);
ciot_err_t ciot_ble_scn_get_status(ciot_ble_scn_t self, ciot_ble_scn_status_t *status);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_BLE_SCN__H__
