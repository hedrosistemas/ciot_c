/**
 * @file ciot_config.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_CONFIG__H__
#define __CIOT_CONFIG__H__

#if defined(ICACHE_FLASH) || defined(ICACHE_RAM_ATTR)
#define CIOT_TARGET_ESP8266
#endif

#if defined(_WIN32)
#define CIOT_TARGET_WIN
#define CIOT_TARGET_PC
#endif

#if defined(ARDUINO)
#define CIOT_TARGET_ARDUINO
#endif

#if defined(CIOT_TARGET_ESP8266) || defined(CIOT_TARGET_WIN)
#define CIOT_TARGET_MONGOOSE
#elif defined(ARDUINO)
#define CIOT_TARGET_INO
#elif defined(ESP_PLATFORM)
#define CIOT_TARGET_ESP32
#elif defined(NRF51) || defined(NRF52) || defined(NRF52840_XXAA)
#define CIOT_TARGET_NRF
#else
#define CIOT_TARGET_UNKNOWN
#warning "Target undefined."
#endif

#if defined(CONFIG_IDF_TARGET_ESP8266)
#define CIOT_TARGET_ESP8266
#endif

#if __has_include("ciot_custom_config.h")
#include "ciot_custom_config.h"
#else

#warning "ciot_custom_config.h not found. Using default configuration. Create a ciot_custom_config.h file to customize the ciot lib configurations."

#define CIOT_CONFIG_LOG_LEVEL CIOT_LOG_LEVEL_INFO
#define CIOT_CONFIG_APP_VER 0,3,0
#define CIOT_CONFIG_HARDWARE_NAME "CIOT BOARD"

#define CIOT_CONFIG_FEATURE_STORAGE 1  ///!< Enable Storage
#define CIOT_CONFIG_FEATURE_SYSTEM 1   ///!< Enable System
#define CIOT_CONFIG_FEATURE_UART 1     ///!< Enable UART
#define CIOT_CONFIG_FEATURE_USB 0      ///!< Enable USB
#define CIOT_CONFIG_FEATURE_BLE_SCN 1  ///!< Enable Bluetooth Low Energy Scanner
#define CIOT_CONFIG_FEATURE_ETHERNET 1 ///!< Enable Ethernet
#define CIOT_CONFIG_FEATURE_WIFI 1     ///!< Enable WiFi
#define CIOT_CONFIG_FEATURE_NTP 1      ///!< Enable NTP
#define CIOT_CONFIG_FEATURE_OTA 1      ///!< Enable OTA
#define CIOT_CONFIG_FEATURE_HTTPS 1    ///!< Enable HTTP Server
#define CIOT_CONFIG_FEATURE_HTTPC 1    ///!< Enable HTTP Client
#define CIOT_CONFIG_FEATURE_MQTTC 1    ///!< Enable MQTT Client
#define CIOT_CONFIG_FEATURE_BRIDGE 1   ///!< Enable Bridge Implementation

#define CIOT_CONFIG_MESSAGE_LEN 330         ///!< CIOT expected message size
#define CIOT_CONFIG_MESSAGE_PAYLOAD_LEN 256 ///!< CIOT message payload size

#define CIOT_CONFIG_UART_RX_BUF_SIZE 256
#define CIOT_CONFIG_UART_TX_BUF_SIZE 256
#define CIOT_CONFIG_UART_QUEUE_SIZE 20
#define CIOT_CONFIG_UART_TASK_SIZE 2048
#define CIOT_CONFIG_UART_TASK_PRIO 12
#define CIOT_CONFIG_UART_TASK_CORE 0

#define CIOT_CONFIG_ETH_PHY_KSZ8081 1
#define CIOT_CONFIG_ETH_PHY_NEW(x) esp_eth_phy_new_ksz80xx(&x)
#define CIOT_CONFIG_ETH_PHY_ADDR 0
#define CIOT_CONFIG_ETH_GPIO_PHY_RST 5
#define CIOT_CONFIG_ETH_GPIO_MDC 23
#define CIOT_CONFIG_ETH_GPIO_MDIO 18

#define CIOT_CONFIG_WIFI_AP_SSID_MASK "CIOT BOARD %s"
#define CIOT_CONFIG_WIFI_AP_PASS "administrator"
#define CIOT_CONFIG_WIFI_AP_AUTH WIFI_AUTH_WPA_WPA2_PSK
#define CIOT_CONFIG_WIFI_AP_MAX_CONN 1

#define CIOT_CONFIG_WIFI_STA_SSID "CABO CANAVERAL"
#define CIOT_CONFIG_WIFI_STA_PASS "16192020"

#define CIOT_CONFIG_MQTT_CLIENT_ID_LEN 32
#define CIOT_CONFIG_MQTT_URL_LEN 64
#define CIOT_CONFIG_MQTT_USER_LEN 32
#define CIOT_CONFIG_MQTT_PASS_LEN 32
#define CIOT_CONFIG_MQTT_TOPIC_LEN 32
#define CIOT_CONFIG_MQTT_MSG_LEN 256

#define CIOT_CONFIG_NTP_OP_MODE 0
#define CIOT_CONFIG_NTP_SYNC_MODE 0
#define CIOT_CONFIG_NTP_SYNC_INTERVAL (3600 * 1000)
#define CIOT_CONFIG_NTP_TZ "<-03>3"
#define CIOT_CONFIG_NTP_SERVERS_COUNT 3
#define CIOT_CONFIG_NTP_SERVER1 "pool.ntp.org"
#define CIOT_CONFIG_NTP_SERVER2 "time.google.com"
#define CIOT_CONFIG_NTP_SERVER3 "gps.ntp.br"

#define CIOT_CONFIG_OTA_TASK_STACK_SIZE 8192
#define CIOT_CONFIG_OTA_TASK_TASK_PRIORITY (tskIDLE_PRIORITY + 4)
#define CIOT_CONFIG_OTA_TASK_CORE_ID 1

#endif //__has_include("ciot_custom_config.h")

#endif //!__CIOT_CONFIG__H__