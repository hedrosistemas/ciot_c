/**
 * @file ciot_ota.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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

#include "ciot_ota.h"

#define CIOT_OTA_BUF_SIZE 1024

static const char *TAG = "ciot_ota";

static void ciot_ota_task(void *pvParameters);
static void ciot_ota_task_fatal_error(ciot_ota_t this);
static void ciot_ota_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

#ifdef CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
static ciot_err_t ciot_ota_validate_image_header(esp_app_desc_t *new_app_info);
static ciot_err_t ciot_ota_decrypt_cb(decrypt_cb_arg_t *args, void *user_ctx);
extern const char rsa_private_pem_start[] asm("_binary_private_pem_start");
extern const char rsa_private_pem_end[] asm("_binary_private_pem_end");
#endif // CONFIG_ESP_HTTPS_OTA_DECRYPT_CB

struct ciot_ota
{
    ciot_iface_t iface;
    ciot_ota_cfg_t cfg;
    ciot_ota_status_t status;
    esp_https_ota_handle_t handle;
    TaskHandle_t task;
    char *buffer;
};

ciot_ota_t ciot_ota_new(void *handle)
{
    ciot_ota_t this = calloc(1, sizeof(struct ciot_ota));
    this->iface.base.ptr = this;
    this->iface.base.start = (ciot_iface_start_fn *)ciot_ota_start;
    this->iface.base.stop = (ciot_iface_stop_fn *)ciot_ota_stop;
    this->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_ota_process_req;
    this->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_ota_send_data;
    this->iface.base.cfg.ptr = &this->cfg;
    this->iface.base.cfg.size = sizeof(this->cfg);
    this->iface.base.status.ptr = &this->status;
    this->iface.base.status.size = sizeof(this->status);
    this->iface.info.type = CIOT_IFACE_TYPE_OTA;
    return this;
}

ciot_err_t ciot_ota_start(ciot_ota_t this, ciot_ota_cfg_t *cfg)
{
    CIOT_NULL_CHECK(this);
    CIOT_NULL_CHECK(cfg);

#ifndef CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
    if (this->cfg.encrypted)
    {
        return CIOT_ERR_NOT_SUPPORTED;
    }
#endif // CONFIG_ESP_HTTPS_OTA_DECRYPT_CB

    if (this->status.state != CIOT_OTA_STATE_IDLE)
    {
        return CIOT_ERR_INVALID_STATE;
    }

    this->buffer = malloc(CIOT_OTA_BUF_SIZE);
    this->status.state = CIOT_OTA_STATE_INIT;
    this->status.error = CIOT_OK;

    ESP_ERROR_CHECK(esp_event_handler_register(ESP_HTTPS_OTA_EVENT, ESP_EVENT_ANY_ID, ciot_ota_event_handler, this));

    xTaskCreatePinnedToCore(
        ciot_ota_task,
        "ciot_ota_task",
        CIOT_CONFIG_OTA_TASK_STACK_SIZE,
        this,
        CIOT_CONFIG_OTA_TASK_TASK_PRIORITY,
        &this->task,
        CIOT_CONFIG_OTA_TASK_CORE_ID);
    return this->status.error;
}

ciot_err_t ciot_ota_stop(ciot_ota_t this)
{
    // CIOT_NULL_CHECK((*this));
    // vTaskDelete((*this)->task);
    // free((*this));
    // *this = NULL;
    // return CIOT_OK;
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_ota_process_req(ciot_ota_t this, ciot_ota_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ota_send_data(ciot_ota_t this, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

static void ciot_ota_task(void *pvParameters)
{
    ciot_ota_t this = (ciot_ota_t )pvParameters;

    ESP_LOGI(TAG, "OTA application start.");
    ESP_LOGI(TAG, "cfg: url:%s", this->cfg.url);

    esp_http_client_config_t http_client_config = {
        .url = (const char *)this->cfg.url,
#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
        .crt_bundle_attach = esp_crt_bundle_attach
#endif // CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
    };

    esp_https_ota_config_t ota_config = {
        .http_config = &http_client_config,
    };

#ifdef CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
    esp_decrypt_handle_t decrypt_handle = NULL;
    if (this->cfg.encrypted)
    {
        esp_decrypt_cfg_t decrypt_cfg = {};
        decrypt_cfg.rsa_pub_key = rsa_private_pem_start;
        decrypt_cfg.rsa_pub_key_len = rsa_private_pem_end - rsa_private_pem_start;

        decrypt_handle = esp_encrypted_img_decrypt_start(&decrypt_cfg);
        if (!decrypt_handle)
        {
            ESP_LOGI(TAG, "Failed to start decrypt");
            this->status.error = ESP_ERR_OTA_VALIDATE_FAILED;
            ciot_ota_task_fatal_error(this);
        }

        ota_config.decrypt_cb = ciot_ota_decrypt_cb;
        ota_config.decrypt_user_ctx = (void *)decrypt_handle;
    }
#endif // CONFIG_ESP_HTTPS_OTA_DECRYPT_CB

    this->handle = NULL;
    this->status.error = esp_https_ota_begin(&ota_config, &this->handle);
    if (this->status.error != ESP_OK)
    {
        ESP_LOGE(TAG, "ESP HTTPS OTA Begin failed!");
        ciot_ota_task_fatal_error(this);
    }

    while (1)
    {
        this->status.error = esp_https_ota_perform(this->handle);
        if (this->status.error != ESP_ERR_HTTPS_OTA_IN_PROGRESS)
        {
            break;
        }
    }

    if (!esp_https_ota_is_complete_data_received(this->handle))
    {
        ESP_LOGE(TAG, "Complete data was not received.");
    }
    else
    {
#ifdef CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
        if (this->cfg.encrypted && decrypt_handle != NULL)
        {
            this->status.error = esp_encrypted_img_decrypt_end(decrypt_handle);
            if (this->status.error != ESP_OK)
            {
                esp_https_ota_abort(this->handle);
                ESP_LOGE(TAG, "upgrade failed");
                ciot_ota_task_fatal_error(this);
                return;
            }
        }
#endif // CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
        this->status.error = esp_https_ota_finish(this->handle);
        if (this->status.error == ESP_OK && this->cfg.restart)
        {
            ESP_LOGI(TAG, "Prepare to restart system!");

            vTaskDelay(1000 / portTICK_PERIOD_MS);
            esp_restart();
        }
        if (this->status.error != ESP_OK)
        {
            ESP_LOGE(TAG, "ESP_HTTPS_OTA upgrade failed 0x%x", this->status.error);
            ciot_ota_task_fatal_error(this);
        }
    }

    // xEventGroupSetBits(this->event_group, ciot_OTA_EVENT_BIT_DONE);

    (void)vTaskDelete(NULL);
}

static void __attribute__((noreturn)) ciot_ota_task_fatal_error(ciot_ota_t this)
{
    ESP_LOGE(TAG, "Exiting task due to fatal error...");

    this->status.state = CIOT_OTA_STATE_ERROR;
    if(this->iface.event_handler != NULL)
    {
        ciot_iface_event_t event = { 0 };
        event.id = CIOT_IFACE_EVENT_ERROR;
        event.msg.type = CIOT_MSG_TYPE_EVENT;
        event.msg.iface = this->iface.info;
        event.msg.data.ota.status = this->status;
        this->iface.event_handler(this, &event, this->iface.event_args);
    }

    (void)vTaskDelete(NULL);

    while (1)
    {
        ;
    }
}

static void ciot_ota_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_ota_t this = (ciot_ota_t)arg;
    ciot_iface_event_t event = { 0 };

    event.msg.type = CIOT_MSG_TYPE_EVENT;
    event.msg.iface = this->iface.info;
    event.id = CIOT_OTA_EVENT_STATE_CHANGED;

    switch (event_id)
    {
        case ESP_HTTPS_OTA_START:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_START");
            this->status.state = CIOT_OTA_STATE_START;
            break;
        case ESP_HTTPS_OTA_CONNECTED:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_CONNECTED");
            this->status.state = CIOT_OTA_STATE_CONNECTED;
            break;
        case ESP_HTTPS_OTA_GET_IMG_DESC:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_GET_IMG_DESC");
            this->status.state = CIOT_OTA_STATE_CHECKING_DATA;
            break;
        case ESP_HTTPS_OTA_VERIFY_CHIP_ID:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_VERIFY_CHIP_ID");
            this->status.state = CIOT_OTA_STATE_CHECKING_DATA;
            break;
        case ESP_HTTPS_OTA_DECRYPT_CB:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_DECRYPT_CB");
            this->status.state = CIOT_OTA_STATE_DECRYPTING;
            break;
        case ESP_HTTPS_OTA_WRITE_FLASH:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_WRITE_FLASH");
            this->status.state = CIOT_OTA_STATE_FLASHING;
            this->status.image_size = esp_https_ota_get_image_size(this->handle);
            this->status.image_read = esp_https_ota_get_image_len_read(this->handle);
            break;
        case ESP_HTTPS_OTA_UPDATE_BOOT_PARTITION:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_UPDATE_BOOT_PARTITION");
            this->status.state = CIOT_OTA_STATE_UPDATE_BOOT_PARTITION;
            break;
        case ESP_HTTPS_OTA_FINISH:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_FINISH");
            this->status.state = CIOT_OTA_STATE_DONE;
            break;
        case ESP_HTTPS_OTA_ABORT:
            ESP_LOGI(TAG, "ESP_HTTPS_OTA_ABORT");
            this->status.state = CIOT_OTA_STATE_ERROR;
            break;
    default:
        break;
    }
    
    if(this->iface.event_handler != NULL)
    {
        this->iface.event_handler(this, &event, this->iface.event_args);
    }
}

#ifdef CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
static ciot_err_t ciot_ota_validate_image_header(esp_app_desc_t *new_app_info)
{
    esp_app_desc_t running_app_info;
    esp_app_desc_t invalid_app_info;

    const esp_partition_t *running_partition = esp_ota_get_running_partition();
    const esp_partition_t *last_invalid_partition = esp_ota_get_last_invalid_partition();

    esp_ota_get_partition_description(running_partition, &running_app_info);
    esp_ota_get_partition_description(last_invalid_partition, &invalid_app_info);

    bool version_is_invalid = memcmp(invalid_app_info.version, new_app_info->version, sizeof(new_app_info->version)) == 0;
    if (last_invalid_partition != NULL && version_is_invalid)
    {
        ESP_LOGE(TAG, "The received version is marked as invalid");
        return CIOT_ERR_INVALID_VERSION;
    }

    bool version_is_same = memcmp(new_app_info->version, running_app_info.version, sizeof(new_app_info->version)) == 0;
    if (version_is_same)
    {
        ESP_LOGE(TAG, "The received version is equal current version");
        return CIOT_ERR_SAME_VERSION;
    }

    return CIOT_ERR_OK;
}

static ciot_err_t ciot_ota_decrypt_cb(decrypt_cb_arg_t *args, void *user_ctx)
{
    if (args == NULL || user_ctx == NULL)
    {
        ESP_LOGE(TAG, "ciot_ota_app_decrypt_cb: Invalid argument");
        return ESP_ERR_INVALID_ARG;
    }

    ciot_err_t err;
    pre_enc_decrypt_arg_t pargs = {};

    pargs.data_in = args->data_in;
    pargs.data_in_len = args->data_in_len;

    err = esp_encrypted_img_decrypt_data((esp_decrypt_handle_t *)user_ctx, &pargs);
    if (err != CIOT_ERR_OK && err != ESP_ERR_NOT_FINISHED)
    {
        return err;
    }

    static bool image_header_was_checked = false;
    if (pargs.data_out_len > 0)
    {
        args->data_out = pargs.data_out;
        args->data_out_len = pargs.data_out_len;
        if (image_header_was_checked == false)
        {
            const int header_size = sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t);
            const int app_descr_size = sizeof(esp_app_desc_t);
            assert(args->data_out_len >= header_size + app_descr_size);

            esp_app_desc_t *app_info = (esp_app_desc_t *)&args->data_out[header_size];
            err = ciot_ota_validate_image_header(app_info);
            if (err != CIOT_ERR_OK)
            {
                free(pargs.data_out);
            }
            return err;
        }
    }
    else
    {
        args->data_out_len = 0;
    }

    return CIOT_ERR_OK;
}
#endif

