/**
 * @file ciot_custom_config_win.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __CIOT_CUSTOM_CONFIG_WIN__H__
#define __CIOT_CUSTOM_CONFIG_WIN__H__

#define CIOT_CONFIG_LOG_LEVEL CIOT_LOG_LEVEL_INFO ///!< Log level
#define CIOT_TARGET_MONGOOSE                      ///!< Enable mongoose on windows
#define CIOT_CONFIG_APP_VER 0, 1, 0               ///!< Application version
#define CIOT_CONFIG_HARDWARE_NAME "CIOT WIN32"    ///!< Harware name
#define CIOT_CONFIG_FEATURE_STORAGE 0             ///!< Enable Storage
#define CIOT_CONFIG_FEATURE_SYSTEM 1              ///!< Enable System
#define CIOT_CONFIG_FEATURE_UART 0                ///!< Enable UART
#define CIOT_CONFIG_FEATURE_USB 0                 ///!< Enable USB
#define CIOT_CONFIG_FEATURE_BLE 0                 ///!< Enable Bluetooth
#define CIOT_CONFIG_FEATURE_BLE_SCN 0             ///!< Enable Bluetooth Scanner
#define CIOT_CONFIG_FEATURE_ETHERNET 0            ///!< Enable Ethernet
#define CIOT_CONFIG_FEATURE_WIFI 0                ///!< Enable WiFi
#define CIOT_CONFIG_FEATURE_NTP 0                 ///!< Enable NTP
#define CIOT_CONFIG_FEATURE_OTA 0                 ///!< Enable OTA
#define CIOT_CONFIG_FEATURE_HTTPS 0               ///!< Enable HTTP Server
#define CIOT_CONFIG_FEATURE_HTTPC 0               ///!< Enable HTTP Client
#define CIOT_CONFIG_FEATURE_MQTTC 0               ///!< Enable MQTT Client
#define CIOT_CONFIG_FEATURE_BRIDGE 0              ///!< Enable Bridge Implementation
#define CIOT_CONFIG_MESSAGE_LEN 330               ///!< CIOT expected message size
#define CIOT_CONFIG_MESSAGE_PAYLOAD_LEN 256       ///< CIOT expected message payload size

#endif //!__CIOT_CUSTOM_CONFIG_WIN__H__