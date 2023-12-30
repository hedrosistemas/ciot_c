/**
 * @file ciot_bridge.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <string.h>

#include "ciot_bridge.h"

struct ciot_bridge
{
    ciot_iface_t iface;
    ciot_bridge_cfg_t cfg;
    ciot_bridge_status_t status;
};

ciot_bridge_t ciot_bridge_new(void *handle)
{
    ciot_bridge_t self = calloc(1, sizeof(struct ciot_bridge));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_bridge_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_bridge_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_bridge_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_bridge_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_BRIDGE;
    return self;
}

ciot_err_t ciot_bridge_start(ciot_bridge_t self, ciot_bridge_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    memcpy(&self->cfg, cfg, sizeof(self->cfg));
    self->status.state = CIOT_BRIDGE_STATE_STARTED;
    return CIOT_OK;
}

ciot_err_t ciot_bridge_stop(ciot_bridge_t self)
{
    CIOT_NULL_CHECK(self);
    self->status.state = CIOT_BRIDGE_STATE_IDLE;
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_bridge_process_req(ciot_bridge_t self, ciot_bridge_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_bridge_send_data(ciot_bridge_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

int ciot_bridge_get_target_id(ciot_bridge_t self, uint8_t sender_id)
{
    if(self == NULL) return -1;
    if(self->status.state != CIOT_BRIDGE_STATE_STARTED) return -1;
    if(self->cfg.ifaces_id[0] == sender_id) return self->cfg.ifaces_id[1];
    if(self->cfg.ifaces_id[1] == sender_id) return self->cfg.ifaces_id[0];
    return -1;
}
