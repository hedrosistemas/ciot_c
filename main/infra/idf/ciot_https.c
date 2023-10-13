/**
 * @file ciot_https.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_https.h"

ciot_https_t ciot_https_new(void *handle)
{
    return NULL;
}

ciot_err_t ciot_https_start(ciot_https_t this, ciot_https_cfg_t *cfg)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_https_stop(ciot_https_t this)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_https_process_req(ciot_https_t this, ciot_https_req_t *req)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_https_send_data(ciot_https_t this, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}
