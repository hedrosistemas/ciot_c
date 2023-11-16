/**
 * @file ciot_wifi.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_wifi.h"

#if CIOT_CONFIG_FEATURE_WIFI && defined(CIOT_TARGET_ESP8266)

#include "ciot_tcp.h"

struct ciot_wifi
{
    ciot_iface_t iface;
    ciot_tcp_t tcp;
    ciot_wifi_cfg_t cfg;
    ciot_wifi_status_u status;
};

ciot_err_t ciot_wifi_init(void)
{

}

ciot_wifi_t ciot_wifi_new(void *handle)
{

}

ciot_err_t ciot_wifi_start(ciot_wifi_t self, ciot_wifi_cfg_t *cfg)
{

}

ciot_err_t ciot_wifi_stop(ciot_wifi_t self)
{

}

ciot_err_t ciot_wifi_process_req(ciot_wifi_t self, ciot_wifi_req_t *req)
{

}

ciot_err_t ciot_wifi_send_data(ciot_wifi_t self, uint8_t *data, int size)
{

}

ciot_err_t ciot_wifi_get_mac(ciot_wifi_t self, ciot_wifi_type_t type, uint8_t mac[6])
{

}

#endif