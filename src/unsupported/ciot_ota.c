/**
 * @file ciot_ota.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-10-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ciot_ota.h"

#if CIOT_CONFIG_FEATURE_OTA && (defined(CIOT_TARGET_WIN) || defined(CIOT_TARGET_LINUX))

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ciot_tcp.h"

struct ciot_ota
{
    ciot_iface_t iface;
    ciot_tcp_t tcp;
    ciot_ota_cfg_t cfg;
    ciot_ota_status_t status;
};

ciot_ota_t ciot_ota_new(void *handle)
{
    ciot_ota_t self = calloc(1, sizeof(struct ciot_ota));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_ota_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_ota_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_ota_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_ota_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_OTA;
    return self;
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
