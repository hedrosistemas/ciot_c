/**
 * @file ciot_custom_config.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-11-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_CUSTOM_CONFIG__H__
#define __CIOT_CUSTOM_CONFIG__H__

#define CIOT_CONFIG_APP_VER 0,3,0
#define CIOT_CONFIG_HARDWARE_NAME "CIOT BOARD"
#define CIOT_CONFIG_LOG_LEVEL CIOT_LOG_LEVEL_DEBUG

#define CIOT_CONFIG_FEATURE_STORAGE 0  ///!< Enable Storage
#define CIOT_CONFIG_FEATURE_SYSTEM 1   ///!< Enable System
#define CIOT_CONFIG_FEATURE_UART 1     ///!< Enable UART
#define CIOT_CONFIG_FEATURE_USB 0      ///!< Enable USB
#define CIOT_CONFIG_FEATURE_BLE 1      ///!< Enable Bluetooth
#define CIOT_CONFIG_FEATURE_BLE_SCN 1  ///!< Enable Bluetooth Scanner
#define CIOT_CONFIG_FEATURE_ETHERNET 0 ///!< Enable Ethernet
#define CIOT_CONFIG_FEATURE_WIFI 0     ///!< Enable WiFi
#define CIOT_CONFIG_FEATURE_NTP 0      ///!< Enable NTP
#define CIOT_CONFIG_FEATURE_OTA 0      ///!< Enable OTA
#define CIOT_CONFIG_FEATURE_HTTPS 0    ///!< Enable HTTP Server
#define CIOT_CONFIG_FEATURE_HTTPC 0    ///!< Enable HTTP Client
#define CIOT_CONFIG_FEATURE_MQTTC 0    ///!< Enable MQTT Client
#define CIOT_CONFIG_MESSAGE_LEN 330    ///!< CIOT expected message size
#define CIOT_CONFIG_MESSAGE_PAYLOAD_LEN 300 ///!< CIOT expected message payload size

#define CIOT_CONFIG_UART_RX_BUF_SIZE 256
#define CIOT_CONFIG_UART_TX_BUF_SIZE 256

#define CIOT_CONFIG_UART1_BAUD 115200
#define CIOT_CONFIG_UART1_PORT 20
#define CIOT_CONFIG_UART1_BRIDGE true
#define CIOT_CONFIG_UART1_DTR false  

#define CIOT_CONFIG_UART2_BAUD 115200
#define CIOT_CONFIG_UART2_PORT 23
#define CIOT_CONFIG_UART1_BRIDGE true
#define CIOT_CONFIG_UART2_DTR false  

#endif //!__CIOT_CUSTOM_CONFIG__H__