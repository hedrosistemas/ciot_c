/**
 * @file proto_serializer_unpack.c
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

// static const char *TAG = "proto_serializer_unpack";

int ciot_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->ciot->config == NULL) break;
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->ciot->status == NULL) break;
        msg->data.ciot.status.state = msg_pack->data->ciot->status->state;
        memcpy(msg->data.ciot.status.info.version, msg_pack->data->ciot->status->info->version.data, msg_pack->data->ciot->status->info->version.len);
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->ciot->request == NULL) break;
        msg->data.ciot.request.type = msg_pack->data->ciot->request->type;
        msg->data.ciot.request.data.proxy_msg.iface = msg_pack->data->ciot->request->data->iface_id;
        if(msg_pack->data->ciot->request->type == CIOT__CIOT_REQ_TYPE__CIOT_REQ_TYPE_PROXY_MSG)
        {
            memcpy(msg->data.ciot.request.data.proxy_msg.data, msg_pack->data->ciot->request->data->payload.data, msg_pack->data->ciot->request->data->payload.len);
            msg->data.ciot.request.data.proxy_msg.size = msg_pack->data->ciot->request->data->payload.len;
        }
        break;
    default:
        break;
    }
    return 0;
}

int ciot_storage_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->storage->config == NULL) break;
        msg->data.storage.config.type = msg_pack->data->storage->config->type;
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->storage->status == NULL) break;
        msg->data.storage.status.state = msg_pack->data->storage->status->state;
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->storage->request == NULL) break;
        msg->data.storage.request.type = msg_pack->data->storage->request->type;
        strcpy(msg->data.storage.request.data.path, msg_pack->data->storage->request->data->path);
        memcpy(msg->data.storage.request.data.data, msg_pack->data->storage->request->data->data.data, msg_pack->data->storage->request->data->data.len);
        break;
    default:
        break;
    }
    return 0;
}

int ciot_system_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->sys->config == NULL) break;
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->sys->status == NULL) break;
        msg->data.system.status.free_memory = msg_pack->data->sys->status->free_memory;
        msg->data.system.status.lifetime = msg_pack->data->sys->status->lifetime;
        msg->data.system.status.rst_count = msg_pack->data->sys->status->reset_count;
        msg->data.system.status.rst_reason = msg_pack->data->sys->status->reset_reason;
        msg->data.system.status.info.features.hw = *(ciot_sys_hw_features_t*)&msg_pack->data->sys->status->info->features->hw;
        msg->data.system.status.info.features.sw = *(ciot_sys_sw_features_t*)&msg_pack->data->sys->status->info->features->sw;
        memcpy(msg->data.system.status.info.app_ver, msg_pack->data->sys->status->info->app_ver.data, msg_pack->data->sys->status->info->app_ver.len);
        msg->data.system.status.info.hardware = msg_pack->data->sys->status->info->hardware;
        strcpy(msg->data.system.status.info.hw_name, msg_pack->data->sys->status->info->hw_name);
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->sys->request == NULL) break;
        msg->data.system.request.type = msg_pack->data->sys->request->type;
        break;
    default:
        break;
    }
    return 0;
}

int ciot_uart_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->uart->config == NULL) break;
        msg->data.uart.config.baud_rate = msg_pack->data->uart->config->baud_rate;
        msg->data.uart.config.bridge_mode = msg_pack->data->uart->config->bridge_mode;
        msg->data.uart.config.cts_pin = msg_pack->data->uart->config->cts_pin;
        msg->data.uart.config.dtr = msg_pack->data->uart->config->dtr;
        msg->data.uart.config.flow_control = msg_pack->data->uart->config->flow_control;
        msg->data.uart.config.num = msg_pack->data->uart->config->num;
        msg->data.uart.config.parity = msg_pack->data->uart->config->parity;
        msg->data.uart.config.rts_pin = msg_pack->data->uart->config->rts_pin;
        msg->data.uart.config.rx_pin = msg_pack->data->uart->config->rx_pin;
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->uart->status == NULL) break;
        msg->data.uart.status.error = msg_pack->data->uart->status->error;
        msg->data.uart.status.state = msg_pack->data->uart->status->state;
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->uart->request == NULL) break;
        msg->data.uart.request.type = msg_pack->data->uart->request->type;
        memcpy(msg->data.uart.request.data.send_data.data, msg_pack->data->uart->request->data.data, msg_pack->data->uart->request->data.len);
        msg->data.uart.request.data.send_data.size = msg_pack->data->uart->request->data.len;
        break;
    default:
        break;
    }
    return 0;
}

int ciot_usb_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->usb->config == NULL) break;
        msg->data.usb.config.bridge_mode = msg_pack->data->usb->config->bridge_mode;
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->usb->status == NULL) break;
        msg->data.usb.status.state = msg_pack->data->usb->status->state;
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->usb->request == NULL) break;
        msg->data.usb.request.type = msg_pack->data->usb->request->type;
        break;
    default:
        break;
    }
    return 0;
}

int ciot_tcp_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->tcp->config == NULL) break;
        msg->data.tcp.config.dhcp = msg_pack->data->tcp->config->dhcp;
        memcpy(msg->data.tcp.config.dns, msg_pack->data->tcp->config->dns.data, msg_pack->data->tcp->config->dns.len);
        memcpy(msg->data.tcp.config.gateway, msg_pack->data->tcp->config->gateway.data, msg_pack->data->tcp->config->gateway.len);
        memcpy(msg->data.tcp.config.ip, msg_pack->data->tcp->config->ip.data, msg_pack->data->tcp->config->ip.len);
        memcpy(msg->data.tcp.config.mask, msg_pack->data->tcp->config->mask.data, msg_pack->data->tcp->config->mask.len);
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->tcp->status == NULL) break;
        msg->data.tcp.status.conn_count = msg_pack->data->tcp->status->conn_count;
        msg->data.tcp.status.dhcp.client = msg_pack->data->tcp->status->dhcp->client;
        msg->data.tcp.status.dhcp.server = msg_pack->data->tcp->status->dhcp->server;
        if(msg_pack->data->tcp->status->info == NULL) break;
        memcpy(msg->data.tcp.status.info.ip, msg_pack->data->tcp->status->info->ip.data, msg_pack->data->tcp->status->info->ip.len);
        memcpy(msg->data.tcp.status.info.mac, msg_pack->data->tcp->status->info->mac.data, msg_pack->data->tcp->status->info->mac.len);
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->tcp->request == NULL) break;
        msg->data.tcp.request.type = msg_pack->data->tcp->request->type;
        break;
    default:
        break;
    }
    return 0;
}

int ciot_eth_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->eth->config == NULL) break;
        msg->data.eth.config.dhcp = msg_pack->data->eth->config->dhcp;
        memcpy(msg->data.eth.config.dns, msg_pack->data->eth->config->dns.data, msg_pack->data->eth->config->dns.len);
        memcpy(msg->data.eth.config.gateway, msg_pack->data->eth->config->gateway.data, msg_pack->data->eth->config->gateway.len);
        memcpy(msg->data.eth.config.ip, msg_pack->data->eth->config->ip.data, msg_pack->data->eth->config->ip.len);
        memcpy(msg->data.eth.config.mask, msg_pack->data->eth->config->mask.data, msg_pack->data->eth->config->mask.len);
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->eth->status == NULL) break;
        msg->data.eth.status.conn_count = msg_pack->data->eth->status->conn_count;
        if(msg_pack->data->eth->status->dhcp != NULL)
        {
            msg->data.eth.status.dhcp.client = msg_pack->data->eth->status->dhcp->client;
            msg->data.eth.status.dhcp.server = msg_pack->data->eth->status->dhcp->server;
        }
        if(msg_pack->data->eth->status->info != NULL)
        {
            memcpy(msg->data.eth.status.info.ip, msg_pack->data->eth->status->info->ip.data, msg_pack->data->eth->status->info->ip.len);
            memcpy(msg->data.eth.status.info.mac, msg_pack->data->eth->status->info->mac.data, msg_pack->data->eth->status->info->mac.len);
        }
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->eth->request == NULL) break;
        msg->data.eth.request.type = msg_pack->data->eth->request->type;
        break;
    default:
        break;
    }
    return 0;
}

int ciot_wifi_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->wifi->config == NULL) break;
        strcpy(msg->data.wifi.config.password, msg_pack->data->wifi->config->password);
        strcpy(msg->data.wifi.config.ssid, msg_pack->data->wifi->config->ssid);
        if(msg_pack->data->wifi->config->tcp != NULL)
        {
            msg->data.wifi.config.tcp.dhcp = msg_pack->data->wifi->config->tcp->dhcp;
            memcpy(msg->data.wifi.config.tcp.dns, msg_pack->data->wifi->config->tcp->dns.data, msg_pack->data->wifi->config->tcp->dns.len);
            memcpy(msg->data.wifi.config.tcp.gateway, msg_pack->data->wifi->config->tcp->gateway.data, msg_pack->data->wifi->config->tcp->gateway.len);
            memcpy(msg->data.wifi.config.tcp.ip, msg_pack->data->wifi->config->tcp->ip.data, msg_pack->data->wifi->config->tcp->ip.len);
            memcpy(msg->data.wifi.config.tcp.mask, msg_pack->data->wifi->config->tcp->mask.data, msg_pack->data->wifi->config->tcp->mask.len);
        }
        msg->data.wifi.config.type = msg_pack->data->wifi->config->type;
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->wifi->status == NULL) break;
        msg->data.wifi.status.disconnect_reason = msg_pack->data->wifi->status->disconnect_reason;
        if(msg_pack->data->wifi->status->info != NULL)
        {
            msg->data.wifi.status.info.authmode = msg_pack->data->wifi->status->info->authmode;
            memcpy(msg->data.wifi.status.info.bssid, msg_pack->data->wifi->status->info->bssid.data, msg_pack->data->wifi->status->info->bssid.len);
            msg->data.wifi.status.info.rssi = msg_pack->data->wifi->status->info->rssi;
            strcpy(msg->data.wifi.status.info.ssid, msg_pack->data->wifi->status->info->ssid);
        }
        if(msg_pack->data->wifi->status->tcp != NULL)
        {
            msg->data.wifi.status.tcp.conn_count = msg_pack->data->wifi->status->tcp->conn_count;
            if(msg_pack->data->wifi->status->tcp->dhcp != NULL)
            {
                msg->data.wifi.status.tcp.dhcp.client = msg_pack->data->wifi->status->tcp->dhcp->client;
                msg->data.wifi.status.tcp.dhcp.server = msg_pack->data->wifi->status->tcp->dhcp->server;
            }
            msg->data.wifi.status.tcp.state = msg_pack->data->wifi->status->tcp->state;
            if(msg_pack->data->wifi->status->tcp->info != NULL)
            {
                memcpy(msg->data.wifi.status.tcp.info.ip, msg_pack->data->wifi->status->tcp->info->ip.data, msg_pack->data->wifi->status->tcp->info->ip.len);
                memcpy(msg->data.wifi.status.tcp.info.mac, msg_pack->data->wifi->status->tcp->info->mac.data, msg_pack->data->wifi->status->tcp->info->mac.len);
            }
            msg->data.wifi.status.tcp.state = msg_pack->data->wifi->status->tcp->state;
        }
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->wifi->request == NULL) break;
        msg->data.wifi.request.type = msg_pack->data->wifi->request->type;
        break;
    default:
        break;
    }
    return 0;
}

int ciot_ble_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->ble->config == NULL) break;
        memcpy(msg->data.ble.config.mac, msg_pack->data->ble->config->mac.data, msg_pack->data->ble->config->mac.len);
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->ble->status == NULL) break;
        msg->data.ble.status.err_code = msg_pack->data->ble->status->err_code;
        msg->data.ble.status.state = msg_pack->data->ble->status->state;
        if(msg_pack->data->ble->status->info == NULL) break;
        memcpy(msg->data.ble.status.info.hw_mac, msg_pack->data->ble->status->info->hw_mac.data, msg_pack->data->ble->status->info->hw_mac.len);
        memcpy(msg->data.ble.status.info.sw_mac, msg_pack->data->ble->status->info->sw_mac.data, msg_pack->data->ble->status->info->sw_mac.len);
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->ble->request == NULL) break;
        msg->data.ble.request.type = msg_pack->data->ble->request->type;
        if(msg->data.ble.request.type == CIOT_BLE_REQ_SET_MAC)
        {
            memcpy(msg->data.ble.request.data.set_mac, msg_pack->data->ble->request->set_mac.data, msg_pack->data->ble->request->set_mac.len);
        }
        break;
    default:
        break;
    }
    return 0;
}

int ciot_ble_scn_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->ble_scn->config == NULL) break;
        msg->data.ble_scn.config.active = msg_pack->data->ble_scn->config->active;
        msg->data.ble_scn.config.brigde_mode = msg_pack->data->ble_scn->config->bridge_mode;
        msg->data.ble_scn.config.interval = msg_pack->data->ble_scn->config->interval;
        msg->data.ble_scn.config.timeout = msg_pack->data->ble_scn->config->timeout;
        msg->data.ble_scn.config.window = msg_pack->data->ble_scn->config->window;
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->ble_scn->status == NULL) break;
        msg->data.ble_scn.status.err_code = msg_pack->data->ble_scn->status->err_code;
        msg->data.ble_scn.status.state = msg_pack->data->ble_scn->status->state;
        if(msg_pack->data->ble_scn->status->adv_info == NULL) break;
        memcpy(msg->data.ble_scn.status.adv_info.mac, msg_pack->data->ble_scn->status->adv_info->mac.data, 6);
        msg->data.ble_scn.status.adv_info.rssi = msg_pack->data->ble_scn->status->adv_info->rssi;
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->ble_scn->request == NULL) break;
        break;
    default:
        break;
    }
    return 0;
}

int ciot_ntp_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->ntp->config == NULL) break;
        msg->data.ntp.config.op_mode = msg_pack->data->ntp->config->op_mode;
        strcpy(msg->data.ntp.config.server[0], msg_pack->data->ntp->config->server1);
        strcpy(msg->data.ntp.config.server[1], msg_pack->data->ntp->config->server2);
        strcpy(msg->data.ntp.config.server[2], msg_pack->data->ntp->config->server3);
        msg->data.ntp.config.sync_interval = msg_pack->data->ntp->config->sync_interval;
        msg->data.ntp.config.sync_mode = msg_pack->data->ntp->config->sync_mode;
        strcpy(msg->data.ntp.config.timezone, msg_pack->data->ntp->config->timezone);
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->ntp->status == NULL) break;
        msg->data.ntp.status.init = msg_pack->data->ntp->status->init;
        msg->data.ntp.status.last_sync = msg_pack->data->ntp->status->last_sync;
        msg->data.ntp.status.state = msg_pack->data->ntp->status->state;
        msg->data.ntp.status.sync = msg_pack->data->ntp->status->sync;
        msg->data.ntp.status.sync_count = msg_pack->data->ntp->status->sync_count;
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->ntp->request == NULL) break;
        msg->data.ntp.request.type = msg_pack->data->ntp->request->type;
        break;
    default:
        break;
    }
    return 0;
}

int ciot_ota_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->ota->config == NULL) break;
        msg->data.ota.config.encrypted = msg_pack->data->ota->config->encrypted;
        msg->data.ota.config.force = msg_pack->data->ota->config->force;
        msg->data.ota.config.restart = msg_pack->data->ota->config->restart;
        strcpy(msg->data.ota.config.url, msg_pack->data->ota->config->url);
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->ota->status == NULL) break;
        msg->data.ota.status.error = msg_pack->data->ota->status->error;
        msg->data.ota.status.image_read = msg_pack->data->ota->status->image_read;
        msg->data.ota.status.image_size = msg_pack->data->ota->status->image_size;
        msg->data.ota.status.state = msg_pack->data->ota->status->state;
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->ota->request == NULL) break;
        msg->data.ota.request.type = msg_pack->data->ota->request->type;
        break;
    default:
        break;
    }
    return 0;
}

int ciot_http_client_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->http_client->config == NULL) break;
        msg->data.httpc.config.method = msg_pack->data->http_client->config->method;
        msg->data.httpc.config.timeout = msg_pack->data->http_client->config->timeout;
        msg->data.httpc.config.transport = msg_pack->data->http_client->config->transport;
        strcpy(msg->data.httpc.config.url, msg_pack->data->http_client->config->url);
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->http_client->status == NULL) break;
        msg->data.httpc.status.error = msg_pack->data->http_client->status->error;
        msg->data.httpc.status.state = msg_pack->data->http_client->status->state;
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->http_client->request == NULL) break;
        msg->data.httpc.request.type = msg_pack->data->http_client->request->type;
        if(msg->data.httpc.request.type == CIOT_HTTPC_REQ_SEND_DATA)
        {
            memcpy(msg->data.httpc.request.data.send.body, msg_pack->data->http_client->request->send->body.data, msg_pack->data->http_client->request->send->body.len);
            msg->data.httpc.request.data.send.content_length = msg_pack->data->http_client->request->send->body.len;
            msg->data.httpc.request.data.send.cfg.method = msg_pack->data->http_client->request->send->config->method;
            msg->data.httpc.request.data.send.cfg.timeout = msg_pack->data->http_client->request->send->config->timeout;
            msg->data.httpc.request.data.send.cfg.transport = msg_pack->data->http_client->request->send->config->transport;
            strcpy(msg->data.httpc.request.data.send.cfg.url, msg_pack->data->http_client->request->send->config->url);
        }
        if(msg->data.httpc.request.type == CIOT_HTTPC_REQ_SET_HEADER)
        {
            strcpy(msg->data.httpc.request.data.set_header.header, msg_pack->data->http_client->request->set_header->header);
            strcpy(msg->data.httpc.request.data.set_header.value, msg_pack->data->http_client->request->set_header->value);
        }
        break;
    default:
        break;
    }
    return 0;
}

int ciot_http_server_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->http_server->config == NULL) break;
        strcpy(msg->data.https.config.address, msg_pack->data->http_server->config->address);
        msg->data.https.config.port = msg_pack->data->http_server->config->port;
        strcpy(msg->data.https.config.route, msg_pack->data->http_server->config->route);
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->http_server->status == NULL) break;
        msg->data.https.status.error = msg_pack->data->http_server->status->error;
        msg->data.https.status.state = msg_pack->data->http_server->status->state;
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->http_server->request == NULL) break;
        msg->data.https.request.type = msg_pack->data->http_client->request->type;
        break;
    default:
        break;
    }
    return 0;
}

int ciot_mqtt_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        if(msg_pack->data->mqtt_client->config == NULL) break;
        strcpy(msg->data.mqtt.config.client_id, msg_pack->data->mqtt_client->config->client_id);
        strcpy(msg->data.mqtt.config.pass, msg_pack->data->mqtt_client->config->password);
        msg->data.mqtt.config.port =msg_pack->data->mqtt_client->config->port;
        msg->data.mqtt.config.qos = msg_pack->data->mqtt_client->config->qos;
        if(msg_pack->data->mqtt_client->config->topics != NULL)
        {
            strcpy(msg->data.mqtt.config.topics.b2d, msg_pack->data->mqtt_client->config->topics->b2d);
            strcpy(msg->data.mqtt.config.topics.d2b, msg_pack->data->mqtt_client->config->topics->d2b);
        }
        msg->data.mqtt.config.transport = msg_pack->data->mqtt_client->config->transport;
        strcpy(msg->data.mqtt.config.url, msg_pack->data->mqtt_client->config->url);
        strcpy(msg->data.mqtt.config.user, msg_pack->data->mqtt_client->config->user);
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        if(msg_pack->data->mqtt_client->status == NULL) break;
        msg->data.mqtt.status.conn_count = msg_pack->data->mqtt_client->status->conn_count;
        msg->data.mqtt.status.data_rate = msg_pack->data->mqtt_client->status->data_rate;
        msg->data.mqtt.status.error.code = msg_pack->data->mqtt_client->status->error->code;
        msg->data.mqtt.status.error.tls_cert_verify_flags = msg_pack->data->mqtt_client->status->error->tls_cert_verify_flags;
        msg->data.mqtt.status.error.tls_last_err = msg_pack->data->mqtt_client->status->error->tls_last_err;
        msg->data.mqtt.status.error.tls_stack_err = msg_pack->data->mqtt_client->status->error->tls_stack_err;
        msg->data.mqtt.status.error.transport_sock = msg_pack->data->mqtt_client->status->error->transport_sock;
        msg->data.mqtt.status.error.type = msg_pack->data->mqtt_client->status->error->type;
        msg->data.mqtt.status.last_msg_time = msg_pack->data->mqtt_client->status->last_msg_time;
        msg->data.mqtt.status.state = msg_pack->data->mqtt_client->status->state;
        break;
    case CIOT_MSG_TYPE_REQUEST:
        if(msg_pack->data->mqtt_client->request == NULL) break;
        msg->data.mqtt.request.type = msg_pack->data->mqtt_client->request->type;
        if(msg->data.mqtt.request.type == CIOT_MQTT_REQ_PUBLISH)
        {
            memcpy(msg->data.mqtt.request.data.publish.msg, msg_pack->data->mqtt_client->request->publish->message.data, msg_pack->data->mqtt_client->request->publish->message.len);
            msg->data.mqtt.request.data.publish.size = msg_pack->data->mqtt_client->request->publish->message.len;
            msg->data.mqtt.request.data.publish.qos = msg_pack->data->mqtt_client->request->publish->qos;
            strcpy(msg->data.mqtt.request.data.publish.topic, msg_pack->data->mqtt_client->request->publish->topic);
        }
        if(msg->data.mqtt.request.type == CIOT_MQTT_REQ_SUBSCRIBE)
        {
            strcpy(msg->data.mqtt.request.data.subscribe.topic, msg_pack->data->mqtt_client->request->subscribe->topic);
            msg->data.mqtt.request.data.subscribe.qos = msg_pack->data->mqtt_client->request->subscribe->qos;
        }
        break;
    default:
        break;
    }
    return 0;
}

int ciot_bridge_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack)
{
    switch (msg->type)
    {
    case CIOT_MSG_TYPE_START:
    case CIOT_MSG_TYPE_GET_CONFIG:
        break;
    case CIOT_MSG_TYPE_GET_STATUS:
        break;
    case CIOT_MSG_TYPE_REQUEST:
        break;
    default:
        break;
    }
    return 0;
}
