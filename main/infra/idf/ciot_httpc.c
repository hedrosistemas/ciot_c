/**
 * @file ciot_httpc.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ciot_httpc.h"

#include "esp_http_client.h"
#include "esp_log.h"

#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
#include "esp_crt_bundle.h"
#endif

struct ciot_httpc
{
    ciot_iface_t iface;
    ciot_httpc_cfg_t cfg;
    ciot_httpc_status_t status;
    esp_http_client_handle_t handle;
    ciot_httpc_req_send_t req;
};

static int ciot_httpc_event_handler(esp_http_client_event_handle_t evt);

static const char *TAG = "ciot_httpc";

ciot_httpc_t ciot_httpc_new(void *handle)
{
    ciot_httpc_t this = calloc(1, sizeof(struct ciot_httpc));
    this->iface.base.ptr = this;
    this->iface.base.start = (ciot_iface_start_fn *)ciot_httpc_start;
    this->iface.base.stop = (ciot_iface_stop_fn *)ciot_httpc_stop;
    this->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_httpc_process_req;
    this->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_httpc_send_data;
    this->iface.base.cfg.ptr = &this->cfg;
    this->iface.base.cfg.size = sizeof(this->cfg);
    this->iface.base.status.ptr = &this->status;
    this->iface.base.status.size = sizeof(this->status);
    this->iface.info.type = CIOT_IFACE_TYPE_HTTP_SERVER;
    return this;
}

ciot_err_t ciot_httpc_start(ciot_httpc_t this, ciot_httpc_cfg_t *cfg)
{
    if (this->status.state == CIOT_HTTPC_STATE_IDLE)
    {
        CIOT_NULL_CHECK(this);
        CIOT_NULL_CHECK(cfg);
        memcpy(&this->cfg, cfg, sizeof(this->cfg));
        esp_http_client_config_t req_cfg = {0};
        req_cfg.url = this->cfg.url;
        req_cfg.transport_type = this->cfg.transport;
        req_cfg.method = this->cfg.method;
        req_cfg.user_data = this;
        req_cfg.event_handler = ciot_httpc_event_handler;
        this->status.state = CIOT_HTTPC_STATE_CONNECTING;
#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
        if (this->cfg.transport == CIOT_HTTPC_TRANSPORT_SSL)
        {
            req_cfg.crt_bundle_attach = esp_crt_bundle_attach;
        }
        this->handle = esp_http_client_init(&req_cfg);
#endif
        return CIOT_OK;
    }
    else
    {
        return CIOT_ERR_INVALID_STATE;
    }
}

ciot_err_t ciot_httpc_stop(ciot_httpc_t this)
{
    return esp_http_client_cleanup(this->handle);
}

ciot_err_t ciot_httpc_process_req(ciot_httpc_t this, ciot_httpc_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_httpc_send_data(ciot_httpc_t this, uint8_t *data, int size)
{
    if (this->status.state == CIOT_HTTPC_STATE_STARTED)
    {
        esp_http_client_set_post_field(this->handle, (char*)data, size);
        esp_http_client_perform(this->handle);
    }
    return CIOT_ERR_NOT_IMPLEMENTED;
}

static void ciot_httpc_event_data(ciot_httpc_t this, ciot_iface_event_t *event, char *data, int size)
{
    event->id = CIOT_IFACE_EVENT_DATA;
    event->size = size;
    memcpy(&event->msg.data, data, size);
}

static int ciot_httpc_event_handler(esp_http_client_event_handle_t evt)
{
    ciot_httpc_t this = evt->user_data;
    ciot_iface_event_t event = {0};

    switch (evt->event_id)
    {
    case HTTP_EVENT_ERROR:
        ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
        this->status.state = CIOT_HTTPC_STATE_ERROR;
        event.id = CIOT_IFACE_EVENT_ERROR;
        event.msg.data.httpc.status = this->status;
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
        this->status.state = CIOT_HTTPC_STATE_CONNECTED;
        break;
    case HTTP_EVENT_HEADERS_SENT:
        ESP_LOGD(TAG, "HTTP_EVENT_HEADERS_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER");
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA");
        ciot_httpc_event_data(this, &event, evt->data, evt->data_len);
        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
        this->status.state = CIOT_HTTPC_STATE_IDLE;
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_DISCONNECTED");
        this->status.state = CIOT_HTTPC_STATE_IDLE;
        break;
    case HTTP_EVENT_REDIRECT:
        ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");

        break;
    default:
        break;
    }

    if(this->iface.event_handler != NULL)
    {
        this->iface.event_handler(this, &event, this->iface.event_args);
    }

    return ESP_OK;
}
