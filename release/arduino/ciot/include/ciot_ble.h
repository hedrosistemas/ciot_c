/**
 * @file ciot_ble.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_BLE__H__
#define __CIOT_BLE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_ble_types.h"
#include "ciot_err.h"
#include "ciot_ble_scn.h"

typedef struct ciot_ble *ciot_ble_t;

typedef enum ciot_ble_mac_type
{
    CIOT_BLE_MAC_TYPE_UNKNOWN,
    CIOT_BLE_MAC_TYPE_HARDWARE,
    CIOT_BLE_MAC_TYPE_SOFTWARE,
} ciot_ble_mac_type_t;

// ciot_err_t ciot_ble_power_management_init(void);
// ciot_err_t ciot_ble_stack_init(void);

// ciot_err_t ciot_ble_init(void);

typedef struct ciot_ble_ifaces
{
    ciot_ble_scn_t scanner;
    // ciot_ble_adv_t adv;
} ciot_ble_ifaces_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_ble_status_t status;
} ciot_ble_status_msg_t;

ciot_ble_t ciot_ble_new(void *handle);
ciot_err_t ciot_ble_start(ciot_ble_t self, ciot_ble_cfg_t *cfg);
ciot_err_t ciot_ble_stop(ciot_ble_t self);
ciot_err_t ciot_ble_process_req(ciot_ble_t self, ciot_ble_req_t *req);
ciot_err_t ciot_ble_send_data(ciot_ble_t self, uint8_t *data, int size);

ciot_err_t ciot_ble_task(ciot_ble_t self);
ciot_err_t ciot_ble_set_mac(ciot_ble_t self, uint8_t mac[6]);
ciot_err_t ciot_ble_get_mac(ciot_ble_t self, ciot_ble_mac_type_t type, uint8_t mac[6]);
ciot_err_t ciot_ble_set_ifaces(ciot_ble_t self, ciot_ble_ifaces_t *ifaces);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_BLE__H__