/**
 * @file ciot_storage_nvs.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include "nvs_flash.h"
#include "ciot_storage_nvs.h"

#define CIOT_STORAGE_NVS_NS "ciot"

struct ciot_storage_nvs
{
    struct ciot_storage base;
};

typedef struct ciot_storage_nvs *ciot_storage_nvs_t;

static ciot_err_t ciot_storage_nvs_write_bytes(char *path, uint8_t *bytes, int size);
static ciot_err_t ciot_storage_nvs_read_bytes(char *path, uint8_t *bytes, int *size);
static ciot_err_t ciot_storage_nvs_init(void);

static const char *TAG = "ciot_storage_nvs";
static bool nvs_init = false;

ciot_storage_t ciot_storage_nvs_new(void)
{
    ciot_storage_nvs_t self = calloc(1, sizeof(struct ciot_storage_nvs));
    ciot_storage_t base = &self->base;
    base->write_bytes = ciot_storage_nvs_write_bytes;
    base->read_bytes = ciot_storage_nvs_read_bytes;
    ciot_storage_nvs_init();
    return &self->base;
}

static ciot_err_t ciot_storage_nvs_write_bytes(char *path, uint8_t *bytes, int size)
{
    CIOT_ERR_STATE_CHECK(nvs_init, true);

    nvs_handle_t handle;
    CIOT_ERR_RETURN(nvs_open(CIOT_STORAGE_NVS_NS, NVS_READWRITE, &handle));

    esp_err_t err = nvs_set_blob(handle, path, bytes, size);
    if(err == ESP_OK)
    {
        err = nvs_commit(handle);
    }

    nvs_close(handle);
    return err;
}

static ciot_err_t ciot_storage_nvs_read_bytes(char *path, uint8_t *bytes, int *size)
{
    CIOT_ERR_STATE_CHECK(nvs_init, true);

    nvs_handle_t handle;
    CIOT_ERR_RETURN(nvs_open(CIOT_STORAGE_NVS_NS, NVS_READONLY, &handle));

    esp_err_t err = nvs_get_blob(handle, path, bytes, (size_t*)size);
    if(err != ESP_OK)
    {
        return CIOT_ERR__FAIL;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_storage_nvs_init(void)
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
