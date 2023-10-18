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

#include <string.h>

#include "esp_mac.h"
#include "esp_eth.h"
#include "esp_eth_mac.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "esp_event.h"

#include "ciot_tcp.h"
#include "ciot_eth.h"

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

static ciot_err_t ciot_eth_init(ciot_eth_t this);
static ciot_err_t ciot_eth_tcp_event_handler(void *sender, ciot_iface_event_t *event, void *event_args);
static void ciot_eth_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data);

ciot_eth_t ciot_eth_new(void *handle)
{
    ciot_eth_t this = calloc(1, sizeof(struct ciot_eth));
    this->iface.base.ptr = this;
    this->iface.base.start = (ciot_iface_start_fn *)ciot_eth_start;
    this->iface.base.stop = (ciot_iface_stop_fn *)ciot_eth_stop;
    this->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_eth_process_req;
    this->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_eth_send_data;
    this->iface.base.cfg.ptr = &this->cfg;
    this->iface.base.cfg.size = sizeof(this->cfg);
    this->iface.base.status.ptr = &this->status;
    this->iface.base.status.size = sizeof(this->status);
    this->iface.info.type = CIOT_IFACE_TYPE_ETH;
    return this;
}

ciot_err_t ciot_eth_start(ciot_eth_t this, ciot_tcp_cfg_t *cfg)
{
    CIOT_NULL_CHECK(this);
    memcpy(&this->cfg, cfg, sizeof(this->cfg));

    if(this->init == false)
    {
        CIOT_ERROR_RETURN(ciot_eth_init(this));
        this->init = true;
    }

    if(this->status.state == CIOT_TCP_STATE_STARTED)
    {
        CIOT_ERROR_RETURN(esp_eth_stop(this->handle));
    }

    CIOT_ERROR_RETURN(esp_eth_start(this->handle));

    return CIOT_OK;
}

ciot_err_t ciot_eth_stop(ciot_eth_t this)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_eth_process_req(ciot_eth_t this, ciot_tcp_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_eth_send_data(ciot_eth_t this, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

static ciot_err_t ciot_eth_init(ciot_eth_t this)
{
    esp_netif_config_t netif_conf = ESP_NETIF_DEFAULT_ETH();
    esp_netif_t *netif = esp_netif_new(&netif_conf);
    eth_mac_config_t mac_conf = ETH_MAC_DEFAULT_CONFIG();
    eth_phy_config_t phy_conf = ETH_PHY_DEFAULT_CONFIG();
    eth_esp32_emac_config_t emac_conf = ETH_ESP32_EMAC_DEFAULT_CONFIG();

    ciot_tcp_handle_t tcp_handle = {
        .netif = netif,
        .cfg = &this->cfg,
        .status = &this->status,
    };
    this->tcp = ciot_tcp_new(&tcp_handle);

    CIOT_ERROR_RETURN(ciot_tcp_register_event(this->tcp, ciot_eth_tcp_event_handler, this));
    ESP_ERROR_CHECK(esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, ciot_eth_event_handler, this));

    phy_conf.phy_addr = CIOT_CONFIG_ETH_PHY_ADDR;
    phy_conf.reset_gpio_num = CIOT_CONFIG_ETH_GPIO_PHY_RST;
    
    emac_conf.smi_mdc_gpio_num = CIOT_CONFIG_ETH_GPIO_MDC;
    emac_conf.smi_mdio_gpio_num = CIOT_CONFIG_ETH_GPIO_MDIO;

    esp_eth_mac_t *mac = esp_eth_mac_new_esp32(&emac_conf, &mac_conf);
    esp_eth_phy_t *phy = CIOT_CONFIG_ETH_PHY_NEW(phy_conf);
    esp_eth_config_t eth_conf = ETH_DEFAULT_CONFIG(mac, phy);

    CIOT_ERROR_RETURN(esp_eth_driver_install(&eth_conf, &this->handle));
    CIOT_ERROR_RETURN(esp_netif_attach(netif, esp_eth_new_netif_glue(this->handle)));

    return CIOT_OK;
}

static ciot_err_t ciot_eth_tcp_event_handler(void *sender, ciot_iface_event_t *event, void *args)
{
    CIOT_NULL_CHECK(args);

    ciot_eth_t this = (ciot_eth_t)args;
    if (this->iface.event_handler != NULL)
    {
        return this->iface.event_handler(this, event, this->iface.event_args);
    }

    return CIOT_ERR_INVALID_STATE;
}

static void ciot_eth_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_eth_t this = (ciot_eth_t)handler_args;
    ciot_iface_event_t event = { 0 };

    event.msg.type = CIOT_MSG_TYPE_EVENT;
    event.msg.iface = this->iface.info;
    event.msg.data.eth.status = this->status;

    switch ((eth_event_t)event_id)
    {
    case ETHERNET_EVENT_START:
        ESP_LOGI(TAG, "ETHERNET_EVENT_START");
        CIOT_ERROR_PRINT(esp_read_mac(this->status.info.mac, ESP_MAC_ETH));
        this->status.state = CIOT_TCP_STATE_CONNECTING;
        event.id = CIOT_ETH_EVENT_START;
        break;
    case ETHERNET_EVENT_STOP:
        ESP_LOGI(TAG, "ETHERNET_EVENT_STOP");
        this->status.state = CIOT_TCP_STATE_STOPPED;
        event.id = CIOT_ETH_EVENT_STOP;
        break;
    case ETHERNET_EVENT_CONNECTED:
        ESP_LOGI(TAG, "ETHERNET_EVENT_CONNECTED");
        this->status.state = CIOT_TCP_STATE_CONNECTED;
        this->status.conn_count++;
        CIOT_ERROR_PRINT(ciot_tcp_start(this->tcp, &this->cfg));
        event.id = CIOT_ETH_EVENT_CONNECTED;
        break;
    case ETHERNET_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "ETHERNET_EVENT_DISCONNECTED");
        this->status.state = CIOT_TCP_STATE_STARTED;
        event.id = CIOT_ETH_EVENT_DISCONNECTED;
        break;
    default:
        break;
    }

    if (this->iface.event_handler != NULL)
    {
        this->iface.event_handler(this, &event, this->iface.event_args);
    }
}
