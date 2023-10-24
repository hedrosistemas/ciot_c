/**
 * @file ciot_sys.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_sys.h"

ciot_sys_t ciot_sys_new(void *handle)
{
    return NULL;
}

ciot_err_t ciot_sys_start(ciot_sys_t this, ciot_sys_cfg_t *cfg)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_sys_stop(ciot_sys_t this)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_sys_process_req(ciot_sys_t this, ciot_sys_req_t *req)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_sys_send_data(ciot_sys_t this, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}
