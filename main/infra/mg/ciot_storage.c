/**
 * @file ciot_storage.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_storage.h"

#if CIOT_CONFIG_FEATURE_STORAGE && defined(CIOT_TARGET_PC)

#include <stdlib.h>
#include <stdio.h>

struct ciot_storage
{
    ciot_iface_t iface;
    ciot_storage_cfg_t cfg;
    ciot_storage_status_t status;
};

ciot_storage_t ciot_storage_new(void *handle)
{
    ciot_storage_t self = calloc(1, sizeof(struct ciot_storage));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_storage_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_storage_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_storage_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_storage_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(ciot_storage_status_t);
    self->iface.info.type = CIOT_IFACE_TYPE_STORAGE;
    return self;
}

ciot_err_t ciot_storage_start(ciot_storage_t self, ciot_storage_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);

    self->cfg = *cfg;

    switch (cfg->type)
    {
    case CIOT_STORAGE_TYPE_UNKNOWN:
        return CIOT_ERR_INVALID_TYPE;
    case CIOT_STORAGE_TYPE_EEPROM:
        return CIOT_ERR_NOT_SUPPORTED;
    case CIOT_STORAGE_TYPE_FLASH:
        return CIOT_ERR_NOT_SUPPORTED;
    case CIOT_STORAGE_TYPE_FS:
        return CIOT_OK;
    }

    return CIOT_ERR_INVALID_TYPE;
}

ciot_err_t ciot_storage_stop(ciot_storage_t self)
{
    CIOT_NULL_CHECK(self);
    return CIOT_OK;
}

ciot_err_t ciot_storage_process_req(ciot_storage_t self, ciot_storage_req_t *req)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(req);

    switch (req->id)
    {
    case CIOT_STORAGE_REQ_UNKNOWN:
        return CIOT_ERR_INVALID_ID;
    case CIOT_STORAGE_REQ_SAVE:
        return ciot_storage_save(self, req->data.save.path, req->data.save.data, req->data.save.size);
    case CIOT_STORAGE_REQ_LOAD:
        return ciot_storage_load(self, req->data.load.path, req->data.load.data, req->data.load.size);
    case CIOT_STORAGE_REQ_DELETE:
        return ciot_storage_delete(self, req->data.remove.path);
    case CIOT_STORAGE_REQ_FORMAT:
        return ciot_storage_format(self);
    }

    return CIOT_ERR_INVALID_ID;
}

ciot_err_t ciot_storage_send_data(ciot_storage_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_storage_save(ciot_storage_t self, char *path, uint8_t *data, uint8_t size)
{
    CIOT_NULL_CHECK(self);
    FILE *f = fopen(path, "wb");
    if(f != NULL) 
    {
        fwrite(data, size, 1, f);
        fclose(f);
        return CIOT_OK;
    }
    return CIOT_FAIL;
}

ciot_err_t ciot_storage_load(ciot_storage_t self, char *path, uint8_t *data, uint8_t size)
{
    CIOT_NULL_CHECK(self);
    FILE *f = fopen(path, "rb");
    if(f != NULL) 
    {
        fread(data, size, 1, f);
        fclose(f);
        return CIOT_OK;
    }
    return CIOT_FAIL;
}

ciot_err_t ciot_storage_delete(ciot_storage_t self, char *path)
{
    CIOT_NULL_CHECK(self);
    if(remove(path) == 0)
    {
        return CIOT_OK;
    }
    else
    {
        return CIOT_FAIL;
    }
}

ciot_err_t ciot_storage_format(ciot_storage_t self)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

#endif
