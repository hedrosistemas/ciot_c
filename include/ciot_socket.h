/**
 * @file ciot_socket.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_SOCKET__H__
#define __CIOT_SOCKET__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/socket.pb-c.h"

#define CIOT_CONFIG_TCP_SERVER_ENDPOINT_SIZE 64

typedef struct ciot_socket *ciot_socket_t;
typedef Ciot__SocketCfg ciot_socket_cfg_t;
typedef Ciot__SocketReq ciot_socket_req_t;
typedef Ciot__SocketStatus ciot_socket_status_t;
typedef Ciot__SocketInfo ciot_socket_info_t;
typedef Ciot__SocketReq ciot_socket_req_t;
typedef Ciot__SocketData ciot_socket_data_t;
typedef Ciot__SocketType ciot_socket_type_t;

typedef struct ciot_socket_base
{
    ciot_iface_t iface;
    ciot_socket_cfg_t cfg;
    ciot_socket_status_t status;
    ciot_socket_info_t info;
    ciot_socket_req_t req;
    ciot_socket_data_t data;
} ciot_socket_base_t;

ciot_socket_t ciot_socket_new(void *handle);
ciot_err_t ciot_socket_init(ciot_socket_t self);
ciot_err_t ciot_socket_start(ciot_socket_t self, ciot_socket_cfg_t *cfg);
ciot_err_t ciot_socket_stop(ciot_socket_t self);
ciot_err_t ciot_socket_process_req(ciot_socket_t self, ciot_socket_req_t *req);
ciot_err_t ciot_socket_get_cfg(ciot_socket_t self, ciot_socket_cfg_t *cfg);
ciot_err_t ciot_socket_get_status(ciot_socket_t self, ciot_socket_status_t *status);
ciot_err_t ciot_socket_get_info(ciot_socket_t self, ciot_socket_info_t *info);
ciot_err_t ciot_socket_send_bytes(ciot_socket_t self, uint8_t *data, int size);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_SOCKET__H__
