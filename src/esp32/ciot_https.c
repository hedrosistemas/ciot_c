/**
 * @file ciot_https.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_https.h"

#if CIOT_CONFIG_FEATURE_HTTPC && defined(CIOT_TARGET_ESP32)

#include "esp_log.h"
#include "esp_http_server.h"

struct ciot_https
{
    ciot_iface_t iface;
    ciot_https_cfg_t cfg;
    ciot_https_status_t status;
    httpd_handle_t handle;
    httpd_req_t *req;
};

static ciot_err_t ciot_https_register_routes(ciot_https_t self);
static esp_err_t ciot_post_handler(httpd_req_t *req);

static const char *TAG = "ciot_https";

ciot_https_t ciot_https_new(void *handle)
{
    ciot_https_t self = calloc(1, sizeof(struct ciot_https));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_https_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_https_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_https_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_https_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_HTTP_SERVER;
    return self;
}

ciot_err_t ciot_https_start(ciot_https_t self, ciot_https_cfg_t *cfg)
{
    httpd_config_t http_config = HTTPD_DEFAULT_CONFIG();
    http_config.server_port = cfg->port;
    http_config.uri_match_fn = httpd_uri_match_wildcard;
    http_config.max_uri_handlers = 7;

    int err_code = httpd_start(&self->handle, &http_config);
    if (err_code == ESP_OK)
    {
        ESP_LOGI(TAG, "Server Started on port %d", cfg->port);
        ciot_https_register_routes(self);
    }

    return err_code;
}

ciot_err_t ciot_https_stop(ciot_https_t self)
{
    return httpd_stop(self->handle);
}

ciot_err_t ciot_https_process_req(ciot_https_t self, ciot_https_req_t *req)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_https_send_data(ciot_https_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    CIOT_NULL_CHECK(self->req);
    httpd_resp_set_status(self->req, HTTPD_200);
    httpd_resp_set_type(self->req, HTTPD_TYPE_OCTET);
    httpd_resp_send(self->req, (const char*)data, size);
    self->req = NULL;
    return CIOT_OK;
}

static ciot_err_t ciot_https_register_routes(ciot_https_t self)
{
    httpd_uri_t ciot_post = {
        .uri = self->cfg.route,
        .handler = ciot_post_handler,
        .method = HTTP_POST,
        .user_ctx = self,
    };
    return httpd_register_uri_handler(self->handle, &ciot_post);
}

static esp_err_t ciot_post_handler(httpd_req_t *req)
{
    ciot_https_t self = (ciot_https_t)req->user_ctx;

    if(self == NULL) return 0;

    ciot_iface_event_t event = { 0 };
    ciot_msg_t msg;

    httpd_req_recv(req, (char*)&msg, event.size);

    self->req = req;
    event.id = CIOT_IFACE_EVENT_REQUEST;
    event.size = req->content_len;
    event.data = (ciot_iface_event_data_u*)&msg;

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &event, self->iface.event_args);
    }

    return CIOT_OK;
}

#endif
