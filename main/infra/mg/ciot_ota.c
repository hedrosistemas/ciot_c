/**
 * @file ciot_ota.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_ota.h"

#if CIOT_CONFIG_FEATURE_OTA

struct ciot_ota
{
    ciot_iface_t iface;
};

ciot_ota_t ciot_ota_new(void *handle)
{
    return NULL;
}

ciot_err_t ciot_ota_start(ciot_ota_t self, ciot_ota_cfg_t *cfg)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ota_stop(ciot_ota_t self)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ota_process_req(ciot_ota_t self, ciot_ota_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ota_send_data(ciot_ota_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

#endif
