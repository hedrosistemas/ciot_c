/**
 * @file ciot_tcp.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_tcp.h"

#if (CIOT_CONFIG_FEATURE_ETHERNET || CIOT_CONFIG_FEATURE_WIFI)  && (defined(CIOT_TARGET_WIN) || defined(CIOT_TARGET_LINUX))

#include <string.h>

struct ciot_tcp
{
    ciot_iface_t iface;
};

ciot_tcp_t ciot_tcp_new(ciot_tcp_handle_t *handle)
{
    return NULL;
}

ciot_err_t ciot_tcp_start(ciot_tcp_t self, ciot_tcp_cfg_t *cfg)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_tcp_stop(ciot_tcp_t self)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_tcp_process_req(ciot_tcp_t self, ciot_tcp_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_tcp_send_data(ciot_tcp_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

#endif