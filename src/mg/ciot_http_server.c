/**
 * @file ciot_http_server.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdlib.h>
#include "mongoose.h"
#include "ciot_http_server.h"
#include "ciot_err.h"
#include "ciot_log.h"

static const char *TAG = "ciot_http_server";

static void ciot_http_server_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

struct ciot_http_server
{
    ciot_http_server_base_t base;
    struct mg_mgr *mgr;
    struct mg_connection *conn_rx;
    struct mg_connection *conn_tx;
    char endpoint[CIOT_CONFIG_HTTP_SERVER_ENDPOINT_SIZE];
    char route[CIOT_CONFIG_HTTP_SERVER_ROUTE_SIZE];
};

ciot_http_server_t ciot_http_server_new(void *handle)
{
    ciot_http_server_t self = calloc(1, sizeof(struct ciot_http_server));
    ciot_http_server_init(self);
    self->mgr = handle;
    return self;
}

ciot_err_t ciot_http_server_start(ciot_http_server_t self, ciot_http_server_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    CIOT_ERR_NULL_CHECK(self->mgr);

    ciot_http_server_base_t *base = &self->base;

    sprintf(self->endpoint, "%s:%d", cfg->address, cfg->port);
    strcpy(self->route, cfg->route);

    base->cfg = *cfg;
    base->cfg.address = self->endpoint;
    base->cfg.route = self->route;

    self->conn_rx = mg_http_listen(self->mgr, self->endpoint, ciot_http_server_event_handler, self);
    if (self->conn_rx == NULL)
    {
        base->status.state = CIOT__HTTP_SERVER_STATE__HTTP_SERVER_STATE_ERROR;
        return CIOT_ERR__FAIL;
    }
    else
    {
        return CIOT_ERR__OK;
    }
}

ciot_err_t ciot_http_server_stop(ciot_http_server_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(self->conn_rx);
    mg_close_conn(self->conn_rx);
    return CIOT_ERR__OK;
}

ciot_err_t ciot_http_server_send_bytes(ciot_http_server_t self, uint8_t *data, int size)
{
    mg_printf(self->conn_tx,
              "HTTP/1.0 200 OK\r\n"
              "Content-Type: octet-stream\r\n"
              "Content-Length: %d\r\n\r\n",
              size);
    mg_send(self->conn_tx, data, size);
    return CIOT_ERR__OK;
}

static void ciot_http_server_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_http_server_t self = fn_data;
    ciot_http_server_base_t *base = &self->base;
    ciot_iface_event_t iface_event = {0};
    mg_event_t mg_ev = ev;

    switch (mg_ev)
    {
    case MG_EV_ERROR:
    {
        CIOT_LOGE(TAG, "MG_EV_ERROR (%s)", (char *)ev_data);
        base->status.state = CIOT__HTTP_SERVER_STATE__HTTP_SERVER_STATE_ERROR;
        iface_event.type = CIOT_IFACE_EVENT_ERROR;
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    }
    case MG_EV_OPEN:
    {
        CIOT_LOGI(TAG, "MG_EV_OPEN url:%s", base->cfg.address);
        base->status.state = CIOT__HTTP_SERVER_STATE__HTTP_SERVER_STATE_STARTED;
        iface_event.type = CIOT_IFACE_EVENT_STARTED;
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    }
    case MG_EV_CLOSE:
    {
        CIOT_LOGI(TAG, "MG_EV_CLOSE");
        base->status.state = CIOT__HTTP_SERVER_STATE__HTTP_SERVER_STATE_STOPPED;
        iface_event.type = CIOT_IFACE_EVENT_STOPPED;
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    }
    case MG_EV_HTTP_MSG:
    {
        CIOT_LOGI(TAG, "MG_EV_HTTP_MSG");
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;
        mg_http_parse((char *)c->recv.buf, c->recv.len, hm);
        bool is_post = strncmp(hm->method.ptr, "POST", hm->method.len) == 0;
        self->conn_tx = c;
        if (mg_http_match_uri(hm, base->cfg.route) && is_post)
        {
            iface_event.type = CIOT_IFACE_EVENT_REQUEST;
            iface_event.data = (uint8_t*)hm->body.ptr;
            iface_event.size = hm->body.len;
            ciot_iface_send_event(&base->iface, &iface_event);
        }
        else
        {
            ciot_http_server_event_data_t event_data = { 0 };
            event_data.uri = (char*)hm->uri.ptr;
            event_data.body = (uint8_t*)hm->body.ptr;
            iface_event.type = CIOT_IFACE_EVENT_DATA;
            iface_event.data = (uint8_t*)&event_data;
            iface_event.size = hm->body.len;
            ciot_iface_send_event(&base->iface, &iface_event);
        }
        break;
    }
    default:
        return;
    }
}
