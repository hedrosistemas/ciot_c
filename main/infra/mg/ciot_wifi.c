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

#include <string.h>
#include <stdbool.h>

#include "ciot_wifi.h"
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
