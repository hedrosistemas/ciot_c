/**
 * @file ciot_socket.c
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
#include "ciot_socket.h"
#include "ciot_err.h"
#include "ciot_str.h"

// static const char *TAG = "ciot_socket";

struct ciot_socket
{
    ciot_socket_base_t base;
    struct mg_mgr *mgr;
    struct mg_connection *conn;
    struct mg_connection *resp_conn;
    char endpoint[CIOT_CONFIG_TCP_SERVER_ENDPOINT_SIZE];
};

static const char *TAG = "ciot_socket";

static void ciot_socket_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
static ciot_err_t ciot_socket_server_start(ciot_socket_t self);
static ciot_err_t ciot_socket_client_start(ciot_socket_t self);

ciot_socket_t ciot_socket_new(void *handle)
{
    ciot_socket_t self = calloc(1, sizeof(struct ciot_socket));
    ciot_socket_init(self);
    self->mgr = handle;
    return self;
}

ciot_err_t ciot_socket_start(ciot_socket_t self, ciot_socket_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    ciot_socket_base_t *base = &self->base;

    sprintf(self->endpoint, "%s:%ld", cfg->address, cfg->port);
    
    base->cfg = *cfg;
    base->cfg.address = self->endpoint;

    if(cfg->type == CIOT__SOCKET_TYPE__SOCKET_TYPE_TCP_SERVER)
    {
        return ciot_socket_server_start(self);
    }

    if(cfg->type == CIOT__SOCKET_TYPE__SOCKET_TYPE_TCP_CLIENT)
    {
        return ciot_socket_client_start(self);
    }

    return CIOT__ERR__OK;
}

ciot_err_t ciot_socket_stop(ciot_socket_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT__ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_socket_send_bytes(ciot_socket_t self, uint8_t *data, int size)
{
    CIOT_ERR_NULL_CHECK(self);
    struct mg_connection *conn = self->resp_conn ? self->resp_conn : self->conn;
    mg_send(conn, data, size);
    self->resp_conn = NULL;
    return CIOT__ERR__OK;
}

static ciot_err_t ciot_socket_server_start(ciot_socket_t self)
{
    ciot_socket_base_t *base = &self->base;

    self->conn = mg_listen(self->mgr, self->endpoint, ciot_socket_event_handler, self);
    if(self->conn == NULL)
    {
        base->status.state = CIOT__SOCKET_STATE__SOCKET_STATE_ERROR;
        return CIOT__ERR__FAIL;
    }
    return CIOT__ERR__OK;
}

static ciot_err_t ciot_socket_client_start(ciot_socket_t self)
{
    ciot_socket_base_t *base = &self->base;

    self->conn = mg_connect(self->mgr, self->endpoint, ciot_socket_event_handler, self);
    if(self->conn == NULL)
    {
        base->status.state = CIOT__SOCKET_STATE__SOCKET_STATE_ERROR;
        return CIOT__ERR__FAIL;
    }
    return CIOT__ERR__OK;
}

static void ciot_socket_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_socket_t self = fn_data;
    ciot_socket_base_t *base = &self->base;
    ciot_iface_event_t iface_event = {0};
    mg_event_t mg_ev = ev;

    switch (mg_ev)
    {
    case MG_EV_ERROR:
        CIOT_LOGE(TAG, "MG_EV_ERROR (%s)", (char *)ev_data);
        base->status.state = CIOT__SOCKET_STATE__SOCKET_STATE_ERROR;
        iface_event.type = CIOT_IFACE_EVENT_ERROR;
        ciot_iface_send_event(&base->iface, &iface_event);
        break;  
    case MG_EV_OPEN:
        CIOT_LOGI(TAG, "MG_EV_OPEN url:%s", base->cfg.address);
        base->status.state = CIOT__SOCKET_STATE__SOCKET_STATE_OPEN;
        iface_event.type = CIOT_IFACE_EVENT_STARTED;
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    case MG_EV_READ:
    {
        CIOT_LOGI(TAG, "MG_EV_READ");
        struct mg_iobuf *r = &c->recv;
        self->resp_conn = c;
        iface_event.type = CIOT_IFACE_EVENT_REQUEST;
        iface_event.data = r->buf;
        iface_event.size = r->len;
        ciot_iface_send_event(&base->iface, &iface_event);
        r->len = 0;
        break;
    }
    case MG_EV_CLOSE:
        CIOT_LOGI(TAG, "MG_EV_CLOSE");
        base->status.state = CIOT__SOCKET_STATE__SOCKET_STATE_CLOSED;
        iface_event.type = CIOT_IFACE_EVENT_STOPPED;
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    default:
        break;
    }
}
