/**
 * @file ciot_https.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>

#include "mongoose.h"

#include "ciot_log.h"
#include "ciot_https.h"

typedef struct ciot_https_msg
{
    void *data;
    int size;
} ciot_https_msg_t;

struct ciot_https
{
    ciot_iface_t iface;
    ciot_https_cfg_t cfg;
    ciot_https_status_t status;
    struct mg_mgr *mgr;
    struct mg_connection *conn_rx;
    struct mg_connection *conn_tx;
};

static void ciot_https_event_handle(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

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
    self->mgr = handle;
    return self;
}

ciot_err_t ciot_https_start(ciot_https_t self, ciot_https_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    memcpy(&self->cfg, cfg, sizeof(self->cfg));
    self->conn_rx = mg_http_listen(self->mgr, cfg->address, ciot_https_event_handle, self);
    if (self->conn_rx == NULL)
    {
        self->status.state = CIOT_HTTPS_STATE_ERROR;
        return CIOT_FAIL;
    }
    else
    {
        self->status.state = CIOT_HTTPS_STATE_STARTED;
        return CIOT_OK;
    }
}

ciot_err_t ciot_https_stop(ciot_https_t self)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(self->conn_rx);
    mg_close_conn(self->conn_rx);
    self->status.state = CIOT_HTTPS_STATE_STOPPED;
    return CIOT_OK;
}

ciot_err_t ciot_https_process_req(ciot_https_t self, ciot_https_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_https_send_data(ciot_https_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    mg_printf(self->conn_tx, 
              "HTTP/1.0 200 OK\r\n"
              "Content-Type: octet-stream\r\n"
              "Content-Length: %d\r\n\r\n", size);
    mg_send(self->conn_tx, data, size);
    return CIOT_OK;
}

static void ciot_httpc_event_data(ciot_https_t self, ciot_iface_event_t *ciot_evt, struct mg_connection *c, struct mg_http_message *hm)
{
    bool is_post = strncmp(hm->method.ptr, "POST", hm->method.len) == 0;
    if (mg_http_match_uri(hm, self->cfg.route) && is_post)
    {
        ciot_evt->id = CIOT_IFACE_EVENT_DATA;
        memcpy(&ciot_evt->msg, hm->body.ptr, hm->body.len);
    }
    else
    {
        ciot_evt->id = CIOT_HTTPS_EVENT_DATA;
        ciot_evt->msg.iface = self->iface.info;
        ciot_evt->msg.type = CIOT_MSG_TYPE_UNKNOWN;
        ciot_evt->msg.data.https.msg.url = (char *)hm->uri.ptr;
        ciot_evt->msg.data.https.msg.method = (char *)hm->method.ptr;
        ciot_evt->msg.data.https.msg.data = (uint8_t *)hm->body.ptr;
        ciot_evt->msg.data.https.msg.size = hm->body.len;
        ciot_evt->size = CIOT_MSG_GET_SIZE(ciot_evt->msg.data.https.msg);
    }
    self->conn_tx = c;
    self->iface.event_handler(self, ciot_evt, self->iface.event_args);
}

static void ciot_https_event_handle(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_https_t self = fn_data;
    ciot_iface_event_t ciot_evt = {0};
    mg_event_t mg_ev = ev;

    ciot_evt.msg.type = CIOT_MSG_TYPE_EVENT;
    ciot_evt.msg.iface = self->iface.info;

    switch (mg_ev)
    {
    case MG_EV_ERROR:
        CIOT_LOGE(TAG, "MG_EV_ERROR:%d:%s", c->id, (char *)ev_data);
        self->status.state = CIOT_HTTPS_STATE_ERROR;
        self->status.error = c->id;
        ciot_evt.id = CIOT_IFACE_EVENT_ERROR;
        ciot_evt.msg.data.https.status = self->status;
    case MG_EV_OPEN:
        CIOT_LOGI(TAG, "MG_EV_OPEN", "");
        self->status.state = CIOT_HTTPS_STATE_STARTED;
        ciot_evt.id = CIOT_IFACE_EVENT_STARTED;
        ciot_evt.msg.data.https.status = self->status;
        break;
    case MG_EV_CLOSE:
        CIOT_LOGI(TAG, "MG_EV_CLOSE", "");
        self->status.state = CIOT_HTTPS_STATE_STOPPED;
        ciot_evt.id = CIOT_IFACE_EVENT_STOPPED;
        ciot_evt.msg.data.https.status = self->status;
        break;
    case MG_EV_HTTP_MSG:
    {
        CIOT_LOGI(TAG, "MG_EV_HTTP_MSG", "");
        struct mg_http_message *hm = (struct mg_http_message *)ev_data, tmp = {0};
        mg_http_parse((char*)c->recv.buf, c->recv.len, hm);
        ciot_httpc_event_data(self, &ciot_evt, c, hm);
        break;
    }
    default:
        break;
    }
    (void)fn_data;

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(self, &ciot_evt, self->iface.event_args);
    }
}
