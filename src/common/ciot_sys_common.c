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

# ifndef CIOT_CONFIG_FEATURE_STORAGE
#define CIOT_CONFIG_FEATURE_STORAGE 0
#endif
# ifndef CIOT_CONFIG_FEATURE_SYSTEM
#define CIOT_CONFIG_FEATURE_SYSTEM 0
#endif
# ifndef CIOT_CONFIG_FEATURE_UART
#define CIOT_CONFIG_FEATURE_UART 0
#endif
# ifndef CIOT_CONFIG_FEATURE_USB
#define CIOT_CONFIG_FEATURE_USB 0
#endif
# ifndef CIOT_CONFIG_FEATURE_ETHERNET
#define CIOT_CONFIG_FEATURE_ETHERNET 0
#endif
# ifndef CIOT_CONFIG_FEATURE_WIFI
#define CIOT_CONFIG_FEATURE_WIFI 0
#endif
# ifndef CIOT_CONFIG_FEATURE_BLE_SCN
#define CIOT_CONFIG_FEATURE_BLE_SCN 0
#endif
# ifndef CIOT_CONFIG_FEATURE_NTP
#define CIOT_CONFIG_FEATURE_NTP 0
#endif
# ifndef CIOT_CONFIG_FEATURE_OTA
#define CIOT_CONFIG_FEATURE_OTA 0
#endif
# ifndef CIOT_CONFIG_FEATURE_HTTPC
#define CIOT_CONFIG_FEATURE_HTTPC 0
#endif
# ifndef CIOT_CONFIG_FEATURE_HTTPS
#define CIOT_CONFIG_FEATURE_HTTPS 0
#endif
# ifndef CIOT_CONFIG_FEATURE_MQTTC
#define CIOT_CONFIG_FEATURE_MQTTC 0
#endif
# ifndef CIOT_CONFIG_FEATURE_TIMER
#define CIOT_CONFIG_FEATURE_TIMER 0
#endif

ciot_err_t ciot_sys_update_features(ciot_sys_features_t *features)
{
    CIOT_NULL_CHECK(features);
    features->hw.storage = CIOT_CONFIG_FEATURE_STORAGE;
    features->hw.system = CIOT_CONFIG_FEATURE_SYSTEM;
    features->hw.uart = CIOT_CONFIG_FEATURE_UART;
    features->hw.usb = CIOT_CONFIG_FEATURE_USB;
    features->hw.ethernet = CIOT_CONFIG_FEATURE_ETHERNET;
    features->hw.wifi = CIOT_CONFIG_FEATURE_WIFI;
    features->hw.ble_scn = CIOT_CONFIG_FEATURE_BLE_SCN;

    features->sw.ntp = CIOT_CONFIG_FEATURE_NTP;
    features->sw.ota = CIOT_CONFIG_FEATURE_OTA;
    features->sw.http_client = CIOT_CONFIG_FEATURE_HTTPC;
    features->sw.http_server = CIOT_CONFIG_FEATURE_HTTPS;
    features->sw.mqtt_client = CIOT_CONFIG_FEATURE_MQTTC;
    features->sw.timer = CIOT_CONFIG_FEATURE_TIMER;
    return CIOT_OK;
}
