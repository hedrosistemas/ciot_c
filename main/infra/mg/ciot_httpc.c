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

#include <stdlib.h>
#include <string.h>
#include "ciot_httpc.h"
#include "mongoose.h"

typedef struct ciot_http_data_to_send
{
    char *data;
    int size;
} ciot_http_data_to_send_t;

struct ciot_httpc
{
    ciot_iface_t iface;
    ciot_httpc_cfg_t cfg;
    ciot_httpc_status_t status;
    struct mg_mgr *mgr;
    struct mg_connection *connection;
    ciot_http_data_to_send_t data_to_send;
};

static void ciot_httpc_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

static const char *ciot_httpc_get_method(ciot_httpc_method_t method);

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
    this->iface.info.type = CIOT_IFACE_TYPE_HTTP_CLIENT;
    this->mgr = handle;
    return this;
}

ciot_err_t ciot_httpc_start(ciot_httpc_t this, ciot_httpc_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(this);
    CIOT_ERR_NULL_CHECK(cfg);
    memcpy(&this->cfg, cfg, sizeof(this->cfg));
    return CIOT_OK;
}

ciot_err_t ciot_httpc_stop(ciot_httpc_t this)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_httpc_process_req(ciot_httpc_t this, ciot_httpc_req_t *req)
{
    // switch (req->id)
    // {
    // case CIOT_HTTPC_REQ_SEND_DATA:
    //     memcpy(&this->req, &req->data.send, sizeof(this->req));
    //     this->status.state = CIOT_HTTPC_STATE_CONNECTING;
    //     mg_http_connect(this->mgr, this->cfg.url, ciot_httpc_event_handler, this);
    //     break;
    // default:
    //     break;
    // }
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_httpc_send_data(ciot_httpc_t this, uint8_t *data, int size)
{
    if (this->status.state == CIOT_HTTPC_STATE_IDLE || this->status.state == CIOT_HTTPC_STATE_TIMEOUT)
    {
        //     memcpy(&this->req.cfg, &this->cfg, sizeof(this->req.cfg));
        //     memcpy(this->req.body, data, size);
        //     this->req.content_length = size;
        //     this->status.state = CIOT_HTTPC_STATE_CONNECTING;
        //     mg_http_connect(this->mgr, this->cfg.url, ciot_httpc_event_handler, this);
        //     return CIOT_OK;
    }
    else
    {
        return CIOT_ERR_BUSY;
    }
}

static void ciot_httpc_event_data(ciot_httpc_t this, ciot_iface_event_t *event, char *data, int size)
{
    event->id = CIOT_IFACE_EVENT_DATA;
    event->size = size;
    memcpy(&event->msg.data, data, size);
}

static void ciot_httpc_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_httpc_t this = fn_data;
    ciot_iface_event_t event = {0};
    mg_event_t mg_ev = ev;

    event.msg.type = CIOT_MSG_TYPE_EVENT;
    event.msg.iface = this->iface.info;

    switch (mg_ev)
    {
    case MG_EV_OPEN:
        this->status.state = CIOT_HTTPC_STATE_CONNECTING;
        *(uint64_t *)c->data = mg_millis() + this->cfg.timeout;
        break;
    case MG_EV_POLL:
        if (mg_millis() > *(uint64_t *)c->data && (c->is_connecting || c->is_resolving))
        {
            this->status.state = CIOT_HTTPC_STATE_TIMEOUT;
            event.msg.data.httpc.status = this->status;
            mg_error(c, "Connect timeout");
            if (this->data_to_send.data != NULL)
            {
                free(this->data_to_send.data);
                this->data_to_send.data = NULL;
            }
        }
        break;
    case MG_EV_CONNECT:
    {
        this->status.state = CIOT_HTTPC_STATE_CONNECTED;;
        struct mg_str host = mg_url_host(this->cfg.url);
        mg_printf(c,
                  "%s %s HTTP/1.0\r\n"
                  "Host: %.*s\r\n"
                  "Content-Type: octet-stream\r\n"
                  "Content-Length: %d\r\n"
                  "\r\n",
                  ciot_httpc_get_method(this->cfg.method), mg_url_uri(this->cfg.url), (int)host.len,
                  host.ptr, this->data_to_send.size);
        mg_send(c, this->data_to_send.data, this->data_to_send.size);
        break;
    }
    case MG_EV_HTTP_MSG:
    {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;
        ciot_httpc_event_data(this, &event, (char*)hm->body.ptr, (int)hm->body.len);
        break;
    }
    default:
        break;
    }

    if(this->iface.event_handler != NULL)
    {
        this->iface.event_handler(this, &event, this->iface.event_args);
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
