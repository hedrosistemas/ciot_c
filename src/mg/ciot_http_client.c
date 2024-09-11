/**
 * @file ciot_http_client.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "mongoose.h"
#include "ciot_http_client.h"
#include "ciot_err.h"
#include "ciot_log.h"

static const char *TAG = "ciot_http_client";

struct ciot_http_client
{
    ciot_iface_t iface;
    ciot_http_client_cfg_t cfg;
    ciot_http_client_status_t status;
    char url[CIOT_CONFIG_HTTP_CLIENT_URL_SIZE];
    struct mg_mgr *mgr;
    uint8_t data[CIOT_CONFIG_HTTP_CLIENT_BUF_SIZE];
    int len;
};

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);
static void ciot_http_client_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
static const char *ciot_http_client_get_method(ciot_http_client_method_t method);

ciot_http_client_t ciot_http_client_new(void *handle)
{
    ciot_http_client_t self = calloc(1, sizeof(struct ciot_http_client));
    self->iface.ptr = self;
    self->iface.process_req = ciot_iface_process_req;
    self->iface.get_data = ciot_iface_get_data;
    self->iface.send_data = ciot_iface_send_data;
    self->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_HTTP_CLIENT;
    self->mgr = handle;
    return self;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_http_client_t self = iface->ptr;

    switch (req->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_START:
        return ciot_http_client_start(self, req->data->http_client->config);
    case CIOT__MSG_TYPE__MSG_TYPE_STOP:
        return ciot_http_client_stop(self);
    case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
        return ciot_http_client_process_req(self, req->data->http_client->request);
    default:
        break;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_http_client_t self = iface->ptr;

    switch (msg->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
        msg->data->http_client->config = &self->cfg;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
        msg->data->http_client->status = &self->status;
        break;
    default:
        return CIOT_ERR__NOT_FOUND;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    CIOT_ERR_NULL_CHECK(iface);
    CIOT_ERR_NULL_CHECK(data);

    ciot_http_client_t self = (ciot_http_client_t)iface->ptr;

    if (self->status.state == CIOT__HTTP_CLIENT_STATE__HTTP_CLIENT_STATE_IDLE ||
        self->status.state == CIOT__HTTP_CLIENT_STATE__HTTP_CLIENT_STATE_TIMEOUT)
    {
        self->status.state = CIOT__HTTP_CLIENT_STATE__HTTP_CLIENT_STATE_CONNECTING;
        self->len = size;
        memcpy(self->data, data, size);
        mg_http_connect(self->mgr, self->cfg.url, ciot_http_client_event_handler, self);
        return CIOT_ERR__OK;
    }
    else
    {
        return CIOT_ERR__BUSY;
    }
}

ciot_err_t ciot_http_client_start(ciot_http_client_t self, ciot_http_client_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    strcpy(self->url, cfg->url);
    self->cfg = *cfg;
    self->cfg.url = self->url;

    return CIOT_ERR__OK;
}

ciot_err_t ciot_http_client_stop(ciot_http_client_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT_ERR__OK;
}

ciot_err_t ciot_http_client_process_req(ciot_http_client_t self, ciot_http_client_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);

    switch (req->type)
    {
    case CIOT__HTTP_CLIENT_REQ_TYPE__HTTP_CLIENT_REQ_TYPE_UNKOWN:
        return CIOT_ERR__NOT_IMPLEMENTED;
    case CIOT__HTTP_CLIENT_REQ_TYPE__HTTP_CLIENT_REQ_SEND_DATA:
        return CIOT_ERR__NOT_IMPLEMENTED;
    case CIOT__HTTP_CLIENT_REQ_TYPE__HTTP_CLIENT_REQ_SET_HEADER:
        return CIOT_ERR__NOT_IMPLEMENTED;
    default:
        break;
    }

    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_http_client_get_cfg(ciot_http_client_t self, ciot_http_client_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    *cfg = self->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_http_client_get_status(ciot_http_client_t self, ciot_http_client_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    *status = self->status;
    return CIOT_ERR__NOT_IMPLEMENTED;
}

static void ciot_http_client_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_http_client_t self = fn_data;
    // ciot_http_client_base_t *base = &self->base;
    ciot_iface_event_t iface_event = {0};
    mg_event_t mg_ev = ev;
    // iface_event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);

    switch (mg_ev)
    {
    case MG_EV_ERROR:
        CIOT_LOGE(TAG, "MG_EV_ERROR (%s)", (char *)ev_data);
        self->status.state = CIOT__HTTP_CLIENT_STATE__HTTP_CLIENT_STATE_ERROR;
        iface_event.type = CIOT_IFACE_EVENT_ERROR;
        ciot_iface_send_event(&self->iface, &iface_event);
        break;
    case MG_EV_OPEN:
    {
        CIOT_LOGD(TAG, "MG_EV_OPEN url:%s", self->cfg.url);
        *(uint64_t *)c->data = mg_millis() + self->cfg.timeout;
        self->status.state = CIOT__HTTP_CLIENT_STATE__HTTP_CLIENT_STATE_CONNECTING;
        iface_event.type = CIOT_IFACE_EVENT_INTERNAL;
        ciot_iface_send_event(&self->iface, &iface_event);
        break;
    }
    case MG_EV_POLL:
        CIOT_LOGD(TAG, "MG_EV_POLL");
        if (mg_millis() > *(uint64_t *)c->data && (self->status.state != CIOT__HTTP_CLIENT_STATE__HTTP_CLIENT_STATE_IDLE))
        {
            mg_error(c, "Connect timeout");
            self->status.state = CIOT__HTTP_CLIENT_STATE__HTTP_CLIENT_STATE_TIMEOUT;
            iface_event.type = CIOT_IFACE_EVENT_ERROR;
            ciot_iface_send_event(&self->iface, &iface_event);
        }
        else
        {
            return;
        }
        break;
    case MG_EV_CONNECT:
    {
        CIOT_LOGD(TAG, "MG_EV_CONNECT");
        struct mg_str host = mg_url_host(self->cfg.url);
        mg_printf(c,
                  "%s %s HTTP/1.0\r\n"
                  "Host: %.*s\r\n"
                  "Content-Type: octet-stream\r\n"
                  "Content-Length: %d\r\n"
                  "\r\n",
                  ciot_http_client_get_method(self->cfg.method), mg_url_uri(self->cfg.url), (int)host.len,
                  host.ptr, self->len);
        mg_send(c, self->data, self->len);
        self->status.state = CIOT__HTTP_CLIENT_STATE__HTTP_CLIENT_STATE_CONNECTED;
        iface_event.type = CIOT_IFACE_EVENT_INTERNAL;
        ciot_iface_send_event(&self->iface, &iface_event);
        break;
    }
    case MG_EV_HTTP_MSG:
    {
        CIOT_LOGD(TAG, "MG_EV_HTTP_MSG");
        struct mg_http_message *hm = ev_data, tmp = {0};
        mg_http_parse((char *)c->recv.buf, c->recv.len, &tmp);
        c->is_draining = 1;
        self->status.state = CIOT__HTTP_CLIENT_STATE__HTTP_CLIENT_STATE_IDLE;
        iface_event.type = CIOT_IFACE_EVENT_DATA;
        iface_event.data = (uint8_t*)hm->body.ptr;
        iface_event.size = hm->body.len;
        ciot_iface_send_event(&self->iface, &iface_event);
        break;
    }
    case MG_EV_CLOSE:
    {
        CIOT_LOGD(TAG, "MG_EV_CLOSE");
        self->status.state = CIOT__HTTP_CLIENT_STATE__HTTP_CLIENT_STATE_IDLE;
        iface_event.type = CIOT_IFACE_EVENT_STOPPED;
        ciot_iface_send_event(&self->iface, &iface_event);
        break;
    }
    default:
        return;
    }
}

static const char *ciot_http_client_get_method(ciot_http_client_method_t method)
{
    switch (method)
    {
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_GET:
        return "GET";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_POST:
        return "POST";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_PUT:
        return "PUT";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_PATCH:
        return "PATCH";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_DELETE:
        return "DELETE";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_HEAD:
        return "HEAD";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_NOTIFY:
        return "NOTIFY";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_SUBSCRIBE:
        return "SUBSCRIBE";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_UNSUBSCRIBE:
        return "UNSUBSCRIBE";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_OPTIONS:
        return "OPTIONS";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_COPY:
        return "COPY";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_MOVE:
        return "MOVE";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_LOCK:
        return "LOCK";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_UNLOCK:
        return "UNLOCK";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_PROPFIND:
        return "PROPFIND";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_PROPPATCH:
        return "PROPPATCH";
    case CIOT__HTTP_CLIENT_METHOD__HTTP_METHOD_MKCOL:
        return "MKCOL";
    default:
        return "UNKNOWN"; // Tratar métodos desconhecidos
    }
}
