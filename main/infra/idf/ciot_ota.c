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
#endif

#include "ciot_ota.h"

static const char *TAG = "hg_ota";

static void hg_ota_task(void *pvParameters);
static void hg_ota_task_fatal_error(hg_ota_t ota);
static void hg_ota_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

#ifdef CONFIG_ESP_HTTPS_OTA_DECRYPT_CB
static hg_err_t hg_ota_validate_image_header(esp_app_desc_t *new_app_info);
static hg_err_t hg_ota_decrypt_cb(decrypt_cb_arg_t *args, void *user_ctx);
extern const char rsa_private_pem_start[] asm("_binary_private_pem_start");
extern const char rsa_private_pem_end[] asm("_binary_private_pem_end");
#endif // CONFIG_ESP_HTTPS_OTA_DECRYPT_CB

struct ciot_ota
{
    ciot_iface_t iface;
    ciot_ota_cfg_t cfg;
    ciot_ota_status_t status;
    char *buffer;
    esp_https_ota_handle_t handle;
};

ciot_ota_t ciot_ota_new(void *handle)
{

}

ciot_err_t ciot_ota_start(ciot_ota_t this, ciot_ota_cfg_t *cfg)
{

}

ciot_err_t ciot_ota_stop(ciot_ota_t this)
{

}

ciot_err_t ciot_ota_process_req(ciot_ota_t this, ciot_ota_req_t *req)
{

}

ciot_err_t ciot_ota_send_data(ciot_ota_t this, uint8_t *data, int size)
{

}
