/**
 * @file ciot_sys_common.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-01-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ciot_sys.h"
#include "ciot_config.h"

ciot_sys_hw_t ciot_sys_get_hw(void)
{
#if defined(ICACHE_FLASH) || defined(ICACHE_RAM_ATTR)
    return CIOT_SYS_HW_ESP8266;
#elif defined(_WIN32)
    return CIOT_SYS_HW_WIN32;
#elif defined(ARDUINO)
    return CIOT_SYS_HW_ARDUINO;
#elif defined(ESP_PLATFORM)
    return CIOT_SYS_HW_ESP32;
#elif defined(NRF51)
    return CIOT_SYS_HW_NRF51;
#elif defined(NRF52) || defined(NRF52840_XXAA)
    return CIOT_SYS_HW_NRF52;
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    return CIOT_SYS_HW_LINUX;
#else
    return CIOT_SYS_HW_UNKNOWN;
#endif
}

ciot_err_t ciot_sys_update_features(ciot_sys_features_t *features)
{
    CIOT_NULL_CHECK(features);

#ifdef CIOT_CONFIG_FEATURE_STORAGE
    features->hw.storage = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_SYSTEM
    features->hw.system = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_UART
    features->hw.uart = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_USB
    features->hw.usb = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_ETHERNET
    features->hw.ethernet = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_WIFI
    features->hw.wifi = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_BLE_SCN
    features->hw.ble_scn = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_GPIO
    features->hw.gpio = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_NTP
    features->sw.ntp = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_OTA
    features->sw.ota = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_HTTPC
    features->sw.http_client = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_HTTPS
    features->sw.http_server = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_MQTTC
    features->sw.mqtt_client = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_TIMER
    features->sw.timer = true;
#endif

#ifdef CIOT_CONFIG_FEATURE_SERIALIZER
    features->sw.serializer = true;
#endif

    return CIOT_OK;
}
