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

static ciot_err_t ciot_storage_nvs_init();

static const char *TAG = "ciot_storage";
static bool nvs_init = false;

ciot_err_t ciot_storage_init(void)
{
    return ciot_storage_nvs_init();
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
