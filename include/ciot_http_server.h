/**
 * @file ciot_http_server.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_HTTP_SERVER__H__
#define __CIOT_HTTP_SERVER__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/http_server.pb-c.h"

#define CIOT_CONFIG_HTTP_SERVER_ENDPOINT_SIZE 64
#define CIOT_CONFIG_HTTP_SERVER_ROUTE_SIZE 64
#define CIOT_CONFIG_HTTP_SERVER_ROOT_SIZE 48

typedef struct ciot_http_server *ciot_http_server_t;
typedef Ciot__HttpServerData ciot_http_server_data_t;
typedef Ciot__HttpServerCfg ciot_http_server_cfg_t;
typedef Ciot__HttpServerReq ciot_http_server_req_t;
typedef Ciot__HttpServerStatus ciot_http_server_status_t;

typedef struct ciot_http_server_event_data
{
    char *uri;
    uint8_t *body;
} ciot_http_server_event_data_t;

typedef struct ciot_http_server_base
{
    ciot_iface_t iface;
    ciot_http_server_cfg_t cfg;
    ciot_http_server_status_t status;
    ciot_http_server_req_t req;
    ciot_http_server_data_t data;
    char endpoint[CIOT_CONFIG_HTTP_SERVER_ENDPOINT_SIZE];
    char route[CIOT_CONFIG_HTTP_SERVER_ROUTE_SIZE];
    char root[CIOT_CONFIG_HTTP_SERVER_ROOT_SIZE];
} ciot_http_server_base_t;

ciot_http_server_t ciot_http_server_new(void *handle);
ciot_err_t ciot_http_server_init(ciot_http_server_t self);
ciot_err_t ciot_http_server_start(ciot_http_server_t self, ciot_http_server_cfg_t *cfg);
ciot_err_t ciot_http_server_stop(ciot_http_server_t self);
ciot_err_t ciot_http_server_process_req(ciot_http_server_t self, ciot_http_server_req_t *req);
ciot_err_t ciot_http_server_get_cfg(ciot_http_server_t self, ciot_http_server_cfg_t *cfg);
ciot_err_t ciot_http_server_get_status(ciot_http_server_t self, ciot_http_server_status_t *status);
ciot_err_t ciot_http_server_send_bytes(ciot_http_server_t self, uint8_t *data, int size);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_HTTP_SERVER__H__
