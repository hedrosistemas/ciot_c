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
#include "esp_http_client.h"

struct ciot_httpc
{
    ciot_iface_t iface;
    ciot_httpc_cfg_t cfg;
    ciot_httpc_status_t status;
    esp_http_client_handle_t handle;
};

ciot_httpc_t ciot_httpc_new(void *handle)
{
    ciot_https_t this = calloc(1, sizeof(struct ciot_https));
    this->iface.base.ptr = this;
    this->iface.base.start = (ciot_iface_start_fn *)ciot_https_start;
    this->iface.base.stop = (ciot_iface_stop_fn *)ciot_https_stop;
    this->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_https_process_req;
    this->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_https_send_data;
    this->iface.base.cfg.ptr = &this->cfg;
    this->iface.base.cfg.size = sizeof(this->cfg);
    this->iface.base.status.ptr = &this->status;
    this->iface.base.status.size = sizeof(this->status);
    this->iface.info.type = CIOT_IFACE_TYPE_HTTP_SERVER;
    return this;
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
