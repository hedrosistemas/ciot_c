/**
 * @file ciot_wifi.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ciot_wifi.h"
#include <string.h>

#if CIOT_CONFIG_FEATURE_WIFI && defined(CIOT_TARGET_MONGOOSE) && defined(CIOT_TARGET_WIN)

#include <string.h>
#include <stdbool.h>

#include "ciot_tcp.h"

struct ciot_wifi
{
    ciot_iface_t iface;
};

ciot_wifi_t ciot_wifi_new(void *handle)
{
    return NULL;
}

ciot_err_t ciot_wifi_start(ciot_wifi_t self, ciot_wifi_cfg_t *cfg)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_wifi_stop(ciot_wifi_t self)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_wifi_process_req(ciot_wifi_t self, ciot_wifi_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_wifi_send_data(ciot_wifi_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_wifi_get_mac(ciot_wifi_t self, ciot_wifi_type_t type, uint8_t mac[6])
{
    switch (type)
    {
    case CIOT_WIFI_IF_AP:
    {
        uint8_t mac_ptr[] = {CIOT_CONFIG_WIFI_AP_MAC};
        memcpy(mac, mac_ptr, 6);
        break;
    }
    case CIOT_WIFI_IF_STA:
    {
        uint8_t mac_ptr[] = {CIOT_CONFIG_WIFI_STA_MAC};
        memcpy(mac, mac_ptr, 6);
        break;
    }
    default:
        break;
    }
}

#endif
