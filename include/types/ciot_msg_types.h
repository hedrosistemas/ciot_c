/**
 * @file ciot_msg_types.h
 * @brief Defines data types and structures for CIOT messaging.
 * @version 0.1
 * @date 2023-10-09
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_MSG_DATA__H__
#define __CIOT_MSG_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "types/ciot_types.h"
#include "types/ciot_storage_types.h"
#include "types/ciot_sys_types.h"
#include "types/ciot_uart_types.h"
#include "types/ciot_usb_types.h"
#include "types/ciot_tcp_types.h"
#include "types/ciot_wifi_types.h"
#include "types/ciot_ble_types.h"
#include "types/ciot_ble_scn_types.h"
#include "types/ciot_ntp_types.h"
#include "types/ciot_dfu_types.h"
#include "types/ciot_ota_types.h"
#include "types/ciot_https_types.h"
#include "types/ciot_httpc_types.h"
#include "types/ciot_mqttc_types.h"
#include "types/ciot_bridge_types.h"

/** Size of the message header */
#define CIOT_MSG_HEADER_SIZE (sizeof(ciot_msg_header_t))
/** Calculate message size */
#define CIOT_MSG_GET_SIZE(data) (CIOT_MSG_HEADER_SIZE + sizeof(data))
/** Maximum message size */
#define CIOT_MSG_MAX_SIZE sizeof(ciot_msg_t);

/**
 * @brief Enumeration for CIOT message types.
 */
typedef enum __attribute__((packed))
{
    CIOT_MSG_TYPE_UNKNOWN, /**< Unknown message type */
    CIOT_MSG_TYPE_START, /**< Start message type */
    CIOT_MSG_TYPE_STOP, /**< Stop message type */
    CIOT_MSG_TYPE_GET_CONFIG, /**< Get configuration message type */
    CIOT_MSG_TYPE_GET_STATUS, /**< Get status message type */
    CIOT_MSG_TYPE_REQUEST, /**< Request message type */
    CIOT_MSG_TYPE_ERROR, /**< Error message type */
    CIOT_MSG_TYPE_EVENT, /**< Event message type */
    CIOT_MSG_TYPE_CUSTOM, /**< Custom message type */
} ciot_msg_type_t;

/**
 * @brief Enumeration for CIOT message interface types.
 */
typedef enum __attribute__((packed))
{
    CIOT_IFACE_TYPE_UNKNOWN, /**< Unknown interface type */
    CIOT_IFACE_TYPE_CIOT, /**< CIOT interface type */
    CIOT_IFACE_TYPE_STORAGE, /**< Storage interface type */
    CIOT_IFACE_TYPE_SYSTEM, /**< System interface type */
    CIOT_IFACE_TYPE_UART, /**< UART interface type */
    CIOT_IFACE_TYPE_USB, /**< USB interface type */
    CIOT_IFACE_TYPE_TCP, /**< TCP interface type */
    CIOT_IFACE_TYPE_ETH, /**< Ethernet interface type */
    CIOT_IFACE_TYPE_WIFI, /**< WiFi interface type */
    CIOT_IFACE_TYPE_BLE, /**< BLE interface type */
    CIOT_IFACE_TYPE_BLE_SCN, /**< BLE SCN interface type */
    CIOT_IFACE_TYPE_GPIO, /**< GPIO interface type */
    CIOT_IFACE_TYPE_NTP = 127, /**< NTP interface type */
    CIOT_IFACE_TYPE_OTA, /**< OTA interface type */
    CIOT_IFACE_TYPE_DFU, /**< DFU interface type */
    CIOT_IFACE_TYPE_HTTP_CLIENT, /**< HTTP client interface type */
    CIOT_IFACE_TYPE_HTTP_SERVER, /**< HTTP server interface type */
    CIOT_IFACE_TYPE_MQTT, /**< MQTT interface type */
    CIOT_IFACE_TYPE_CUSTOM, /**< Custom interface type */
    CIOT_IFACE_TYPE_BRIDGE, /**< Bridge interface type */
} ciot_msg_iface_type_t;

/**
 * @brief Structure for CIOT message interface information.
 */
typedef struct __attribute__((packed))
{
    uint8_t id; /**< Interface ID */
    ciot_msg_iface_type_t type; /**< Interface type */
} ciot_msg_iface_info_t;

/**
 * @brief Structure for CIOT message error information.
 */
typedef struct __attribute__((packed))
{
    ciot_msg_type_t msg_type; /**< Message type */
    uint32_t code; /**< Error code */
} ciot_msg_error_t;

/**
 * @brief Union for CIOT message data.
 */
typedef union __attribute__((packed))
{
    ciot_data_u ciot; /**< CIOT data */
    ciot_storage_data_u storage; /**< Storage data */
    ciot_sys_data_u system; /**< System data */
    ciot_uart_data_u uart; /**< UART data */
    ciot_usb_data_u usb; /**< USB data */
    ciot_tcp_data_u tcp; /**< TCP data */
    ciot_tcp_data_u eth; /**< ETH data */
    ciot_wifi_data_u wifi; /**< WiFi data */
    ciot_ble_data_u ble; /**< BLE data */
    ciot_ble_scn_data_u ble_scn; /**< BLE SCN data */
    ciot_ntp_data_u ntp; /**< NTP data */
    ciot_ota_data_u ota; /**< OTA data */
    ciot_dfu_data_u dfu; /**< DFU data */
    ciot_https_data_u https; /**< HTTP server data */
    ciot_httpc_data_u httpc; /**< HTTP client data */
    ciot_mqttc_data_u mqtt; /**< MQTT client data */
    ciot_bridge_data_u bridge; /**< Bridge data */
    ciot_msg_error_t error; /**< Error data */
    uint8_t payload[256]; /**< Payload data */
} ciot_msg_data_u;

/**
 * @brief Structure for CIOT message header.
 */
typedef struct __attribute__((packed))
{
    uint8_t id; /**< Message ID */
    ciot_msg_type_t type; /**< Message type */
    ciot_msg_iface_info_t iface; /**< Interface information */
} ciot_msg_header_t;

/**
 * @brief Structure for CIOT message.
 */
typedef struct __attribute__((packed))
{
    uint8_t id; /**< Message ID */
    ciot_msg_type_t type; /**< Message type */
    ciot_msg_iface_info_t iface; /**< Interface information */
    ciot_msg_data_u data; /**< Message data */
} ciot_msg_t;

/**
 * @brief Convert CIOT message type to string.
 * @param msg The CIOT message.
 * @return The string representation of the message type.
 */
const char *ciot_msg_type_to_str(ciot_msg_t *msg);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_MSG_DATA__H__
