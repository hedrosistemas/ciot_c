/**
 * @file ciot_tcp.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_TCP__H__
#define __CIOT_TCP__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/tcp.pb-c.h"

typedef struct ciot_tcp_netif *ciot_tcp_netif_t;
typedef struct ciot_tcp *ciot_tcp_t;
typedef Ciot__TcpCfg ciot_tcp_cfg_t;
typedef Ciot__TcpDhcpCfg ciot_tcp_dhcp_cfg_t;
typedef Ciot__TcpReq ciot_tcp_req_t;
typedef Ciot__TcpStatus ciot_tcp_status_t;
typedef Ciot__TcpDhcpStatus ciot_tcp_dhcp_status_t;
typedef Ciot__TcpInfo ciot_tcp_info_t;
typedef Ciot__TcpReq ciot_tcp_req_t;
typedef Ciot__TcpData ciot_tcp_data_t;

typedef enum ciot_tcp_type
{
    CIOT_TCP_TYPE_UNKNOWN,
    CIOT_TCP_TYPE_WIFI_STA,
    CIOT_TCP_TYPE_WIFI_AP,
    CIOT_TCP_TYPE_ETHERNET,
} ciot_tcp_type_t;

typedef struct ciot_tcp_base
{
    ciot_iface_t *iface_p;
    ciot_tcp_cfg_t cfg;
    ciot_tcp_status_t status;
    ciot_tcp_dhcp_status_t dhcp_status;
    ciot_tcp_info_t info;
    ciot_tcp_req_t req;
    ciot_tcp_data_t data;
    ciot_tcp_type_t type;
    uint8_t cfg_ip[4];
    uint8_t cfg_gateway[4];
    uint8_t cfg_mask[4];
    uint8_t cfg_dns[4];
    uint8_t info_ip[4];
    uint8_t info_mac[6];
    ciot_tcp_netif_t netif;
} ciot_tcp_base_t;

ciot_tcp_t ciot_tcp_new(ciot_iface_t *iface, ciot_tcp_type_t type);
ciot_err_t ciot_tcp_init(ciot_tcp_t self);
ciot_err_t ciot_tcp_init_netif(ciot_tcp_t self);
ciot_err_t ciot_tcp_start(ciot_tcp_t self);
ciot_err_t ciot_tcp_stop(ciot_tcp_t self);
ciot_err_t ciot_tcp_process_req(ciot_tcp_t self, ciot_tcp_req_t *req);
ciot_err_t ciot_tcp_set_cfg(ciot_tcp_t self, ciot_tcp_cfg_t *cfg);
ciot_err_t ciot_tcp_get_cfg(ciot_tcp_t self, ciot_tcp_cfg_t *cfg);
ciot_err_t ciot_tcp_get_status(ciot_tcp_t self, ciot_tcp_status_t *status);
ciot_err_t ciot_tcp_get_info(ciot_tcp_t self, ciot_tcp_info_t *info);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_TCP__H__
