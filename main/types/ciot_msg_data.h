/**
 * @file ciot_msg_data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_MSG_DATA__H__
#define __CIOT_MSG_DATA__H__

#include "ciot_err.h"
#include "ciot_config.h"
#include "ciot_sys_data.h"
#include "ciot_uart_data.h"
#include "ciot_tcp_data.h"
#include "ciot_wifi_data.h"
#include "ciot_ble_data.h"
#include "ciot_ntp_data.h"
#include "ciot_ota_data.h"
#include "ciot_https_data.h"
#include "ciot_httpc_data.h"
#include "ciot_mqttc_data.h"
#include "ciot_tcp_data.h"

#define CIOT_MSG_SIZE (sizeof(ciot_msg_t) - sizeof(ciot_msg_data_u))
#define CIOT_MSG_GET_SIZE(type) (CIOT_MSG_SIZE + sizeof(type))

typedef enum __attribute__((packed))
{
    CIOT_MSG_TYPE_UNKNOWN,
    CIOT_MSG_TYPE_START,
    CIOT_MSG_TYPE_STOP,
    CIOT_MSG_TYPE_GET_CONFIG,
    CIOT_MSG_TYPE_GET_STATUS,
    CIOT_MSG_TYPE_REQUEST,
    CIOT_MSG_TYPE_EVENT,
} ciot_msg_type_t;

typedef enum __attribute__((packed))
{
    CIOT_IFACE_TYPE_UNKNOWN,
    CIOT_IFACE_TYPE_SYSTEM,
    CIOT_IFACE_TYPE_UART,
    CIOT_IFACE_TYPE_TCP,
    CIOT_IFACE_TYPE_ETH,
    CIOT_IFACE_TYPE_WIFI,
    CIOT_IFACE_TYPE_BLE,
    CIOT_IFACE_TYPE_NTP,
    CIOT_IFACE_TYPE_OTA,
    CIOT_IFACE_TYPE_HTTP_CLIENT,
    CIOT_IFACE_TYPE_HTTP_SERVER,
    CIOT_IFACE_TYPE_MQTT,
} ciot_msg_iface_type_t;

typedef struct __attribute__((packed))
{
    ciot_msg_iface_type_t type;
    uint8_t id;
} ciot_msg_iface_info_t;

typedef union __attribute__((packed))
{
    ciot_sys_data_u system;
    ciot_uart_data_u uart;
    ciot_tcp_data_u eth;
    ciot_wifi_data_u wifi;
    ciot_ble_data_u ble;
    ciot_ntp_data_u ntp;
    ciot_ota_data_u ota;
    ciot_https_data_u https;
    ciot_httpc_data_u httpc;
    ciot_mqttc_data_u mqtt;
} ciot_msg_data_u;

typedef struct __attribute__((packed))
{
    ciot_msg_type_t type;
    ciot_msg_iface_info_t iface ;
    ciot_err_t error;
    ciot_msg_data_u data;
} ciot_msg_t;

#endif  //!__CIOT_MSG_DATA__H__