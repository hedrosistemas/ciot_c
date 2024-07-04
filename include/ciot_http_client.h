/**
 * @file ciot_http_client.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_HTTP_CLIENT__H__
#define __CIOT_HTTP_CLIENT__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/http_client.pb-c.h"

#define CIOT_CONFIG_HTTP_CLIENT_URL_SIZE 64
#define CIOT_CONFIG_HTTP_CLIENT_BUF_SIZE 128

typedef struct ciot_http_client *ciot_http_client_t;
typedef Ciot__HttpClientCfg ciot_http_client_cfg_t;
typedef Ciot__HttpClientReq ciot_http_client_req_t;
typedef Ciot__HttpClientStatus ciot_http_client_status_t;
typedef Ciot__HttpClientReq ciot_http_client_req_t;
typedef Ciot__HttpClientData ciot_http_client_data_t;
typedef Ciot__HttpClientMethod ciot_http_client_method_t;

typedef struct ciot_http_client_base
{
    ciot_iface_t iface;
    ciot_http_client_cfg_t cfg;
    ciot_http_client_status_t status;
    ciot_http_client_req_t req;
    ciot_http_client_data_t data;
} ciot_http_client_base_t;

ciot_http_client_t ciot_http_client_new(void *handle);

ciot_err_t ciot_http_client_start(ciot_http_client_t self, ciot_http_client_cfg_t *cfg);
ciot_err_t ciot_http_client_stop(ciot_http_client_t self);
ciot_err_t ciot_http_client_process_req(ciot_http_client_t self, ciot_http_client_req_t *req);
ciot_err_t ciot_http_client_get_cfg(ciot_http_client_t self, ciot_http_client_cfg_t *cfg);
ciot_err_t ciot_http_client_get_status(ciot_http_client_t self, ciot_http_client_status_t *status);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_HTTP_CLIENT__H__
