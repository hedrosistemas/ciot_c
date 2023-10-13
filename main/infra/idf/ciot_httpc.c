/**
 * @file ciot_httpc.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_httpc.h"

ciot_httpc_t ciot_httpc_new(void *handle)
{
    return NULL;
}

ciot_err_t ciot_httpc_start(ciot_httpc_t this, ciot_httpc_cfg_t *cfg)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_httpc_stop(ciot_httpc_t this)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_httpc_process_req(ciot_httpc_t this, ciot_httpc_req_t *req)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_httpc_send_data(ciot_httpc_t this, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}
