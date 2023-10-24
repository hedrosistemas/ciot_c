/**
 * @file ciot_ntp.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <string.h>

#include "ciot_ntp.h"

struct ciot_ntp
{
    ciot_iface_t iface;
};

ciot_ntp_t ciot_ntp_new(void *handle)
{
    return NULL;
}

ciot_err_t ciot_ntp_start(ciot_ntp_t this, ciot_ntp_cfg_t *cfg)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ntp_stop(ciot_ntp_t this)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ntp_process_req(ciot_ntp_t this, ciot_ntp_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ntp_send_data(ciot_ntp_t this, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}
