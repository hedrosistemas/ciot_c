/**
 * @file ciot_ifaces.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_IFACES__H__
#define __CIOT_IFACES__H__

#include "ciot.h"
#include "ciot_storage.h"
#include "ciot_sys.h"
#include "ciot_uart.h"
#include "ciot_usb.h"
#include "ciot_tcp.h"
#include "ciot_tcp.h"
#include "ciot_wifi.h"
#include "ciot_ble.h"
#include "ciot_ble_scn.h"
#include "ciot_ntp.h"
#include "ciot_ota.h"
#include "ciot_https.h"
#include "ciot_httpc.h"
#include "ciot_mqttc.h"
#include "ciot_bridge.h"

typedef enum ciot_iface_id
{
    CIOT_IFACE_ID_UNKNOWN,
    CIOT_IFACE_ID_CIOT,
    CIOT_IFACE_ID_STORAGE,
    CIOT_IFACE_ID_SYSTEM,
    CIOT_IFACE_ID_UART,
    CIOT_IFACE_ID_USB,
    CIOT_IFACE_ID_TCP,
    CIOT_IFACE_ID_ETH,
    CIOT_IFACE_ID_WIFI,
    CIOT_IFACE_ID_BLE,
    CIOT_IFACE_ID_BLE_SCN,
    CIOT_IFACE_ID_GPIO,
    CIOT_IFACE_ID_NTP,
    CIOT_IFACE_ID_OTA,
    CIOT_IFACE_ID_DFU,
    CIOT_IFACE_ID_HTTP_CLIENT,
    CIOT_IFACE_ID_HTTP_SERVER,
    CIOT_IFACE_ID_MQTT,
    CIOT_IFACE_ID_BRIDGE,
} ciot_iface_id_t;

typedef struct ciot_ifaces
{
    ciot_t ciot;
    ciot_storage_t storage;
    ciot_sys_t system;
    ciot_uart_t uart;
    ciot_usb_t usb;
    ciot_tcp_t tcp;
    ciot_tcp_t eth;
    ciot_wifi_t wifi;
    ciot_ble_t ble;
    ciot_ble_scn_t ble_scn;
    ciot_ntp_t ntp;
    ciot_ota_t ota;
    ciot_https_t https;
    ciot_httpc_t httpc;
    ciot_mqttc_t mqtt;
    ciot_bridge_t bridge;
} ciot_ifaces_t;

#endif  //!__CIOT_IFACES__H__