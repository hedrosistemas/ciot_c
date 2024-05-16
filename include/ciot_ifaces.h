/**
 * @file ciot_ifaces.h
 * @brief Header file for CIOT interfaces.
 * @version 0.1
 * @date 2024-04-15
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2024
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

/**
 * @brief Enumeration for CIOT interface IDs.
 */
typedef enum ciot_iface_id {
    CIOT_IFACE_ID_UNKNOWN, /**< Unknown interface ID. */
    CIOT_IFACE_ID_CIOT, /**< CIOT interface ID. */
    CIOT_IFACE_ID_STORAGE, /**< Storage interface ID. */
    CIOT_IFACE_ID_SYSTEM, /**< System interface ID. */
    CIOT_IFACE_ID_UART, /**< UART interface ID. */
    CIOT_IFACE_ID_USB, /**< USB interface ID. */
    CIOT_IFACE_ID_TCP, /**< TCP interface ID. */
    CIOT_IFACE_ID_ETH, /**< Ethernet interface ID. */
    CIOT_IFACE_ID_WIFI, /**< WiFi interface ID. */
    CIOT_IFACE_ID_BLE, /**< BLE interface ID. */
    CIOT_IFACE_ID_BLE_SCN, /**< BLE SCN interface ID. */
    CIOT_IFACE_ID_GPIO, /**< GPIO interface ID. */
    CIOT_IFACE_ID_NTP, /**< NTP interface ID. */
    CIOT_IFACE_ID_OTA, /**< OTA interface ID. */
    CIOT_IFACE_ID_DFU, /**< DFU interface ID. */
    CIOT_IFACE_ID_HTTP_CLIENT, /**< HTTP client interface ID. */
    CIOT_IFACE_ID_HTTP_SERVER, /**< HTTP server interface ID. */
    CIOT_IFACE_ID_MQTT, /**< MQTT interface ID. */
    CIOT_IFACE_ID_BRIDGE, /**< Bridge interface ID. */
} ciot_iface_id_t;

/**
 * @brief Structure representing CIOT interfaces.
 */
typedef struct ciot_ifaces {
    ciot_t ciot; /**< CIOT interface. */
    ciot_storage_t storage; /**< Storage interface. */
    ciot_sys_t system; /**< System interface. */
    ciot_uart_t uart; /**< UART interface. */
    ciot_usb_t usb; /**< USB interface. */
    ciot_tcp_t tcp; /**< TCP interface. */
    ciot_tcp_t eth; /**< Ethernet interface. */
    ciot_wifi_t wifi; /**< WiFi interface. */
    ciot_ble_t ble; /**< BLE interface. */
    ciot_ble_scn_t ble_scn; /**< BLE SCN interface. */
    ciot_ntp_t ntp; /**< NTP interface. */
    ciot_ota_t ota; /**< OTA interface. */
    ciot_https_t https; /**< HTTP server interface. */
    ciot_httpc_t httpc; /**< HTTP client interface. */
    ciot_mqttc_t mqtt; /**< MQTT client interface. */
    ciot_bridge_t bridge; /**< Bridge interface. */
} ciot_ifaces_t;

#endif //!__CIOT_IFACES__H__
