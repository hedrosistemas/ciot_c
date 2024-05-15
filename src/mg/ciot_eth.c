/**
 * @file ciot_eth.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_eth.h"

#if CIOT_CONFIG_FEATURE_ETHERNET && defined(CIOT_TARGET_PC)

#include <string.h>
#include "ciot_tcp.h"

struct ciot_eth
{
    ciot_iface_t iface;
};

static const char *TAG = "ciot_eth";

ciot_eth_t ciot_eth_new(void *handle)
{
    return NULL;
}

ciot_err_t ciot_eth_start(ciot_eth_t self, ciot_tcp_cfg_t *cfg)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_eth_stop(ciot_eth_t self)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_eth_process_req(ciot_eth_t self, ciot_tcp_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_eth_send_data(ciot_eth_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

#endif