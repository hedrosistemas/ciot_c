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
#include "ciot_config.h"

#if CIOT_CONFIG_FEATURE_STORAGE && defined(CIOT_TARGET_ESP32)

#include <stdlib.h>

#include "nvs_flash.h"

#include "esp_partition.h"

#include "ciot_storage.h"
#include "ciot_err.h"

#define CIOT_STORAGE_NVS_NAMESPACE "ciot"  

struct ciot_storage
{
    ciot_iface_t iface;
    ciot_storage_cfg_t cfg;
    ciot_storage_status_t status;
};

static const char *TAG = "ciot_storage";
static bool nvs_initialized = false;

static ciot_err_t ciot_storage_nvs_init();

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
        return ciot_storage_nvs_init();
    case CIOT_STORAGE_TYPE_FS:
        return CIOT_OK;
    }

    return CIOT_ERR_INVALID_TYPE;
}

ciot_err_t ciot_storage_stop(ciot_storage_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_storage_process_req(ciot_storage_t self, ciot_storage_req_t *req)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(req);

    switch (req->type)
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

ciot_err_t ciot_storage_save(ciot_storage_t self, char *path, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    if(nvs_initialized == false)
    {
        return CIOT_ERR_INVALID_STATE;
    }

    nvs_handle_t nvs_handle;
    CIOT_ERROR_RETURN(nvs_open(CIOT_STORAGE_NVS_NAMESPACE, NVS_READWRITE, &nvs_handle));

    esp_err_t err = nvs_set_blob(nvs_handle, path, data, size);
    if (err == ESP_OK) {
        err = nvs_commit(nvs_handle);
    }

    nvs_close(nvs_handle);
    return err;
}

ciot_err_t ciot_storage_load(ciot_storage_t self, char *path, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    if(nvs_initialized == false)
    {
        return CIOT_ERR_INVALID_STATE;
    }

    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(CIOT_STORAGE_NVS_NAMESPACE, NVS_READONLY, &nvs_handle);
    if(err != ESP_OK)
    {
        return err;
    }

    size_t required_size = size;
    err = nvs_get_blob(nvs_handle, path, data, &required_size);
    nvs_close(nvs_handle);
    return err;
}

ciot_err_t ciot_storage_delete(ciot_storage_t self, char *path)
{
    CIOT_NULL_CHECK(self);
    if(nvs_initialized == false)
    {
        return CIOT_ERR_INVALID_STATE;
    }

    nvs_handle_t nvs_handle;
    CIOT_ERROR_RETURN(nvs_open(CIOT_STORAGE_NVS_NAMESPACE, NVS_READWRITE, &nvs_handle));

    ciot_err_t err = nvs_erase_key(nvs_handle, path);
    if (err != ESP_OK) {
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_commit(nvs_handle);
    nvs_close(nvs_handle);
    return err;
}

ciot_err_t ciot_storage_format(ciot_storage_t self)
{
    CIOT_NULL_CHECK(self);
    
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(CIOT_STORAGE_NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK) {
        return err;
    }

    err = nvs_erase_all(nvs_handle);
    if (err != ESP_OK) {
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_commit(nvs_handle);
    nvs_close(nvs_handle);
    return err;
}

size_t ciot_storage_get_size(void)
{
    const esp_partition_t* partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "nvs");
    return partition->size;
}

static ciot_err_t ciot_storage_nvs_init()
{
    if(nvs_initialized == false)
    {
        CIOT_LOGI(TAG, "Initializing nvs flash");
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
        {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }
        nvs_initialized = ret == ESP_OK;
        return ret;
    }
    else
    {
        return CIOT_OK;
    }
}

#endif
