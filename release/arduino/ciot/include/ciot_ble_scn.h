/**
 * @file ciot_ble_scn.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_BLE_SCN__H__
#define __CIOT_BLE_SCN__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_ble_scn_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_ble_scn *ciot_ble_scn_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_ble_scn_status_t status;
} ciot_ble_scn_status_msg_t;

ciot_ble_scn_t ciot_ble_scn_new(void *handle);
ciot_err_t ciot_ble_scn_start(ciot_ble_scn_t self, ciot_ble_scn_cfg_t *cfg);
ciot_err_t ciot_ble_scn_stop(ciot_ble_scn_t self);
ciot_err_t ciot_ble_scn_process_req(ciot_ble_scn_t self, ciot_ble_scn_req_t *req);
ciot_err_t ciot_ble_scn_send_data(ciot_ble_scn_t self, uint8_t *data, int size);

ciot_err_t ciot_ble_scn_handle_event(ciot_ble_scn_t self, void *event, void *event_args);
ciot_err_t ciot_ble_scn_get_adv_info(ciot_ble_scn_t self, ciot_ble_scn_adv_info_t *adv_info);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_BLE_SCANNER__H__