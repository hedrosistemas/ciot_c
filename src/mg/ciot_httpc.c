/**
 * @file ciot_httpc.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ciot_httpc.h"

#if CIOT_CONFIG_FEATURE_HTTPC && defined(CIOT_TARGET_MONGOOSE)

#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

typedef struct ciot_http_data_to_send
{
    uint8_t data[CIOT_CONFIG_MESSAGE_LEN];
    int size;
} ciot_http_data_to_send_t;

struct ciot_httpc
{
    ciot_iface_t iface;
    ciot_httpc_cfg_t cfg;
    ciot_httpc_status_t status;
    struct mg_mgr *mgr;
    ciot_http_data_to_send_t data_to_send;
};

static void ciot_httpc_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

static const char *ciot_httpc_get_method(ciot_httpc_method_t method);

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
    self->iface.info.type = CIOT_IFACE_TYPE_HTTP_CLIENT;
    self->mgr = handle;
    return self;
}

ciot_err_t ciot_httpc_start(ciot_httpc_t self, ciot_httpc_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    memcpy(&self->cfg, cfg, sizeof(self->cfg));
    ciot_iface_event_t iface_event = { 0 };
    iface_event.id = CIOT_IFACE_EVENT_STARTED;
    if (self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
    }
    return CIOT_OK;
}

ciot_err_t ciot_httpc_stop(ciot_httpc_t self)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_httpc_process_req(ciot_httpc_t self, ciot_httpc_req_t *req)
{
    // switch (req->type)
    // {
    // case CIOT_HTTPC_REQ_SEND_DATA:
    //     memcpy(&self->req, &req->data.send, sizeof(self->req));
    //     self->status.state = CIOT_HTTPC_STATE_CONNECTING;
    //     mg_http_connect(self->mgr, self->cfg.url, ciot_httpc_event_handler, self);
    //     break;
    // default:
    //     break;
    // }
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_httpc_send_data(ciot_httpc_t self, uint8_t *data, int size)
{
    if (self->status.state == CIOT_HTTPC_STATE_IDLE || self->status.state == CIOT_HTTPC_STATE_TIMEOUT)
    {
        self->status.state = CIOT_HTTPC_STATE_CONNECTING;
        self->data_to_send.size = size;
        memcpy(self->data_to_send.data, data, size);
        mg_http_connect(self->mgr, self->cfg.url, ciot_httpc_event_handler, self);
        return CIOT_OK;
    }
    else
    {
        return CIOT_ERR_BUSY;
    }
}

static void ciot_httpc_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_httpc_t self = fn_data;

    if(self == NULL) return;

    ciot_iface_event_t iface_event = {0};
    ciot_httpc_status_msg_t status_msg = {0};
    mg_event_t mg_event = ev;

    status_msg.header.iface = self->iface.info;
    iface_event.data = (ciot_iface_event_data_u*)&status_msg;
    iface_event.size = sizeof(status_msg);

    switch (mg_event)
    {
    case MG_EV_ERROR:
        CIOT_LOGD(TAG, "MG_EV_ERROR");
        // self->status.error = (int*)ev_data;
        self->status.state = CIOT_HTTPC_STATE_ERROR;
        status_msg.header.type = CIOT_MSG_TYPE_ERROR;
        status_msg.status = self->status;
        iface_event.id = CIOT_IFACE_EVENT_ERROR;
        break;
    case MG_EV_OPEN:
    {
        CIOT_LOGD(TAG, "MG_EV_OPEN url:%s", self->cfg.url);
        self->status.state = CIOT_HTTPC_STATE_CONNECTING;
        status_msg.header.type = CIOT_MSG_TYPE_EVENT;
        status_msg.status = self->status;
        iface_event.id = CIOT_HTTPC_EVENT_CONNECTING;
        *(uint64_t *)c->data = mg_millis() + self->cfg.timeout;
        break;
    }
    case MG_EV_POLL:
        // CIOT_LOGD(TAG, "MG_EV_POLL");
        if (mg_millis() > *(uint64_t *)c->data && (self->status.state != CIOT_HTTPC_STATE_IDLE))
        {
            mg_error(c, "Connect timeout");
            self->status.state = CIOT_HTTPC_STATE_TIMEOUT;
            status_msg.header.type = CIOT_MSG_TYPE_ERROR;
            status_msg.status = self->status;
            iface_event.id = CIOT_IFACE_EVENT_ERROR;
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
                  ciot_httpc_get_method(self->cfg.method), mg_url_uri(self->cfg.url), (int)host.len,
                  host.ptr, self->data_to_send.size);
             mg_send(c, self->data_to_send.data, self->data_to_send.size);
        self->status.state = CIOT_HTTPC_STATE_CONNECTED;
        status_msg.header.type = CIOT_MSG_TYPE_EVENT;
        status_msg.status = self->status;
        iface_event.id = CIOT_HTTPC_EVENT_CONNECTED;
        break;
    }
    case MG_EV_HTTP_MSG:
    {
        CIOT_LOGD(TAG, "MG_EV_HTTP_MSG");
        struct mg_http_message *hm = ev_data, tmp = {0};
        mg_http_parse((char *)c->recv.buf, c->recv.len, &tmp);
        self->status.state = CIOT_HTTPC_STATE_IDLE;
        iface_event.id = CIOT_IFACE_EVENT_REQUEST;
        iface_event.data = (ciot_iface_event_data_u*)hm->body.ptr;
        iface_event.size = c->recv.len;
        c->is_draining = 1;
        break;
    }
    case MG_EV_CLOSE:
    {
        CIOT_LOGD(TAG, "MG_EV_CLOSE");
        self->status.state = CIOT_HTTPC_STATE_IDLE;
        status_msg.header.type = CIOT_MSG_TYPE_STOP;
        status_msg.status = self->status;
        iface_event.id = CIOT_IFACE_EVENT_STOPPED;
        break;
    }
    default:
        return;
    }

    if (self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
    }
}

static const char *ciot_httpc_get_method(ciot_httpc_method_t method)
{
    switch (method)
    {
        case CIOT_HTTPC_METHOD_GET:
            return "GET";
        case CIOT_HTTPC_METHOD_POST:
            return "POST";
        case CIOT_HTTPC_METHOD_PUT:
            return "PUT";
        case CIOT_HTTPC_METHOD_PATCH:
            return "PATCH";
        case CIOT_HTTPC_METHOD_DELETE:
            return "DELETE";
        case CIOT_HTTPC_METHOD_HEAD:
            return "HEAD";
        case CIOT_HTTPC_METHOD_NOTIFY:
            return "NOTIFY";
        case CIOT_HTTPC_METHOD_SUBSCRIBE:
            return "SUBSCRIBE";
        case CIOT_HTTPC_METHOD_UNSUBSCRIBE:
            return "UNSUBSCRIBE";
        case CIOT_HTTPC_METHOD_OPTIONS:
            return "OPTIONS";
        case CIOT_HTTPC_METHOD_COPY:
            return "COPY";
        case CIOT_HTTPC_METHOD_MOVE:
            return "MOVE";
        case CIOT_HTTPC_METHOD_LOCK:
            return "LOCK";
        case CIOT_HTTPC_METHOD_UNLOCK:
            return "UNLOCK";
        case CIOT_HTTPC_METHOD_PROPFIND:
            return "PROPFIND";
        case CIOT_HTTPC_METHOD_PROPPATCH:
            return "PROPPATCH";
        case CIOT_HTTPC_METHOD_MKCOL:
            return "MKCOL";
        default:
            return "UNKNOWN"; // Tratar métodos desconhecidos
    }
}

#endif