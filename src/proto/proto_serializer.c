/**
 * @file proto_serializer.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <string.h>
#include <stdlib.h>

#include "proto_serializer.h"
#include "ciot/proto/v1/msg.pb-c.h"

static const char *TAG = "proto_serializer";

int ciot_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_storage_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_system_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_uart_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_usb_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_tcp_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_eth_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_wifi_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_ble_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_ble_scn_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_ntp_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_ota_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_http_client_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_http_server_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_mqtt_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);
int ciot_bridge_pack(Ciot__Msg *msg_pack, ciot_msg_t *msg, uint8_t *bytes);

int ciot_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_storage_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_system_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_uart_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_usb_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_tcp_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_eth_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_wifi_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_ble_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_ble_scn_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_ntp_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_ota_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_http_client_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_http_server_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_mqtt_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);
int ciot_bridge_unpack(ciot_msg_t *msg, Ciot__Msg *msg_pack);

ciot_serializer_t proto_serializer_new(void)
{
    ciot_serializer_t self = calloc(1, sizeof(struct ciot_serializer));
    self->type = CIOT_SERIALIZER_TYPE_PROTOBUF;
    self->from_bytes = proto_serializer_from_bytes;
    self->to_bytes = proto_serializer_to_bytes;
    return self;
}

int proto_serializer_to_bytes(uint8_t *bytes, ciot_msg_t *msg)
{
    Ciot__Msg msg_pack = CIOT__MSG__INIT;
    Ciot__InterfaceInfo iface = CIOT__INTERFACE_INFO__INIT;
    Ciot__MsgData data = CIOT__MSG_DATA__INIT;

    msg_pack.iface = &iface;
    msg_pack.data = &data;

    msg_pack.id = msg->id;
    msg_pack.type = msg->type;
    msg_pack.iface->id = msg->iface.id;
    msg_pack.iface->type = msg->iface.type;

    if(msg->type == CIOT_MSG_TYPE_ERROR)
    {
        Ciot__MsgError error = CIOT__MSG_ERROR__INIT;
        msg_pack.data->error = &error;
        msg_pack.data->error->code = msg->data.error.code;
        msg_pack.data->error->msg_type = msg->data.error.msg_type;
        return ciot__msg__pack(&msg_pack, bytes);
    }

    switch (msg->iface.type)
    {
        case CIOT_IFACE_TYPE_UNKNOWN:
            return ciot__msg__pack(&msg_pack, bytes);
        case CIOT_IFACE_TYPE_CIOT:
            return ciot_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_STORAGE:
            return ciot_storage_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_SYSTEM:
            return ciot_system_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_UART:
            return ciot_uart_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_USB:
            return ciot_usb_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_TCP:
            return ciot_tcp_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_ETH:
            return ciot_eth_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_WIFI:
            return ciot_wifi_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_BLE:
            return ciot_ble_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_BLE_SCN:
            return ciot_ble_scn_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_NTP:
            return ciot_ntp_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_OTA:
            return ciot_ota_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_HTTP_CLIENT:
            return ciot_http_client_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_HTTP_SERVER:
            return ciot_http_server_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_MQTT:
            return ciot_mqtt_pack(&msg_pack, msg, bytes);
        case CIOT_IFACE_TYPE_BRIDGE:
            return ciot_bridge_pack(&msg_pack, msg, bytes);
    default:
        return ciot__msg__pack(&msg_pack, bytes);
    }
}

int proto_serializer_from_bytes(ciot_msg_t *msg, uint8_t *bytes, int size)
{
    Ciot__Msg *msg_pack = ciot__msg__unpack(NULL, size, bytes);

    msg->id = msg_pack->id;
    msg->type = msg_pack->type;
    msg->iface.id = msg_pack->iface->id;
    msg->iface.type = msg_pack->iface->type;

    CIOT_LOG_BUFFER_HEX(TAG, bytes, size);

    if(msg_pack->data == NULL)
    {
        return 0;
    }

    switch (msg->iface.type)
    {
        case CIOT_IFACE_TYPE_UNKNOWN:
            return 0;
        case CIOT_IFACE_TYPE_CIOT:
            return ciot_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_STORAGE:
            return ciot_storage_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_SYSTEM:
            return ciot_system_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_UART:
            return ciot_uart_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_USB:
            return ciot_usb_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_TCP:
            return ciot_tcp_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_ETH:
            return ciot_eth_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_WIFI:
            return ciot_wifi_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_BLE:
            return ciot_ble_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_BLE_SCN:
            return ciot_ble_scn_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_NTP:
            return ciot_ntp_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_OTA:
            return ciot_ota_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_HTTP_CLIENT:
            return ciot_http_client_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_HTTP_SERVER:
            return ciot_http_server_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_MQTT:
            return ciot_mqtt_unpack(msg, msg_pack);
        case CIOT_IFACE_TYPE_BRIDGE:
            return ciot_bridge_unpack(msg, msg_pack);
    default:
        return 0;
    }
}
