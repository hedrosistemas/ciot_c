/**
 * @file ciot_storage.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "ciot_storage.h"
#include "ciot_err.h"
#include "ciot_msg.h"

// static const char *TAG = "ciot_storage";

struct ciot_storage
{
    ciot_storage_base_t base;
};

ciot_storage_t ciot_storage_new(void *handle)
{
    ciot_storage_t self = calloc(1, sizeof(struct ciot_storage));
    ciot_storage_init(self);
    return self;
}

ciot_err_t ciot_storage_start(ciot_storage_t self, ciot_storage_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    ciot_storage_base_t *base = &self->base;

    base->cfg = *cfg;

    switch (base->cfg.type)
    {
        case CIOT__STORAGE_TYPE__STORAGE_TYPE_FS:
            break;
        default:
            return CIOT_ERR__INVALID_TYPE;
    }

    ciot_iface_event_t event;
    event.type = CIOT_IFACE_EVENT_STARTED;
    event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);
    ciot_iface_send_event(&base->iface, &event);

    return CIOT_ERR__OK;
}

ciot_err_t ciot_storage_stop(ciot_storage_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_storage_save(ciot_storage_t self, char *path, uint8_t *data, int size)
{
    FILE *f = fopen(path, "wb");
    if(f != NULL)
    {
        fwrite(data, size, 1, f);
        fclose(f);
        return CIOT_ERR__OK;
    }

    return CIOT_ERR__FAIL;
}

ciot_err_t ciot_storage_load(ciot_storage_t self, char *path, uint8_t *data, int size)
{
    FILE *f = fopen(path, "rb");
    if(f != NULL)
    {
        fread(data, size, 1, f);
        fclose(f);
        return CIOT_ERR__OK;
    }

    return CIOT_ERR__FAIL;
}

ciot_err_t ciot_storage_delete(ciot_storage_t self, char *path)
{
    if(remove(path) == 0)
    {
        return CIOT_ERR__OK;
    }
    return CIOT_ERR__FAIL;
}

ciot_err_t ciot_storage_format(ciot_storage_t self)
{
    return CIOT_ERR__NOT_SUPPORTED;
}
