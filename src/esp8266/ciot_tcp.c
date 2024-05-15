/**
 * @file ciot_tcp.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <string.h>

#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "lwip/ip4_addr.h"
#include "lwip/ip_addr.h"

#include "ciot_tcp.h"

#if (CIOT_CONFIG_FEATURE_ETHERNET || CIOT_CONFIG_FEATURE_WIFI) && defined(CIOT_TARGET_ESP8266)

struct ciot_tcp
{
    ciot_iface_t iface;
    tcpip_adapter_if_t netif;
    ciot_tcp_type_t type;
};

static const char *TAG = "ciot_tcp";

static ciot_err_t ciot_tcp_set_dhcp_cfg(ciot_tcp_t self, ciot_tcp_dhcp_cfg_t dhcp);
static ciot_err_t ciot_tcp_set_ip_cfg(ciot_tcp_t self, ciot_tcp_cfg_t *cfg);
static void ciot_tcp_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data);

ciot_err_t ciot_tcp_init(void)
{
    return esp_netif_init();
}

ciot_tcp_t ciot_tcp_new(ciot_tcp_handle_t *handle)
{
    ciot_tcp_t self = calloc(1, sizeof(struct ciot_tcp));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_tcp_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_tcp_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_tcp_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_tcp_send_data;
    self->iface.base.cfg.ptr = handle->cfg;
    self->iface.base.cfg.size = sizeof(*handle->cfg);
    self->iface.base.status.ptr = handle->status;
    self->iface.base.status.size = sizeof(*handle->status);
    self->iface.info.type = CIOT_IFACE_TYPE_TCP;
    self->netif = handle->netif;
    return self;
}

ciot_err_t ciot_tcp_start(ciot_tcp_t self, ciot_tcp_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    memcpy(self->iface.base.cfg.ptr, cfg, self->iface.base.cfg.size);
    CIOT_ERROR_RETURN(ciot_tcp_set_dhcp_cfg(self, cfg->dhcp));
    CIOT_ERROR_RETURN(ciot_tcp_set_ip_cfg(self, cfg));
    return CIOT_OK;
}

ciot_err_t ciot_tcp_stop(ciot_tcp_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_tcp_process_req(ciot_tcp_t self, ciot_tcp_req_t *req)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_tcp_send_data(ciot_tcp_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_tcp_register_event(ciot_tcp_t tcp, ciot_iface_event_handler_t event_handler, void *event_args)
{
    CIOT_NULL_CHECK(tcp);
    tcp->iface.event_args = event_args;
    tcp->iface.event_handler = event_handler;
    return esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, ciot_tcp_event_handler, tcp);
}

static ciot_err_t ciot_tcp_set_dhcp_cfg(ciot_tcp_t self, ciot_tcp_dhcp_cfg_t dhcp)
{
    CIOT_NULL_CHECK(self);

    tcpip_adapter_dhcp_status_t dhcpc = TCPIP_ADAPTER_DHCP_STOPPED;
    tcpip_adapter_dhcp_status_t dhcps = TCPIP_ADAPTER_DHCP_STOPPED;

    CIOT_ERROR_PRINT(tcpip_adapter_dhcpc_get_status(self->netif, &dhcpc));
    CIOT_ERROR_PRINT(tcpip_adapter_dhcps_get_status(self->netif, &dhcps));

    switch (dhcp)
    {
    case CIOT_TCP_DHCP_CFG_NO_CHANGE:
        ESP_LOGI(TAG, "CIOT_TCP_DHCP_CFG_NO_CHANGE");
        return CIOT_OK;
    case CIOT_TCP_DHCP_CFG_CLIENT:
        ESP_LOGI(TAG, "CIOT_TCP_DHCP_CFG_CLIENT");
        if (dhcps != TCPIP_ADAPTER_DHCP_STOPPED)
        {
            CIOT_ERROR_RETURN(tcpip_adapter_dhcps_stop(self->netif));
        }
        if (dhcpc != TCPIP_ADAPTER_DHCP_STARTED)
        {
            CIOT_ERROR_RETURN(tcpip_adapter_dhcpc_stop(self->netif));
        }
        break;
    case CIOT_TCP_DHCP_CFG_SERVER:
        ESP_LOGI(TAG, "CIOT_TCP_DHCP_CFG_SERVER");
        if (dhcpc != TCPIP_ADAPTER_DHCP_STOPPED)
        {
            CIOT_ERROR_RETURN(tcpip_adapter_dhcpc_stop(self->netif));
        }
        if (dhcps != TCPIP_ADAPTER_DHCP_STARTED)
        {
            CIOT_ERROR_RETURN(tcpip_adapter_dhcps_start(self->netif));
        }
        break;
    case CIOT_TCP_DHCP_CFG_DISABLED:
        ESP_LOGI(TAG, "CIOT_TCP_DHCP_CFG_DISABLED");
        if (dhcpc != TCPIP_ADAPTER_DHCP_STOPPED)
        {
            CIOT_ERROR_RETURN(tcpip_adapter_dhcpc_stop(self->netif));
        }
        if (dhcps != TCPIP_ADAPTER_DHCP_STOPPED)
        {
            CIOT_ERROR_RETURN(tcpip_adapter_dhcps_stop(self->netif));
        }
        break;
    default:
        return CIOT_ERR_INVALID_ARG;
    }
    return CIOT_OK;
}

static ciot_err_t ciot_tcp_set_ip_cfg(ciot_tcp_t self, ciot_tcp_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);

    if (cfg->dhcp == CIOT_TCP_DHCP_CFG_DISABLED)
    {
        ESP_LOGI(TAG, "cfg:cfg: cfg:%d.%d.%d.%d gw:%d.%d.%d.%d mask:%d.%d.%d.%d dns:%d.%d.%d.%d",
                 cfg->ip[0], cfg->ip[1], cfg->ip[2], cfg->ip[3],
                 cfg->gateway[0], cfg->gateway[1], cfg->gateway[2], cfg->gateway[3],
                 cfg->mask[0], cfg->mask[1], cfg->mask[2], cfg->mask[3],
                 cfg->dns[0], cfg->dns[1], cfg->dns[2], cfg->dns[3]);

        char ip[16];
        char gateway[16];
        char mask[16];
        char dns[16];

        tcpip_adapter_ip_info_t ip_info;
        tcpip_adapter_dns_info_t dns_info;

        sprintf(ip, "%d.%d.%d.%d", cfg->ip[0], cfg->ip[1], cfg->ip[2], cfg->ip[3]);
        sprintf(gateway, "%d.%d.%d.%d", cfg->gateway[0], cfg->gateway[1], cfg->gateway[2], cfg->gateway[3]);
        sprintf(mask, "%d.%d.%d.%d", cfg->mask[0], cfg->mask[1], cfg->mask[2], cfg->mask[3]);
        sprintf(dns, "%d.%d.%d.%d", cfg->dns[0], cfg->dns[1], cfg->dns[2], cfg->dns[3]);

        ip_info.ip.addr = ipaddr_addr(ip);
        ip_info.gw.addr = ipaddr_addr(gateway);
        ip_info.netmask.addr = ipaddr_addr(mask);
        dns_info.ip.addr = ipaddr_addr(mask);

        CIOT_ERROR_RETURN(tcpip_adapter_set_ip_info(self->netif, &ip_info));
        CIOT_ERROR_RETURN(tcpip_adapter_set_dns_info(self->netif, TCPIP_ADAPTER_DNS_MAIN, &dns_info));
    }
    return CIOT_OK;
}

static void ciot_tcp_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_tcp_t self = (ciot_tcp_t)handler_args;
    ciot_tcp_status_t *status = (ciot_tcp_status_t*)self->iface.base.status.ptr;
    
    ciot_iface_event_t iface_event = {0};
    ciot_tcp_status_msg_t status_msg = {0};

    status_msg.header.iface = self->iface.info;
    iface_event.data = (ciot_iface_event_data_u*)&status_msg;
    iface_event.size = sizeof(status_msg);

    switch ((ip_event_t)event_id)
    {
    case IP_EVENT_STA_GOT_IP:
    // case IP_EVENT_AP_STAIPASSIGNED:
    {
        ip_event_got_ip_t *ip_event = (ip_event_got_ip_t*)event_data;
        tcpip_adapter_dhcp_status_t dhcpc = TCPIP_ADAPTER_DHCP_STOPPED;
        tcpip_adapter_dhcp_status_t dhcps = TCPIP_ADAPTER_DHCP_STOPPED;

        status->info.ip[0] = ip4_addr1(&ip_event->ip_info.ip);
        status->info.ip[1] = ip4_addr2(&ip_event->ip_info.ip);
        status->info.ip[2] = ip4_addr3(&ip_event->ip_info.ip);
        status->info.ip[3] = ip4_addr4(&ip_event->ip_info.ip);

        if (tcpip_adapter_dhcpc_get_status(ip_event->if_index, &dhcpc) == ESP_OK)
        {
            status->dhcp.client = dhcpc;
        }
        if (tcpip_adapter_dhcps_get_status(ip_event->if_index, &dhcps) == ESP_OK)
        {
            status->dhcp.server = dhcps;
        }

        status_msg.header.type = CIOT_MSG_TYPE_START;
        status_msg.status = *status;
        iface_event.id = CIOT_IFACE_EVENT_STARTED;
        break;
    }
    case IP_EVENT_STA_LOST_IP:
    {
        status_msg.header.type = CIOT_MSG_TYPE_STOP;
        status_msg.status = *status;
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

#endif