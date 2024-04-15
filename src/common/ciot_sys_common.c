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
