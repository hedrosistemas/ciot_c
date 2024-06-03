/**
 * @file ciot_serializer_pb_pack.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <string.h>

#include "ciot/proto/v1/msg.pb-c.h"
#include "types/ciot_msg_types.h"

// static const char *TAG = "ciot_serializer_pb_pack";

int ciot_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__CiotData ciot = CIOT__CIOT_DATA__INIT;
    msg_pack->data->ciot = &ciot;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__CiotCfg cfg = CIOT__CIOT_CFG__INIT;
        msg_pack->data->ciot->config = &cfg;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__CiotStatus status = CIOT__CIOT_STATUS__INIT;
        Ciot__CiotInfo info = CIOT__CIOT_INFO__INIT;
        uint8_t ciot_ver[] = { CIOT_VER };
        msg_pack->data->ciot->status = &status;
        msg_pack->data->ciot->status->info = &info;
        msg_pack->data->ciot->status->state = msg->data.ciot.status.state;
        msg_pack->data->ciot->status->info->version.len = sizeof(ciot_ver);
        msg_pack->data->ciot->status->info->version.data = ciot_ver;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__CiotReq req = CIOT__CIOT_REQ__INIT;
        Ciot__CiotReqData data = CIOT__CIOT_REQ_DATA__INIT;
        msg_pack->data->ciot->request = &req;
        msg_pack->data->ciot->request->data = &data;
        msg_pack->data->ciot->request->type = msg->data.ciot.request.type;
        msg_pack->data->ciot->request->data->iface_id = msg->data.ciot.request.data.proxy_msg.iface;
        if(req.type == CIOT__CIOT_REQ_TYPE__CIOT_REQ_TYPE_PROXY_MSG)
        {
            msg_pack->data->ciot->request->data->payload.data = msg->data.ciot.request.data.proxy_msg.data;
            msg_pack->data->ciot->request->data->payload.len = msg->data.ciot.request.data.proxy_msg.size;
        }
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_storage_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__StorageData storage = CIOT__STORAGE_DATA__INIT;
    msg_pack->data->storage = &storage;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__StorageCfg cfg = CIOT__STORAGE_CFG__INIT;
        msg_pack->data->storage->config = &cfg;
        msg_pack->data->storage->config->type = msg->data.storage.config.type;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__StorageStatus status = CIOT__STORAGE_STATUS__INIT;
        msg_pack->data->storage->status = &status;
        msg_pack->data->storage->status->state = msg->data.storage.status.state;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__StorageReq req = CIOT__STORAGE_REQ__INIT;
        Ciot__StorageReqData data = CIOT__STORAGE_REQ_DATA__INIT;
        msg_pack->data->storage->request = &req;
        msg_pack->data->storage->request->data = &data;
        msg_pack->data->storage->request->type = msg->data.storage.request.type;
        msg_pack->data->storage->request->data->path = msg->data.storage.request.data.path;
        msg_pack->data->storage->request->data->data.data = msg->data.storage.request.data.data;
        msg_pack->data->storage->request->data->data.len = msg->data.storage.request.data.size;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_system_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__SysData sys = CIOT__SYS_DATA__INIT;
    msg_pack->data->sys = &sys;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__SysStatus status = CIOT__SYS_STATUS__INIT;
        Ciot__SysInfo info = CIOT__SYS_INFO__INIT;
        Ciot__SysFeatures features = CIOT__SYS_FEATURES__INIT;
        msg_pack->data->sys->status = &status;
        msg_pack->data->sys->status->info = &info;
        msg_pack->data->sys->status->info->features = &features;
        msg_pack->data->sys->status->free_memory = msg->data.system.status.free_memory;
        msg_pack->data->sys->status->lifetime = msg->data.system.status.lifetime;
        msg_pack->data->sys->status->reset_count = msg->data.system.status.rst_count;
        msg_pack->data->sys->status->reset_reason = msg->data.system.status.rst_reason;
        msg_pack->data->sys->status->info->app_ver.data = msg->data.system.status.info.app_ver;
        msg_pack->data->sys->status->info->app_ver.len = sizeof(msg->data.system.status.info.app_ver);
        msg_pack->data->sys->status->info->hardware = msg->data.system.status.info.hardware;
        msg_pack->data->sys->status->info->hw_name = msg->data.system.status.info.hw_name;
        msg_pack->data->sys->status->info->features->hw = *(uint32_t*)&msg->data.system.status.info.features.hw;
        msg_pack->data->sys->status->info->features->sw = *(uint32_t*)&msg->data.system.status.info.features.sw;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__SysReq request = CIOT__SYS_REQ__INIT;
        msg_pack->data->sys->request = &request;
        msg_pack->data->sys->request->type = msg->data.system.request.type;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_uart_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__UartData uart = CIOT__UART_DATA__INIT;
    msg_pack->data->uart = &uart;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__UartCfg cfg = CIOT__UART_CFG__INIT;
        msg_pack->data->uart->config = &cfg;
        msg_pack->data->uart->config->baud_rate = msg->data.uart.config.baud_rate;
        msg_pack->data->uart->config->bridge_mode = msg->data.uart.config.bridge_mode;
        msg_pack->data->uart->config->cts_pin = msg->data.uart.config.cts_pin;
        msg_pack->data->uart->config->dtr = msg->data.uart.config.dtr;
        msg_pack->data->uart->config->flow_control = msg->data.uart.config.flow_control;
        msg_pack->data->uart->config->num = msg->data.uart.config.num;
        msg_pack->data->uart->config->parity = msg->data.uart.config.parity;
        msg_pack->data->uart->config->rts_pin = msg->data.uart.config.rts_pin;
        msg_pack->data->uart->config->rx_pin = msg->data.uart.config.rx_pin;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__UartStatus status = CIOT__UART_STATUS__INIT;
        msg_pack->data->uart->status = &status;
        msg_pack->data->uart->status->error = msg->data.uart.status.error;
        msg_pack->data->uart->status->state = msg->data.uart.status.state;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__UartReq req = CIOT__UART_REQ__INIT;
        msg_pack->data->uart->request = &req;
        msg_pack->data->uart->request->type = msg->data.uart.request.type;
        msg_pack->data->uart->request->data.data = msg->data.uart.request.data.send_data.data;
        msg_pack->data->uart->request->data.len = msg->data.uart.request.data.send_data.size;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_usb_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__UsbData usb = CIOT__USB_DATA__INIT;
    msg_pack->data->usb = &usb;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__UsbCfg cfg = CIOT__USB_CFG__INIT;
        msg_pack->data->usb->config = &cfg;
        msg_pack->data->usb->config->bridge_mode = msg->data.usb.config.bridge_mode;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__UsbStatus status = CIOT__USB_STATUS__INIT;
        msg_pack->data->usb->status = &status;
        msg_pack->data->usb->status->state = msg->data.usb.status.state;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__UsbReq req = CIOT__USB_REQ__INIT;
        msg_pack->data->usb->request = &req;
        msg_pack->data->usb->request->type = msg->data.usb.request.type;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_tcp_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__TcpData tcp = CIOT__TCP_DATA__INIT;
    msg_pack->data->tcp = &tcp;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__TcpCfg cfg = CIOT__TCP_CFG__INIT;
        msg_pack->data->tcp->config = &cfg;
        msg_pack->data->tcp->config->dhcp = msg->data.tcp.config.dhcp;
        msg_pack->data->tcp->config->dns.data = msg->data.tcp.config.dns;
        msg_pack->data->tcp->config->dns.len = sizeof(msg->data.tcp.config.dns);
        msg_pack->data->tcp->config->gateway.data = msg->data.tcp.config.gateway;
        msg_pack->data->tcp->config->gateway.len = sizeof(msg->data.tcp.config.gateway);
        msg_pack->data->tcp->config->ip.data = msg->data.tcp.config.ip;
        msg_pack->data->tcp->config->ip.len = sizeof(msg->data.tcp.config.ip);
        msg_pack->data->tcp->config->mask.data = msg->data.tcp.config.mask;
        msg_pack->data->tcp->config->mask.len = sizeof(msg->data.tcp.config.mask);
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__TcpStatus status = CIOT__TCP_STATUS__INIT;
        Ciot__TcpInfo info = CIOT__TCP_INFO__INIT;
        Ciot__TcpDhcpStatus dhcp = CIOT__TCP_DHCP_STATUS__INIT;
        msg_pack->data->tcp->status = &status;
        msg_pack->data->tcp->status->info = &info;
        msg_pack->data->tcp->status->dhcp = &dhcp;
        msg_pack->data->tcp->status->conn_count = msg->data.tcp.status.conn_count;
        msg_pack->data->tcp->status->dhcp->client = msg->data.tcp.status.dhcp.client;
        msg_pack->data->tcp->status->dhcp->server = msg->data.tcp.status.dhcp.server;
        msg_pack->data->tcp->status->info->ip.data = msg->data.tcp.status.info.ip;
        msg_pack->data->tcp->status->info->ip.len = sizeof(msg->data.tcp.status.info.ip);
        msg_pack->data->tcp->status->info->mac.data = msg->data.tcp.status.info.mac;
        msg_pack->data->tcp->status->info->mac.len = sizeof(msg->data.tcp.status.info.mac);
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__TcpReq req = CIOT__TCP_REQ__INIT;
        msg_pack->data->tcp->request = &req;
        msg_pack->data->tcp->request->type = msg->data.tcp.request.type;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_eth_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__TcpData eth = CIOT__TCP_DATA__INIT;
    msg_pack->data->eth = &eth;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__TcpCfg cfg = CIOT__TCP_CFG__INIT;
        msg_pack->data->eth->config = &cfg;
        msg_pack->data->eth->config->dhcp = msg->data.eth.config.dhcp;
        msg_pack->data->eth->config->dns.data = msg->data.eth.config.dns;
        msg_pack->data->eth->config->dns.len = sizeof(msg->data.eth.config.dns);
        msg_pack->data->eth->config->gateway.data = msg->data.eth.config.gateway;
        msg_pack->data->eth->config->gateway.len = sizeof(msg->data.eth.config.gateway);
        msg_pack->data->eth->config->ip.data = msg->data.eth.config.ip;
        msg_pack->data->eth->config->ip.len = sizeof(msg->data.eth.config.ip);
        msg_pack->data->eth->config->mask.data = msg->data.eth.config.mask;
        msg_pack->data->eth->config->mask.len = sizeof(msg->data.eth.config.mask);
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__TcpStatus status = CIOT__TCP_STATUS__INIT;
        Ciot__TcpInfo info = CIOT__TCP_INFO__INIT;
        Ciot__TcpDhcpStatus dhcp = CIOT__TCP_DHCP_STATUS__INIT;
        msg_pack->data->eth->status = &status;
        msg_pack->data->eth->status->info = &info;
        msg_pack->data->eth->status->dhcp = &dhcp;
        msg_pack->data->eth->status->conn_count = msg->data.eth.status.conn_count;
        msg_pack->data->eth->status->dhcp->client = msg->data.eth.status.dhcp.client;
        msg_pack->data->eth->status->dhcp->server = msg->data.eth.status.dhcp.server;
        msg_pack->data->eth->status->info->ip.data = msg->data.eth.status.info.ip;
        msg_pack->data->eth->status->info->ip.len = sizeof(msg->data.eth.status.info.ip);
        msg_pack->data->eth->status->info->mac.data = msg->data.eth.status.info.mac;
        msg_pack->data->eth->status->info->mac.len = sizeof(msg->data.eth.status.info.mac);
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__TcpReq req = CIOT__TCP_REQ__INIT;
        msg_pack->data->eth->request = &req;
        msg_pack->data->eth->request->type = msg->data.eth.request.type;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_wifi_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__WifiData wifi = CIOT__WIFI_DATA__INIT;
    msg_pack->data->wifi = &wifi;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__WifiCfg cfg = CIOT__WIFI_CFG__INIT;
        Ciot__TcpCfg tcp = CIOT__TCP_CFG__INIT;
        msg_pack->data->wifi->config = &cfg;
        msg_pack->data->wifi->config->tcp = &tcp;
        msg_pack->data->wifi->config->password = msg->data.wifi.config.password;
        msg_pack->data->wifi->config->ssid = msg->data.wifi.config.ssid;
        msg_pack->data->wifi->config->type = msg->data.wifi.config.type;
        msg_pack->data->wifi->config->tcp->dhcp = msg->data.wifi.config.tcp.dhcp;
        msg_pack->data->wifi->config->tcp->dns.data = &msg->data.wifi.config.tcp.dns[0];
        msg_pack->data->wifi->config->tcp->dns.len = sizeof(msg->data.wifi.config.tcp.dns);
        msg_pack->data->wifi->config->tcp->gateway.data = &msg->data.wifi.config.tcp.gateway[0];
        msg_pack->data->wifi->config->tcp->gateway.len = sizeof(msg->data.wifi.config.tcp.gateway);
        msg_pack->data->wifi->config->tcp->ip.data = &msg->data.wifi.config.tcp.ip[0];
        msg_pack->data->wifi->config->tcp->ip.len = sizeof(msg->data.wifi.config.tcp.ip);
        msg_pack->data->wifi->config->tcp->mask.data = &msg->data.wifi.config.tcp.mask[0];
        msg_pack->data->wifi->config->tcp->mask.len = sizeof(msg->data.wifi.config.tcp.mask);
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__WifiStatus status = CIOT__WIFI_STATUS__INIT;
        Ciot__WifiApInfo info = CIOT__WIFI_AP_INFO__INIT;
        Ciot__TcpStatus tcp = CIOT__TCP_STATUS__INIT;
        Ciot__TcpDhcpStatus dhcp = CIOT__TCP_DHCP_STATUS__INIT;
        Ciot__TcpInfo tcp_info = CIOT__TCP_INFO__INIT;
        msg_pack->data->wifi->status = &status;
        msg_pack->data->wifi->status->info = &info;
        msg_pack->data->wifi->status->tcp = &tcp;
        msg_pack->data->wifi->status->tcp->dhcp = &dhcp;
        msg_pack->data->wifi->status->tcp->info = &tcp_info;
        msg_pack->data->wifi->status->disconnect_reason = msg->data.wifi.status.disconnect_reason;
        msg_pack->data->wifi->status->info->authmode = msg->data.wifi.status.info.authmode;
        msg_pack->data->wifi->status->info->bssid.data = msg->data.wifi.status.info.bssid;
        msg_pack->data->wifi->status->info->bssid.len = sizeof(msg->data.wifi.status.info.bssid);
        msg_pack->data->wifi->status->info->rssi = msg->data.wifi.status.info.rssi;
        msg_pack->data->wifi->status->info->ssid = msg->data.wifi.status.info.ssid;
        msg_pack->data->wifi->status->tcp->conn_count = msg->data.wifi.status.tcp.conn_count;
        msg_pack->data->wifi->status->tcp->dhcp->client = msg->data.wifi.status.tcp.dhcp.client;
        msg_pack->data->wifi->status->tcp->dhcp->server = msg->data.wifi.status.tcp.dhcp.server;
        msg_pack->data->wifi->status->tcp->state = msg->data.wifi.status.tcp.state;
        msg_pack->data->wifi->status->tcp->info->ip.data = msg->data.wifi.status.tcp.info.ip;
        msg_pack->data->wifi->status->tcp->info->ip.len = sizeof(msg->data.wifi.status.tcp.info.ip);
        msg_pack->data->wifi->status->tcp->info->mac.data = msg->data.wifi.status.tcp.info.mac;
        msg_pack->data->wifi->status->tcp->info->mac.len = sizeof(msg->data.wifi.status.tcp.info.mac);
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__WifiReq req = CIOT__WIFI_REQ__INIT;
        msg_pack->data->wifi->request = &req;
        msg_pack->data->wifi->request->type = msg->data.wifi.request.type;
        if(msg->data.wifi.request.type == CIOT_WIFI_REQ_SCAN)
        {

        }
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_ble_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__BleData ble = CIOT__BLE_DATA__INIT;
    msg_pack->data->ble = &ble;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__BleCfg cfg = CIOT__BLE_CFG__INIT;
        msg_pack->data->ble->config = &cfg;
        msg_pack->data->ble->config->mac.data = msg->data.ble.config.mac;
        msg_pack->data->ble->config->mac.len = sizeof(msg->data.ble.config.mac);
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__BleStatus status = CIOT__BLE_STATUS__INIT;
        Ciot__BleInfo info = CIOT__BLE_INFO__INIT;
        msg_pack->data->ble->status = &status;
        msg_pack->data->ble->status->info = &info;
        msg_pack->data->ble->status->err_code = msg->data.ble.status.err_code;
        msg_pack->data->ble->status->info->hw_mac.data = msg->data.ble.status.info.hw_mac;
        msg_pack->data->ble->status->info->hw_mac.len = sizeof(msg->data.ble.status.info.hw_mac);
        msg_pack->data->ble->status->info->sw_mac.data = msg->data.ble.status.info.sw_mac;
        msg_pack->data->ble->status->info->sw_mac.len = sizeof(msg->data.ble.status.info.sw_mac);
        msg_pack->data->ble->status->state = msg->data.ble.status.state;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__BleReq req = CIOT__BLE_REQ__INIT;
        msg_pack->data->ble->request = &req;
        msg_pack->data->ble->request->type = msg->data.ble.request.type;
        if(msg->data.ble.request.type == CIOT_BLE_REQ_SET_MAC)
        {
            msg_pack->data->ble->request->set_mac.data = msg->data.ble.request.data.set_mac;
            msg_pack->data->ble->request->set_mac.len = sizeof(msg->data.ble.request.data.set_mac);
        }
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_ble_scn_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__BleScnData ble_scn = CIOT__BLE_SCN_DATA__INIT;
    msg_pack->data->ble_scn = &ble_scn;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__BleScnCfg cfg = CIOT__BLE_SCN_CFG__INIT;
        msg_pack->data->ble_scn->config = &cfg;
        msg_pack->data->ble_scn->config->active = msg->data.ble_scn.config.active;
        msg_pack->data->ble_scn->config->bridge_mode = msg->data.ble_scn.config.brigde_mode;
        msg_pack->data->ble_scn->config->interval = msg->data.ble_scn.config.interval;
        msg_pack->data->ble_scn->config->timeout = msg->data.ble_scn.config.timeout;
        msg_pack->data->ble_scn->config->window = msg->data.ble_scn.config.window;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__BleScnStatus status = CIOT__BLE_SCN_STATUS__INIT;
        Ciot__BleScnAdvInfo adv_info = CIOT__BLE_SCN_ADV_INFO__INIT;
        msg_pack->data->ble_scn->status = &status;
        msg_pack->data->ble_scn->status->adv_info = &adv_info;
        msg_pack->data->ble_scn->status->adv_info->mac.data = msg->data.ble_scn.status.adv_info.mac;
        msg_pack->data->ble_scn->status->adv_info->mac.len = sizeof(msg->data.ble_scn.status.adv_info.mac);
        msg_pack->data->ble_scn->status->adv_info->rssi = msg->data.ble_scn.status.adv_info.rssi;
        msg_pack->data->ble_scn->status->err_code = msg->data.ble_scn.status.err_code;
        msg_pack->data->ble_scn->status->state = msg->data.ble_scn.status.state;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_ntp_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__NtpData ntp = CIOT__NTP_DATA__INIT;
    msg_pack->data->ntp = &ntp;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__NtpCfg cfg = CIOT__NTP_CFG__INIT;
        msg_pack->data->ntp->config = &cfg;
        msg_pack->data->ntp->config->op_mode = msg->data.ntp.config.op_mode;
        msg_pack->data->ntp->config->server1 = msg->data.ntp.config.server[0];
        msg_pack->data->ntp->config->server2 = msg->data.ntp.config.server[1];
        msg_pack->data->ntp->config->server3 = msg->data.ntp.config.server[2];
        msg_pack->data->ntp->config->sync_interval = msg->data.ntp.config.sync_interval;
        msg_pack->data->ntp->config->sync_mode = msg->data.ntp.config.sync_mode;
        msg_pack->data->ntp->config->timezone = msg->data.ntp.config.timezone;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__NtpStatus status = CIOT__NTP_STATUS__INIT;
        msg_pack->data->ntp->status = &status;
        msg_pack->data->ntp->status->init = msg->data.ntp.status.init;
        msg_pack->data->ntp->status->last_sync = msg->data.ntp.status.last_sync;
        msg_pack->data->ntp->status->state = msg->data.ntp.status.state;
        msg_pack->data->ntp->status->sync = msg->data.ntp.status.sync;
        msg_pack->data->ntp->status->sync_count = msg->data.ntp.status.sync_count;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__NtpReq req = CIOT__NTP_REQ__INIT;
        msg_pack->data->ntp->request = &req;
        msg_pack->data->ntp->request->type = msg->data.ntp.request.type;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_ota_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__OtaData ota = CIOT__OTA_DATA__INIT;
    msg_pack->data->ota = &ota;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__OtaCfg cfg = CIOT__OTA_CFG__INIT;
        msg_pack->data->ota->config = &cfg;
        msg_pack->data->ota->config->encrypted = msg->data.ota.config.encrypted;
        msg_pack->data->ota->config->force = msg->data.ota.config.force;
        msg_pack->data->ota->config->restart = msg->data.ota.config.restart;
        msg_pack->data->ota->config->url = msg->data.ota.config.url;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__OtaStatus status = CIOT__OTA_STATUS__INIT;
        msg_pack->data->ota->status = &status;
        msg_pack->data->ota->status->error = msg->data.ota.status.error;
        msg_pack->data->ota->status->image_read = msg->data.ota.status.image_read;
        msg_pack->data->ota->status->image_size = msg->data.ota.status.image_size;
        msg_pack->data->ota->status->state = msg->data.ota.status.state;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__OtaReq req = CIOT__OTA_REQ__INIT;
        msg_pack->data->ota->request = &req;
        msg_pack->data->ota->request->type = msg->data.ota.request.type;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_dfu_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__DfuData dfu = CIOT__DFU_DATA__INIT;
    msg_pack->data->dfu = &dfu;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__DfuCfg cfg = CIOT__DFU_CFG__INIT;
        msg_pack->data->dfu->config = &cfg;
        msg_pack->data->dfu->config->type = msg->data.dfu.config.type;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__DfuStatus status = CIOT__DFU_STATUS__INIT;
        msg_pack->data->dfu->status = &status;
        msg_pack->data->dfu->status->error = msg->data.dfu.status.error;
        msg_pack->data->dfu->status->image_written = msg->data.dfu.status.image_read;
        msg_pack->data->dfu->status->image_size = msg->data.dfu.status.image_size;
        msg_pack->data->dfu->status->state = msg->data.dfu.status.state;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__DfuRequest req = CIOT__DFU_REQUEST__INIT;
        msg_pack->data->dfu->request = &req;
        msg_pack->data->dfu->request->type = msg->data.dfu.request.type;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_http_client_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__HttpClientData http = CIOT__HTTP_CLIENT_DATA__INIT;
    msg_pack->data->http_client = &http;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__HttpClientCfg cfg = CIOT__HTTP_CLIENT_CFG__INIT;
        msg_pack->data->http_client->config = &cfg;
        msg_pack->data->http_client->config->method = msg->data.httpc.config.method;
        msg_pack->data->http_client->config->timeout = msg->data.httpc.config.timeout;
        msg_pack->data->http_client->config->transport = msg->data.httpc.config.transport;
        msg_pack->data->http_client->config->url = msg->data.httpc.config.url;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__HttpClientStatus status = CIOT__HTTP_CLIENT_STATUS__INIT;
        msg_pack->data->http_client->status = &status;
        msg_pack->data->http_client->status->error = msg->data.httpc.status.error;
        msg_pack->data->http_client->status->state = msg->data.httpc.status.state;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__HttpClientReq req = CIOT__HTTP_CLIENT_REQ__INIT;
        msg_pack->data->http_client->request = &req;
        msg_pack->data->http_client->request->type = msg->data.httpc.request.type;
        if(msg->data.httpc.request.type == CIOT_HTTPC_REQ_SEND_DATA)
        {
            Ciot__HttpClientReqSend send = CIOT__HTTP_CLIENT_REQ_SEND__INIT;
            Ciot__HttpClientCfg cfg = CIOT__HTTP_CLIENT_CFG__INIT;
            msg_pack->data->http_client->request->send = &send;
            msg_pack->data->http_client->request->send->config = &cfg;
            msg_pack->data->http_client->request->send->body.data = msg->data.httpc.request.data.send.body;
            msg_pack->data->http_client->request->send->body.len = msg->data.httpc.request.data.send.content_length;
            msg_pack->data->http_client->request->send->config->method = msg->data.httpc.request.data.send.cfg.method;
            msg_pack->data->http_client->request->send->config->timeout = msg->data.httpc.request.data.send.cfg.timeout;
            msg_pack->data->http_client->request->send->config->transport = msg->data.httpc.request.data.send.cfg.transport;
            msg_pack->data->http_client->request->send->config->url = msg->data.httpc.request.data.send.cfg.url;
        }
        if(msg->data.httpc.request.type == CIOT_HTTPC_REQ_SET_HEADER)
        {
            Ciot__HttpClientReqSetHeader set_header = CIOT__HTTP_CLIENT_REQ_SET_HEADER__INIT;
            msg_pack->data->http_client->request->set_header = &set_header;
            msg_pack->data->http_client->request->set_header->header = msg->data.httpc.request.data.set_header.header;
            msg_pack->data->http_client->request->set_header->value = msg->data.httpc.request.data.set_header.value;
        }
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_http_server_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__HttpServerData http = CIOT__HTTP_SERVER_DATA__INIT;
    msg_pack->data->http_server = &http;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__HttpServerCfg cfg = CIOT__HTTP_SERVER_CFG__INIT;
        msg_pack->data->http_server->config = &cfg;
        msg_pack->data->http_server->config->address = msg->data.https.config.address;
        msg_pack->data->http_server->config->port = msg->data.https.config.port;
        msg_pack->data->http_server->config->route = msg->data.https.config.route;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__HttpServerStatus status = CIOT__HTTP_SERVER_STATUS__INIT;
        msg_pack->data->http_server->status = &status;
        msg_pack->data->http_server->status->error = msg->data.https.status.error;
        msg_pack->data->http_server->status->state = msg->data.https.status.state;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__HttpServerReq req = CIOT__HTTP_SERVER_REQ__INIT;
        Ciot__HttpServerReqData data = CIOT__HTTP_SERVER_REQ_DATA__INIT;
        msg_pack->data->http_server->request = &req;
        msg_pack->data->http_server->request->data = &data;
        msg_pack->data->http_client->request->type = msg->data.https.request.type;
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_mqtt_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    Ciot__MqttClientData mqtt = CIOT__MQTT_CLIENT_DATA__INIT;
    msg_pack->data->mqtt_client = &mqtt;
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
    {
        Ciot__MqttClientCfg cfg = CIOT__MQTT_CLIENT_CFG__INIT;
        Ciot__MqttClientTopicsCfg topics = CIOT__MQTT_CLIENT_TOPICS_CFG__INIT;
        cfg.topics = &topics;
        msg_pack->data->mqtt_client->config = &cfg;
        msg_pack->data->mqtt_client->config->client_id = msg->data.mqtt.config.client_id;
        msg_pack->data->mqtt_client->config->password = msg->data.mqtt.config.pass;
        msg_pack->data->mqtt_client->config->port = msg->data.mqtt.config.port;
        msg_pack->data->mqtt_client->config->qos = msg->data.mqtt.config.qos;
        msg_pack->data->mqtt_client->config->topics->b2d = msg->data.mqtt.config.topics.b2d;
        msg_pack->data->mqtt_client->config->topics->d2b = msg->data.mqtt.config.topics.d2b;
        msg_pack->data->mqtt_client->config->transport = msg->data.mqtt.config.transport;
        msg_pack->data->mqtt_client->config->url = msg->data.mqtt.config.url;
        msg_pack->data->mqtt_client->config->user = msg->data.mqtt.config.user;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_GET_STATUS:
    {
        Ciot__MqttClientStatus status = CIOT__MQTT_CLIENT_STATUS__INIT;
        Ciot__MqttClientError error = CIOT__MQTT_CLIENT_ERROR__INIT;
        msg_pack->data->mqtt_client->status = &status;
        msg_pack->data->mqtt_client->status->error = &error;
        msg_pack->data->mqtt_client->status->conn_count = msg->data.mqtt.status.conn_count;
        msg_pack->data->mqtt_client->status->data_rate = msg->data.mqtt.status.data_rate;
        msg_pack->data->mqtt_client->status->error->code = msg->data.mqtt.status.error.code;
        msg_pack->data->mqtt_client->status->error->tls_cert_verify_flags = msg->data.mqtt.status.error.tls_cert_verify_flags;
        msg_pack->data->mqtt_client->status->error->tls_last_err = msg->data.mqtt.status.error.tls_last_err;
        msg_pack->data->mqtt_client->status->error->tls_stack_err = msg->data.mqtt.status.error.tls_stack_err;
        msg_pack->data->mqtt_client->status->error->transport_sock = msg->data.mqtt.status.error.transport_sock;
        msg_pack->data->mqtt_client->status->error->type = msg->data.mqtt.status.error.type;
        msg_pack->data->mqtt_client->status->last_msg_time = msg->data.mqtt.status.last_msg_time;
        msg_pack->data->mqtt_client->status->state = msg->data.mqtt.status.state;
        return ciot__msg__pack(msg_pack, bytes);
    }
    case CIOT_MSG_TYPE_REQUEST:
    {
        Ciot__MqttClientReq req = CIOT__MQTT_CLIENT_REQ__INIT;
        msg_pack->data->mqtt_client->request = &req;
        msg_pack->data->mqtt_client->request->type = msg->data.mqtt.request.type;
        if(msg->data.mqtt.request.type == CIOT_MQTT_REQ_PUBLISH)
        {
            Ciot__MqttClientReqPublish publish = CIOT__MQTT_CLIENT_REQ_PUBLISH__INIT;
            req.publish = &publish;
            msg_pack->data->mqtt_client->request->publish->message.data = msg->data.mqtt.request.data.publish.msg;
            msg_pack->data->mqtt_client->request->publish->message.len = sizeof(msg->data.mqtt.request.data.publish.msg);
            msg_pack->data->mqtt_client->request->publish->qos = msg->data.mqtt.request.data.publish.qos;
            msg_pack->data->mqtt_client->request->publish->topic = msg->data.mqtt.request.data.publish.topic;
        }
        if(msg->data.mqtt.request.type == CIOT_MQTT_REQ_SUBSCRIBE)
        {
            Ciot__MqttClientReqSubscribe subscribe = CIOT__MQTT_CLIENT_REQ_SUBSCRIBE__INIT;
            req.subscribe = &subscribe;
            msg_pack->data->mqtt_client->request->subscribe->topic = msg->data.mqtt.request.data.subscribe.topic;
            msg_pack->data->mqtt_client->request->subscribe->qos = msg->data.mqtt.request.data.subscribe.qos;
        }
        return ciot__msg__pack(msg_pack, bytes);
    }
    default:
        return ciot__msg__pack(msg_pack, bytes);
    }
}

int ciot_bridge_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes)
{
    return ciot__msg__pack(msg_pack, bytes);
}
