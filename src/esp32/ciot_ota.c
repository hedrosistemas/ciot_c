/**
 * @file ciot_ota.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_ota.h"
#include "ciot_err.h"
#include "ciot_str.h"
#include "ciot_msg.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"

#ifdef CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
#include "esp_encrypted_img.h"
#endif // CONFIG_ESP_HTTPS_OTA_DECRYPT_CB

#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
#include "esp_crt_bundle.h"
#endif // CONFIG_MBEDTLS_CERTIFICATE_BUNDLE

static const char *TAG = "ciot_ota";

struct ciot_ota
{
    ciot_ota_base_t base;
    esp_https_ota_handle_t handle;
    TaskHandle_t task;
    char *buffer;
};

static void ciot_ota_task(void *pvParameters);
static void __attribute__((noreturn)) ciot_ota_task_fatal_error(ciot_ota_t self);
static void ciot_ota_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

ciot_ota_t ciot_ota_new(void *handle)
{
    ciot_ota_t self = calloc(1, sizeof(struct ciot_ota));
    ciot_ota_init(self);
    return self;
}

ciot_err_t ciot_ota_start(ciot_ota_t self, ciot_ota_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    ciot_ota_base_t *base = &self->base;

    #ifndef CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
    if (base->cfg.encrypted)
    {
        return CIOT__ERR__NOT_SUPPORTED;
    }
#endif // CONFIG_ESP_HTTPS_OTA_DECRYPT_CB

    if(base->status.state != CIOT__OTA_STATE__OTA_STATE_IDLE)
    {
        return CIOT__ERR__INVALID_STATE;
    }

    self->buffer = malloc(CIOT_CONFIG_OTA_BUF_SIZE);
    base->status.state = CIOT__OTA_STATE__OTA_STATE_INIT;
    base->status.error = CIOT__ERR__OK;
    base->cfg = *cfg;
    base->cfg.url = base->url;
    ciot_strncpy(base->url, cfg->url, CIOT_CONFIG_OTA_URL_LEN);

    ESP_ERROR_CHECK(esp_event_handler_register(ESP_HTTPS_OTA_EVENT, ESP_EVENT_ANY_ID, ciot_ota_event_handler, self));

    xTaskCreatePinnedToCore(
        ciot_ota_task,
        "ciot_ota_task",
        CIOT_CONFIG_OTA_TASK_STACK_SIZE,
        self,
        CIOT_CONFIG_OTA_TASK_PRIORITY,
        &self->task,
        CIOT_CONFIG_OTA_TASK_CORE_ID
    );

    return base->status.error;
}

ciot_err_t ciot_ota_stop(ciot_ota_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    vTaskDelete(self->task);
    free(self);
    return CIOT__ERR__OK;
}

ciot_err_t ciot_ota_rollback(ciot_ota_t self)
{
    if(esp_ota_check_rollback_is_possible())
    {
        return esp_ota_mark_app_invalid_rollback_and_reboot();
    }
    else
    {
        return CIOT__ERR__IMPOSSIBLE_OP;
    }
}

static void ciot_ota_task(void *pvParameters)
{
    ciot_ota_t self = (ciot_ota_t )pvParameters;
    ciot_ota_base_t *base = &self->base;

    ESP_LOGI(TAG, "OTA application start.");
    ESP_LOGI(TAG, "cfg: url:%s", base->cfg.url);

    esp_http_client_config_t http_client_config = {
        .url = (const char *)base->cfg.url,
#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
        .crt_bundle_attach = esp_crt_bundle_attach
#endif // CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
    };

    esp_https_ota_config_t ota_config = {
        .http_config = &http_client_config,
    };

#ifdef CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
    esp_decrypt_handle_t decrypt_handle = NULL;
    if (self->cfg.encrypted)
    {
        esp_decrypt_cfg_t decrypt_cfg = {};
        decrypt_cfg.rsa_pub_key = rsa_private_pem_start;
        decrypt_cfg.rsa_pub_key_len = rsa_private_pem_end - rsa_private_pem_start;

        decrypt_handle = esp_encrypted_img_decrypt_start(&decrypt_cfg);
        if (!decrypt_handle)
        {
            ESP_LOGI(TAG, "Failed to start decrypt");
            self->status.error = ESP_ERR_OTA_VALIDATE_FAILED;
            ciot_ota_task_fatal_error(self);
        }

        ota_config.decrypt_cb = ciot_ota_decrypt_cb;
        ota_config.decrypt_user_ctx = (void *)decrypt_handle;
    }
#endif // CONFIG_ESP_HTTPS_OTA_DECRYPT_CB

    self->handle = NULL;
    base->status.error = esp_https_ota_begin(&ota_config, &self->handle);
    if (base->status.error != ESP_OK)
    {
        ESP_LOGE(TAG, "ESP HTTPS OTA Begin failed!");
        ciot_iface_send_event_type(&self->base.iface, CIOT_IFACE_EVENT_ERROR);
        ciot_ota_task_fatal_error(self);
    }

    ciot_iface_send_event_type(&self->base.iface, CIOT_IFACE_EVENT_STARTED);

    while (1)
    {
        base->status.error = esp_https_ota_perform(self->handle);
        if (base->status.error != ESP_ERR_HTTPS_OTA_IN_PROGRESS)
        {
            break;
        }
    }

    if (!esp_https_ota_is_complete_data_received(self->handle))
    {
        ESP_LOGE(TAG, "Complete data was not received.");
    }
    else
    {
#ifdef CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
        if (self->cfg.encrypted && decrypt_handle != NULL)
        {
            self->status.error = esp_encrypted_img_decrypt_end(decrypt_handle);
            if (self->status.error != ESP_OK)
            {
                esp_https_ota_abort(self->handle);
                ESP_LOGE(TAG, "upgrade failed");
                ciot_ota_task_fatal_error(self);
                return;
            }
        }
#endif // CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
        base->status.error = esp_https_ota_finish(self->handle);
        if (base->status.error == ESP_OK && base->cfg.restart)
        {
            ESP_LOGI(TAG, "Prepare to restart system!");
            vTaskDelay(pdMS_TO_TICKS(1000));
            esp_restart();
        }
        if (base->status.error != ESP_OK)
        {
            ESP_LOGE(TAG, "ESP_HTTPS_OTA upgrade failed %ld", base->status.error);
            ciot_ota_task_fatal_error(self);
        }
    }
    
    (void)vTaskDelete(NULL);
}

static void __attribute__((noreturn)) ciot_ota_task_fatal_error(ciot_ota_t self)
{
    ESP_LOGE(TAG, "Exiting task due to fatal error...");

    ciot_ota_base_t *base = &self->base;

    base->status.state = CIOT__OTA_STATE__OTA_STATE_ERROR;
    ciot_iface_event_t event = { 0 };
    event.type = CIOT_IFACE_EVENT_ERROR;
    event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);
    ciot_iface_send_event(&base->iface, &event);

    (void)vTaskDelete(NULL);

    while (1)
    {
        ;
    }
}

static void ciot_ota_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_ota_t self = (ciot_ota_t)arg;
    ciot_ota_base_t *base = &self->base;
    ciot_ota_status_t *status = &base->status;
    ciot_iface_event_t event = { 0 };

    event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);

    switch (event_id)
    {
        case ESP_HTTPS_OTA_START:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_START");
            status->state = CIOT__OTA_STATE__OTA_STATE_START;
            event.type = CIOT_IFACE_EVENT_STARTED;
            break;
        case ESP_HTTPS_OTA_CONNECTED:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_CONNECTED");
            status->state = CIOT__OTA_STATE__OTA_STATE_CONNECTED;
            event.type = CIOT_IFACE_EVENT_INTERNAL;
            break;
        case ESP_HTTPS_OTA_GET_IMG_DESC:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_GET_IMG_DESC");
            status->state = CIOT__OTA_STATE__OTA_STATE_CHECKING_DATA;
            event.type = CIOT_IFACE_EVENT_INTERNAL;
            break;
        case ESP_HTTPS_OTA_VERIFY_CHIP_ID:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_VERIFY_CHIP_ID");
            status->state = CIOT__OTA_STATE__OTA_STATE_CHECKING_DATA;
            event.type = CIOT_IFACE_EVENT_INTERNAL;
            break;
        case ESP_HTTPS_OTA_DECRYPT_CB:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_DECRYPT_CB");
            status->state = CIOT__OTA_STATE__OTA_STATE_DECRYPTING;
            event.type = CIOT_IFACE_EVENT_INTERNAL;
            break;
        case ESP_HTTPS_OTA_WRITE_FLASH:
            status->state = CIOT__OTA_STATE__OTA_STATE_FLASHING;
            status->image_size = esp_https_ota_get_image_size(self->handle);
            status->image_written = esp_https_ota_get_image_len_read(self->handle);
            event.type = CIOT_IFACE_EVENT_INTERNAL;
            ESP_LOGD(TAG, "ESP_HTTPS_OTA_WRITE_FLASH %lu from %lu", status->image_written, status->image_size);
            break;
        case ESP_HTTPS_OTA_UPDATE_BOOT_PARTITION:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_UPDATE_BOOT_PARTITION");
            status->state = CIOT__OTA_STATE__OTA_STATE_UPDATE_BOOT_PARTITION;
            event.type = CIOT_IFACE_EVENT_INTERNAL;
            break;
        case ESP_HTTPS_OTA_FINISH:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_FINISH");
            status->state = CIOT__OTA_STATE__OTA_STATE_STATE_DONE;
            event.type = CIOT_IFACE_EVENT_DONE;
            break;
        case ESP_HTTPS_OTA_ABORT:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_ABORT");
            status->state = CIOT__OTA_STATE__OTA_STATE_ERROR;
            event.type = CIOT_IFACE_EVENT_ERROR;
            break;
    default:
        break;
    }

    ciot_iface_send_event(&base->iface, &event);
}
