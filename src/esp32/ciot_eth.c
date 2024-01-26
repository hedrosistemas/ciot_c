/**
 * @file ciot_eth.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_eth.h"

#if 1 && defined(CIOT_TARGET_ESP32)

#include <string.h>

#include "esp_mac.h"
#include "esp_eth.h"
#include "esp_eth_mac.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "esp_event.h"

#include "ciot_tcp.h"

struct ciot_eth
{
    ciot_iface_t iface;
    ciot_tcp_t tcp;
    ciot_tcp_cfg_t cfg;
    ciot_tcp_status_t status;
    esp_eth_handle_t handle;
    bool init;
};

static const char *TAG = "ciot_eth";

static ciot_err_t ciot_eth_init(ciot_eth_t self);
static ciot_err_t ciot_eth_tcp_event_handler(ciot_iface_t *sender, ciot_iface_event_t *iface_event, void *event_args);
static void ciot_eth_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data);

ciot_eth_t ciot_eth_new(void *handle)
{
    ciot_eth_t self = calloc(1, sizeof(struct ciot_eth));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_eth_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_eth_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_eth_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_eth_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_ETH;
    return self;
}

ciot_err_t ciot_eth_start(ciot_eth_t self, ciot_tcp_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    memcpy(&self->cfg, cfg, sizeof(self->cfg));

    if(self->init == false)
    {
        ESP_ERROR_CHECK(ciot_tcp_init());
        CIOT_ERROR_RETURN(ciot_eth_init(self));
        self->init = true;
    }

    if(self->status.state == CIOT_TCP_STATE_STARTED)
    {
        CIOT_ERROR_RETURN(esp_eth_stop(self->handle));
    }

    CIOT_ERROR_RETURN(esp_eth_start(self->handle));

    return CIOT_OK;
}

ciot_err_t ciot_eth_stop(ciot_eth_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_eth_process_req(ciot_eth_t self, ciot_tcp_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_eth_send_data(ciot_eth_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

static ciot_err_t ciot_eth_init(ciot_eth_t self)
{
    esp_netif_config_t netif_conf = ESP_NETIF_DEFAULT_ETH();
    esp_netif_t *netif = esp_netif_new(&netif_conf);
    eth_mac_config_t mac_conf = ETH_MAC_DEFAULT_CONFIG();
    eth_phy_config_t phy_conf = ETH_PHY_DEFAULT_CONFIG();
    eth_esp32_emac_config_t emac_conf = ETH_ESP32_EMAC_DEFAULT_CONFIG();

    ciot_tcp_handle_t tcp_handle = {
        .netif = netif,
        .cfg = &self->cfg,
        .status = &self->status,
    };
    self->tcp = ciot_tcp_new(&tcp_handle);

    CIOT_ERROR_RETURN(ciot_tcp_register_event(self->tcp, ciot_eth_tcp_event_handler, self));
    ESP_ERROR_CHECK(esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, ciot_eth_event_handler, self));

    phy_conf.phy_addr = CIOT_CONFIG_ETH_PHY_ADDR;
    phy_conf.reset_gpio_num = CIOT_CONFIG_ETH_GPIO_PHY_RST;
    
    emac_conf.smi_mdc_gpio_num = CIOT_CONFIG_ETH_GPIO_MDC;
    emac_conf.smi_mdio_gpio_num = CIOT_CONFIG_ETH_GPIO_MDIO;

    esp_eth_mac_t *mac = esp_eth_mac_new_esp32(&emac_conf, &mac_conf);
    esp_eth_phy_t *phy = CIOT_CONFIG_ETH_PHY_NEW(phy_conf);
    esp_eth_config_t eth_conf = ETH_DEFAULT_CONFIG(mac, phy);

    CIOT_ERROR_RETURN(esp_eth_driver_install(&eth_conf, &self->handle));
    CIOT_ERROR_RETURN(esp_netif_attach(netif, esp_eth_new_netif_glue(self->handle)));

    return CIOT_OK;
}

static ciot_err_t ciot_eth_tcp_event_handler(ciot_iface_t *sender, ciot_iface_event_t *iface_event, void *args)
{
    CIOT_NULL_CHECK(args);
    ciot_eth_t self = (ciot_eth_t)args;
    self->status = iface_event->data->msg.data.eth.status;
    if (self->iface.event_handler != NULL)
    {
        return self->iface.event_handler((ciot_iface_t*)self, iface_event, self->iface.event_args);
    }

    return CIOT_ERR_INVALID_STATE;
}

static void ciot_eth_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_eth_t self = (ciot_eth_t)handler_args;

    ciot_iface_event_t iface_event = {0};
    ciot_eth_status_msg_t status_msg = {0};

    status_msg.header.iface = self->iface.info;
    iface_event.data = (ciot_iface_event_data_u*)&status_msg;
    iface_event.size = sizeof(status_msg);

    switch ((eth_event_t)event_id)
    {
    case ETHERNET_EVENT_START:
        ESP_LOGI(TAG, "ETHERNET_EVENT_START");
        CIOT_ERROR_PRINT(esp_read_mac(self->status.info.mac, ESP_MAC_ETH));
        self->status.state = CIOT_TCP_STATE_CONNECTING;
        status_msg.header.type = CIOT_MSG_TYPE_EVENT;
        status_msg.status = self->status;
        iface_event.id = CIOT_ETH_EVENT_START;
        break;
    case ETHERNET_EVENT_STOP:
        ESP_LOGI(TAG, "ETHERNET_EVENT_STOP");
        self->status.state = CIOT_TCP_STATE_STOPPED;
        status_msg.header.type = CIOT_MSG_TYPE_EVENT;
        status_msg.status = self->status;
        iface_event.id = CIOT_IFACE_EVENT_STOPPED;
        break;
    case ETHERNET_EVENT_CONNECTED:
        ESP_LOGI(TAG, "ETHERNET_EVENT_CONNECTED");
        self->status.state = CIOT_TCP_STATE_CONNECTED;
        self->status.conn_count++;
        CIOT_ERROR_PRINT(ciot_tcp_start(self->tcp, &self->cfg));
        status_msg.header.type = CIOT_MSG_TYPE_EVENT;
        status_msg.status = self->status;
        iface_event.id = CIOT_ETH_EVENT_CONNECTED;
        break;
    case ETHERNET_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "ETHERNET_EVENT_DISCONNECTED");
        self->status.state = CIOT_TCP_STATE_STARTED;
        status_msg.header.type = CIOT_MSG_TYPE_EVENT;
        status_msg.status = self->status;
        iface_event.id = CIOT_ETH_EVENT_DISCONNECTED;
        break;
    default:
        break;
    }

    if (self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
    }
}

#endif
