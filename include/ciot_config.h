/**
 * @file ciot_config.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_CONFIG__H__
#define __CIOT_CONFIG__H__

#if defined(ICACHE_FLASH) || defined(ICACHE_RAM_ATTR)
#define CIOT_TARGET_ESP8266
#elif defined(_WIN32)
#define CIOT_TARGET_WIN
#elif defined(ARDUINO)
#define CIOT_TARGET_INO
#elif defined(ESP_PLATFORM)
#define CIOT_TARGET_ESP32
#elif defined(NRF51) || defined(NRF52) || defined(NRF52840_XXAA)
#define CIOT_TARGET_NRF
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#define CIOT_TARGET_LINUX
#else
#define CIOT_TARGET_UNKNOWN
#warning "Target undefined."
#endif

#define CIOT_VER 0, 1, 0

#if defined(CIOT_TARGET_WIN) || defined(CIOT_TARGET_LINUX)

extern struct mg_mgr mg; ///< Mongoose network manager.

#define CIOT_HANDLE &mg

#else

#define CIOT_HANDLE NULL

#endif

#if __has_include("ciot_custom_config.h")
#include "ciot_custom_config.h"
#else
#warning "ciot_custom_config.h not found. Using default configuration. Create a ciot_custom_config.h file to customize the ciot lib configurations."

#define CIOT_CONFIG_LOG_LEVEL CIOT_LOG_LEVEL_INFO
#define CIOT_CONFIG_HARDWARE_NAME "CIoT Device"
#define CIOT_CONFIG_APP_VER 0, 1, 0             

#define CIOT_CONFIG_FEATURE_STORAGE 0
#define CIOT_CONFIG_FEATURE_SYSTEM 0
#define CIOT_CONFIG_FEATURE_UART 0
#define CIOT_CONFIG_FEATURE_USB 0
#define CIOT_CONFIG_FEATURE_ETHERNET 0
#define CIOT_CONFIG_FEATURE_WIFI 0
#define CIOT_CONFIG_FEATURE_BLE_SCN 0
#define CIOT_CONFIG_FEATURE_GPIO 0
#define CIOT_CONFIG_FEATURE_NTP 0
#define CIOT_CONFIG_FEATURE_OTA 0
#define CIOT_CONFIG_FEATURE_DFU 0
#define CIOT_CONFIG_FEATURE_HTTP_CLIENT 0
#define CIOT_CONFIG_FEATURE_HTTP_SERVER 0
#define CIOT_CONFIG_FEATURE_MQTT_CLIENT 0
#define CIOT_CONFIG_FEATURE_TIMER 0
#define CIOT_CONFIG_FEATURE_SERIALIZER 0

#endif

#endif  //!__CIOT_CONFIG__H__
