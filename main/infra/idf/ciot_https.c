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

static ciot_err_t ciot_https_register_routes(ciot_https_t this);
static esp_err_t ciot_post_handler(httpd_req_t *req);

static const char *TAG = "ciot_https";

ciot_https_t ciot_https_new(void *handle)
{
    ciot_https_t this = calloc(1, sizeof(struct ciot_https));
    this->iface.base.ptr = this;
    this->iface.base.start = (ciot_iface_start_fn *)ciot_https_start;
    this->iface.base.stop = (ciot_iface_stop_fn *)ciot_https_stop;
    this->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_https_process_req;
    this->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_https_send_data;
    this->iface.base.cfg.ptr = &this->cfg;
    this->iface.base.cfg.size = sizeof(this->cfg);
    this->iface.base.status.ptr = &this->status;
    this->iface.base.status.size = sizeof(this->status);
    this->iface.info.type = CIOT_IFACE_TYPE_HTTP_SERVER;
    return this;
}

ciot_err_t ciot_https_start(ciot_https_t this, ciot_https_cfg_t *cfg)
{
    httpd_config_t http_config = HTTPD_DEFAULT_CONFIG();
    http_config.server_port = cfg->port;
    http_config.uri_match_fn = httpd_uri_match_wildcard;
    http_config.max_uri_handlers = 7;

    int err_code = httpd_start(&this->handle, &http_config);
    if (err_code == ESP_OK)
    {
        ESP_LOGI(TAG, "Server Started on port %d", cfg->port);
        ciot_https_register_routes(this);
    }

    return err_code;
}

ciot_err_t ciot_https_stop(ciot_https_t this)
{
    return httpd_stop(this->handle);
}

ciot_err_t ciot_https_process_req(ciot_https_t this, ciot_https_req_t *req)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_https_send_data(ciot_https_t this, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(this);
    CIOT_NULL_CHECK(data);
    CIOT_NULL_CHECK(this->req);
    httpd_resp_set_status(this->req, HTTPD_200);
    httpd_resp_set_type(this->req, HTTPD_TYPE_OCTET);
    httpd_resp_send(this->req, (const char*)data, size);
    this->req = NULL;
    return CIOT_OK;
}

static ciot_err_t ciot_https_register_routes(ciot_https_t this)
{
    httpd_uri_t ciot_post = {
        .uri = this->cfg.route,
        .handler = ciot_post_handler,
        .method = HTTP_POST,
        .user_ctx = this,
    };
    return httpd_register_uri_handler(this->handle, &ciot_post);
}

static esp_err_t ciot_post_handler(httpd_req_t *req)
{
    ciot_https_t this = req->user_ctx;
    ciot_iface_event_t event = { 0 };

    this->req = req;
    event.id = CIOT_IFACE_EVENT_DATA;
    event.size = req->content_len;
    httpd_req_recv(req, (char*)&event.msg, sizeof(event.msg));

    if(this->iface.event_handler != NULL)
    {
        this->iface.event_handler(this, &event, this->iface.event_args);
    }

    return CIOT_OK;
}
