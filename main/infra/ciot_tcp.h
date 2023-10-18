/**
 * @file ciot_tcp.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_TCP__H__
#define __CIOT_TCP__H__

#include "ciot_tcp_data.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef enum ciot_tcp_type
{
    CIOT_TCP_TYPE_UNKNOWN,
    CIOT_TCP_TYPE_WIFI_STA,
    CIOT_TCP_TYPE_WIFI_AP,
    CIOT_TCP_TYPE_ETHERNET,
} ciot_tcp_type_t;

typedef struct ciot_tcp_handle
{
    void *netif;
    ciot_tcp_cfg_t *cfg;
    ciot_tcp_status_t *status;
} ciot_tcp_handle_t;

typedef struct ciot_tcp *ciot_tcp_t;

ciot_err_t ciot_tcp_init(void);
ciot_tcp_t ciot_tcp_new(ciot_tcp_handle_t *handle);

ciot_err_t ciot_tcp_start(ciot_tcp_t this, ciot_tcp_cfg_t *cfg);
ciot_err_t ciot_tcp_stop(ciot_tcp_t this);
ciot_err_t ciot_tcp_process_req(ciot_tcp_t this, ciot_tcp_req_t *req);
ciot_err_t ciot_tcp_send_data(ciot_tcp_t this, uint8_t *data, int size);

ciot_err_t ciot_tcp_register_event(ciot_tcp_t tcp, ciot_iface_event_handler_t event_handler, void *event_args);

#endif  //!__CIOT_TCP__H__