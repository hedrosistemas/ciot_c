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

#if CIOT_CONFIG_FEATURE_HTTPC && defined(CIOT_TARGET_ESP)

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
    ciot_httpc_t self = calloc(1, sizeof(struct ciot_httpc));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_httpc_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_httpc_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_httpc_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_httpc_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_HTTP_SERVER;
    return self;
}

ciot_err_t ciot_httpc_start(ciot_httpc_t self, ciot_httpc_cfg_t *cfg)
{
    if (self->status.state == CIOT_HTTPC_STATE_IDLE)
    {
        CIOT_NULL_CHECK(self);
        CIOT_NULL_CHECK(cfg);
        memcpy(&self->cfg, cfg, sizeof(self->cfg));
        esp_http_client_config_t req_cfg = {0};
        req_cfg.url = self->cfg.url;
        req_cfg.transport_type = self->cfg.transport;
        req_cfg.method = self->cfg.method;
        req_cfg.user_data = self;
        req_cfg.event_handler = ciot_httpc_event_handler;
        self->status.state = CIOT_HTTPC_STATE_CONNECTING;
#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
        if (self->cfg.transport == CIOT_HTTPC_TRANSPORT_SSL)
        {
            req_cfg.crt_bundle_attach = esp_crt_bundle_attach;
        }
        self->handle = esp_http_client_init(&req_cfg);
#endif
        return CIOT_OK;
    }
    else
    {
        return CIOT_ERR_INVALID_STATE;
    }
}

ciot_err_t ciot_httpc_stop(ciot_httpc_t self)
{
    return esp_http_client_cleanup(self->handle);
}

ciot_err_t ciot_httpc_process_req(ciot_httpc_t self, ciot_httpc_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_httpc_send_data(ciot_httpc_t self, uint8_t *data, int size)
{
    if (self->status.state == CIOT_HTTPC_STATE_STARTED)
    {
        esp_http_client_set_post_field(self->handle, (char*)data, size);
        esp_http_client_perform(self->handle);
    }
    return CIOT_ERR_NOT_IMPLEMENTED;
}

static void ciot_httpc_event_data(ciot_httpc_t self, ciot_iface_event_t *event, char *data, int size)
{
    event->id = CIOT_IFACE_EVENT_DATA;
    event->size = size;
    memcpy(&event->msg.data, data, size);
}

static int ciot_httpc_event_handler(esp_http_client_event_handle_t evt)
{
    ciot_httpc_t self = evt->user_data;
    ciot_iface_event_t event = {0};

    switch (evt->event_id)
    {
    case HTTP_EVENT_ERROR:
        ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
        self->status.state = CIOT_HTTPC_STATE_ERROR;
        event.id = CIOT_IFACE_EVENT_ERROR;
        event.msg.data.httpc.status = self->status;
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
        self->status.state = CIOT_HTTPC_STATE_CONNECTED;
        break;
    case HTTP_EVENT_HEADERS_SENT:
        ESP_LOGD(TAG, "HTTP_EVENT_HEADERS_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER");
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA");
        ciot_httpc_event_data(self, &event, evt->data, evt->data_len);
        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
        self->status.state = CIOT_HTTPC_STATE_IDLE;
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_DISCONNECTED");
        self->status.state = CIOT_HTTPC_STATE_IDLE;
        break;
    case HTTP_EVENT_REDIRECT:
        ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");

        break;
    default:
        break;
    }

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &event, self->iface.event_args);
    }

    return ESP_OK;
}

#endif