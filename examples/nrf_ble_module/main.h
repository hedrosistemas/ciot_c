/**
 * @file main.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __MAIN__H__
#define __MAIN__H__

#include "ciot.h"
#include "ciot_log.h"
#include "ciot_sys.h"
#include "ciot_uart.h"
#include "ciot_ble.h"
#include "ciot_ble_adv.h"
#include "ciot_ble_scn.h"

typedef enum app_iface_id
{
    APP_IFACE_ID_NONE = -1,
    APP_IFACE_ID_CIOT,
    APP_IFACE_ID_SYS,
    APP_IFACE_ID_UART,
    APP_IFACE_ID_BLE,
    APP_IFACE_ID_BLE_ADV,
    APP_IFACE_ID_BLE_SCN,
    APP_IFACE_ID_COUNT,
} app_iface_id_t;

typedef struct app_ifaces
{
    ciot_t ciot;
    ciot_sys_t sys;
    ciot_uart_t uart;
    ciot_ble_t ble;
    ciot_ble_adv_t ble_adv;
    ciot_ble_scn_t ble_scn;
    ciot_iface_t *list[APP_IFACE_ID_COUNT];
    ciot_msg_data_t *cfgs[APP_IFACE_ID_COUNT];
} app_ifaces_t;

typedef struct app
{
    app_ifaces_t ifaces;
} app_t;

#endif  //!__MAIN__H__
