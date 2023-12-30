/**
 * @file ciot_custom_config.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_CUSTOM_CONFIG__H__
#define __CIOT_CUSTOM_CONFIG__H__

#ifdef __cplusplus
extern "C"
{
#endif

#define CIOT_CONFIG_LOG_LEVEL CIOT_LOG_LEVEL_NONE ///!< Log level
#define CIOT_CONFIG_APP_VER 0, 3, 0               ///!< Application version
#define CIOT_CONFIG_HARDWARE_NAME "CIOT BOARD"    ///!< Hardware name
#define CIOT_CONFIG_FEATURE_STORAGE 0             ///!< Enable Storage
#define CIOT_CONFIG_FEATURE_SYSTEM 1              ///!< Enable System
#define CIOT_CONFIG_FEATURE_UART 1                ///!< Enable UART
#define CIOT_CONFIG_FEATURE_USB 0                 ///!< Enable USB
#define CIOT_CONFIG_FEATURE_BLE_SCN 0             ///!< Enable Bluetooth Low Energy Scanner
#define CIOT_CONFIG_FEATURE_ETHERNET 0            ///!< Enable Ethernet
#define CIOT_CONFIG_FEATURE_WIFI 0                ///!< Enable WiFi
#define CIOT_CONFIG_FEATURE_NTP 0                 ///!< Enable NTP
#define CIOT_CONFIG_FEATURE_OTA 0                 ///!< Enable OTA
#define CIOT_CONFIG_FEATURE_HTTPS 0               ///!< Enable HTTP Server
#define CIOT_CONFIG_FEATURE_HTTPC 0               ///!< Enable HTTP Client
#define CIOT_CONFIG_FEATURE_MQTTC 0               ///!< Enable MQTT Client
#define CIOT_CONFIG_FEATURE_BRIDGE 0              ///!< Enable Bridge Implementation
#define CIOT_CONFIG_MESSAGE_LEN 330               ///!< CIOT expected message size
#define CIOT_CONFIG_MESSAGE_PAYLOAD_LEN 256       ///!< CIOT message payload size

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_CUSTOM_CONFIG__H__