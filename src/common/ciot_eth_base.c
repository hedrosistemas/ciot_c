/**
 * @file ciot_eth_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_eth.h"
#include "ciot_tcp.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_tcp";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_eth_init(ciot_eth_t self)
{
    ciot_eth_base_t *base = (ciot_eth_base_t*)self;

    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_ETH;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_eth_t self = (ciot_eth_t)iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_eth_start(self, req->data->eth->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_eth_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_eth_process_req(self, req->data->eth->request);
    default:
        break;
    }
    
    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_eth_base_t *self = (ciot_eth_base_t*)iface->ptr;
    ciot_tcp_base_t *base = (ciot_tcp_base_t*)self->tcp;

    base->data.config = NULL;
    base->data.status = NULL;
    base->data.info = NULL;
    base->data.request = NULL;

    switch (msg->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
        base->data.config = &base->cfg;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
        base->data.status = &base->status;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_INFO:
        base->data.info = &base->info;
        break;
    default:
        break;
    }

    self->iface.data.tcp = &base->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_eth_process_req(ciot_eth_t self, ciot_tcp_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR__NOT_IMPLEMENTED;
}
