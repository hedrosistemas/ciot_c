/**
 * @file ciot_storage.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "nvs_flash.h"
#include "ciot_storage.h"
#include "ciot_msg.h"

#define CIOT_STORAGE_NVS_NS "ciot"

static ciot_err_t ciot_storage_nvs_init();

static const char *TAG = "ciot_storage";
static bool nvs_init = false;

struct ciot_storage
{
    ciot_storage_base_t base;
};

ciot_storage_t ciot_storage_new(void *handle)
{
    ciot_storage_t self = calloc(1, sizeof(struct ciot_storage));
    ciot_storage_init(self);
    ciot_storage_nvs_init();
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
        case CIOT__STORAGE_TYPE__STORAGE_TYPE_FLASH:
            break;
        default:
            return CIOT_ERR__INVALID_TYPE;
    }

    if(ciot_storage_nvs_init() == CIOT_ERR__OK)
    {
        ciot_iface_event_t event;
        event.type = CIOT_IFACE_EVENT_STARTED;
        event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);
        return ciot_iface_send_event(&base->iface, &event);
    }
    else
    {
        return CIOT_ERR__FAIL;
    }
}

ciot_err_t ciot_storage_stop(ciot_storage_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_storage_write_bytes(ciot_storage_t self, char *path, uint8_t *data, int size)
{
    CIOT_ERR_STATE_CHECK(nvs_init, true);

    nvs_handle_t handle;
    CIOT_ERR_RETURN(nvs_open(CIOT_STORAGE_NVS_NS, NVS_READWRITE, &handle));

    esp_err_t err = nvs_set_blob(handle, path, data, size);
    if(err == ESP_OK)
    {
        err = nvs_commit(handle);
    }

    nvs_close(handle);
    return err;
}

ciot_err_t ciot_storage_read_bytes(ciot_storage_t self, char *path, uint8_t *data, int size)
{
    CIOT_ERR_STATE_CHECK(nvs_init, true);

    nvs_handle_t handle;
    CIOT_ERR_RETURN(nvs_open(CIOT_STORAGE_NVS_NS, NVS_READONLY, &handle));

    esp_err_t err = nvs_get_blob(handle, path, data, (size_t*)&size);
    if(err != ESP_OK)
    {
        return CIOT_ERR__FAIL;
    }

    return CIOT_ERR__OK;
}

ciot_err_t ciot_storage_delete(ciot_storage_t self, char *path)
{
    CIOT_ERR_STATE_CHECK(nvs_init, true);

    nvs_handle_t handle;
    CIOT_ERR_RETURN(nvs_open(CIOT_STORAGE_NVS_NS, NVS_READWRITE, &handle));

    esp_err_t err = nvs_erase_key(handle, path);
    if(err != ESP_OK)
    {
        nvs_close(handle);
        return CIOT_ERR__FAIL;
    }

    err = nvs_commit(handle);
    if(err != ESP_OK)
    {
        return CIOT_ERR__FAIL;
    }

    return CIOT_ERR__OK;
}

ciot_err_t ciot_storage_format(ciot_storage_t self)
{
    CIOT_ERR_STATE_CHECK(nvs_init, true);

    nvs_handle_t handle;
    esp_err_t err = nvs_open(CIOT_STORAGE_NVS_NS, NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        return CIOT_ERR__FAIL;
    }

    err = nvs_erase_all(handle);
    if (err != ESP_OK) {
        nvs_close(handle);
        return CIOT_ERR__FAIL;
    }

    err = nvs_commit(handle);
    nvs_close(handle);
    if (err != ESP_OK) {
        return CIOT_ERR__FAIL;
    }
    
    return CIOT_ERR__OK;
}

int ciot_storage_get_size(ciot_storage_t self, char *path)
{
    nvs_handle_t handle;
    esp_err_t err = nvs_open(CIOT_STORAGE_NVS_NS, NVS_READONLY, &handle);
    if (err != ESP_OK) {
        return 0;
    }

    int size;
    err = nvs_get_blob(handle, path, NULL, (size_t*)&size);
    if(err != ESP_OK)
    {
        return 0;
    }

    return size;
}

static ciot_err_t ciot_storage_nvs_init()
{
    if(nvs_init == false)
    {
        CIOT_LOGI(TAG, "Initializing nvs flash");
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
        {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }
        nvs_init = ret == ESP_OK;
        return ret;
    }
    else
    {
        return CIOT_ERR__OK;
    }
}
