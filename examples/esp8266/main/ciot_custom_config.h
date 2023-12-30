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

#define CIOT_CONFIG_APP_VER 0, 3, 0
#define CIOT_CONFIG_HARDWARE_NAME "CIOT BOARD ESP8266"

#define CIOT_CONFIG_FEATURE_STORAGE 1       ///!< Enable Storage
#define CIOT_CONFIG_FEATURE_SYSTEM 1        ///!< Enable System
#define CIOT_CONFIG_FEATURE_UART 0          ///!< Enable UART
#define CIOT_CONFIG_FEATURE_USB 0           ///!< Enable USB
#define CIOT_CONFIG_FEATURE_BLE 0           ///!< Enable Bluetooth
#define CIOT_CONFIG_FEATURE_BLE_SCN 0       ///!< Ble Scanner
#define CIOT_CONFIG_FEATURE_ETHERNET 0      ///!< Enable Ethernet
#define CIOT_CONFIG_FEATURE_WIFI 1          ///!< Enable WiFi
#define CIOT_CONFIG_FEATURE_NTP 1           ///!< Enable NTP
#define CIOT_CONFIG_FEATURE_OTA 0           ///!< Enable OTA
#define CIOT_CONFIG_FEATURE_HTTPS 1         ///!< Enable HTTP Server
#define CIOT_CONFIG_FEATURE_HTTPC 0         ///!< Enable HTTP Client
#define CIOT_CONFIG_FEATURE_MQTTC 1         ///!< Enable MQTT Client
#define CIOT_CONFIG_MESSAGE_LEN 330         ///!< CIOT expected message size
#define CIOT_CONFIG_MESSAGE_PAYLOAD_LEN 256 ///!< CIOT payload size

#define CIOT_CONFIG_STORAGE_TYPE CIOT_STORAGE_TYPE_FLASH

#define CIOT_CONFIG_WIFI_AP_AUTH WIFI_AUTH_WPA_WPA2_PSK
#define CIOT_CONFIG_WIFI_AP_MAX_CONN 1
#define CIOT_CONFIG_WIFI_AP_SSID "CIOT ESP8266"
#define CIOT_CONFIG_WIFI_AP_PASSWORD "admin123"

#define CIOT_CONFIG_NTP_TZ "<-03>3"
#define CIOT_CONFIG_NTP_SERVERS_COUNT 3
#define CIOT_CONFIG_NTP_SYNC_INTERVAL (3600 * 1000)

#define CIOT_CONFIG_HTTPS_ADDRESS "http://127.0.0.1:80"
#define CIOT_CONFIG_HTTPS_ROUTE "/v1/lumi"

#define CIOT_CONFIG_SYS \
    {                   \
    }

#define CIOT_CONFIG_STORAGE              \
    {                                    \
        .type = CIOT_CONFIG_STORAGE_TYPE \
    }

#define CIOT_CONFIG_HTTPS                     \
    {                                         \
        .address = CIOT_CONFIG_HTTPS_ADDRESS, \
        .route = CIOT_CONFIG_HTTPS_ROUTE      \
    }

#define CIOT_CONFIG_WIFI_AP                       \
    {                                             \
        .type = CIOT_WIFI_IF_AP,                  \
        .ssid = CIOT_CONFIG_WIFI_AP_SSID,         \
        .password = CIOT_CONFIG_WIFI_AP_PASSWORD, \
    }

#endif //!__CIOT_CUSTOM_CONFIG__H__