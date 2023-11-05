/**
 * @file expected_data.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-11-05
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __EXPECTED_DATA__H__
#define __EXPECTED_DATA__H__

#define EXPECTED_FIRMWARE_VER \
    {                         \
        0, 3, 0               \
    }
#define EXPECTED_HARDWARE_NAME "CIOT BOARD"

#define EXPECTED_FEATURE_STORAGE 1  ///!< Enable Storage
#define EXPECTED_FEATURE_SYSTEM 1   ///!< Enable System
#define EXPECTED_FEATURE_UART 1     ///!< Enable UART
#define EXPECTED_FEATURE_USB 0      ///!< Enable USB
#define EXPECTED_FEATURE_BLE 0      ///!< Enable Bluetooth
#define EXPECTED_FEATURE_ETHERNET 0 ///!< Enable Ethernet
#define EXPECTED_FEATURE_WIFI 0     ///!< Enable WiFi
#define EXPECTED_FEATURE_NTP 0      ///!< Enable NTP
#define EXPECTED_FEATURE_OTA 0      ///!< Enable OTA
#define EXPECTED_FEATURE_HTTPS 1    ///!< Enable HTTP Server
#define EXPECTED_FEATURE_HTTPC 1    ///!< Enable HTTP Client
#define EXPECTED_FEATURE_MQTTC 1    ///!< Enable MQTT Client
#define EXPECTED_MESSAGE_LEN 330    ///!< CIOT expected message size

#define EXPECTED_UART_RX_BUF_SIZE 256
#define EXPECTED_UART_TX_BUF_SIZE 256
#define EXPECTED_UART_BAUD 115200
#define EXPECTED_UART_PORT 17

#define EXPECTED_HTTPS_ADDRESS "http://127.0.0.1:8080"
#define EXPECTED_HTTPS_ROUTE "/v1/ciot"

#define EXPECTED_HTTPC_URL "http://127.0.0.1:8181"
#define EXPECTED_HTTPC_TRANSPORT CIOT_HTTPC_TRANSPORT_TCP
#define EXPECTED_HTTPC_METHOD CIOT_HTTPC_METHOD_POST
#define EXPECTED_HTTPC_TIMEOUT 5000

#define EXPECTED_MQTTC_ID "ciot_win32_sample"
#define EXPECTED_MQTTC_URL "mqtt://test.mosquitto.org"
#define EXPECTED_MQTTC_PORT 1883
#define EXPECTED_MQTTC_QOS 0
#define EXPECTED_MQTTC_TOPIC_B2D "CIOT/B2D"
#define EXPECTED_MQTTC_TOPIC_D2B "CIOT/D2B"

#include "ciot_sys.h"
#include "ciot_uart.h"

ciot_sys_info_t expected_sys_info = {
    .features = {
        .hw = {
            .storage = EXPECTED_FEATURE_STORAGE,
            .system = EXPECTED_FEATURE_SYSTEM,
            .uart = EXPECTED_FEATURE_UART,
            .usb = EXPECTED_FEATURE_USB,
            .ethernet = EXPECTED_FEATURE_ETHERNET,
            .wifi = EXPECTED_FEATURE_WIFI,
            .bluetooth = EXPECTED_FEATURE_BLE,
        },
        .sw = {
            .ntp = EXPECTED_FEATURE_NTP,
            .ota = EXPECTED_FEATURE_OTA,
            .http_client = EXPECTED_FEATURE_HTTPC,
            .http_server = EXPECTED_FEATURE_HTTPS,
            .mqtt_client = EXPECTED_FEATURE_MQTTC,
        },
    },
    .fw_ver = EXPECTED_FIRMWARE_VER,
    .hw_name = EXPECTED_HARDWARE_NAME,
};

ciot_uart_cfg_t expected_uart_cfg = {
    .baud_rate = EXPECTED_UART_BAUD,
    .num = EXPECTED_UART_PORT,
};

ciot_uart_status_t expected_uart_status = {
    .state = CIOT_UART_STATE_STARTED,
    .error = CIOT_OK,
};

#endif //!__EXPECTED_DATA__H__