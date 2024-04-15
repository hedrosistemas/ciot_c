/**
 * @file ciot_default.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-04-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __CIOT_DEFAULT__H__
#define __CIOT_DEFAULT__H__

#define CIOT_CONFIG_STORAGE_TYPE CIOT_STORAGE_TYPE_FS

#define CIOT_CONFIG_UART_BAUD_RATE 115200
#define CIOT_CONFIG_UART_NUM 0
#define CIOT_CONFIG_UART_RX_PIN 0
#define CIOT_CONFIG_UART_TX_PIN 0
#define CIOT_CONFIG_UART_RTS_PIN 0
#define CIOT_CONFIG_UART_CTS_PIN 0
#define CIOT_CONFIG_UART_FLOW_CONTROL 0
#define CIOT_CONFIG_UART_PARITY 0
#define CIOT_CONFIG_UART_DTR 0
#define CIOT_CONFIG_UART_BRIDGE_MODE 0

#define CIOT_CONFIG_TCP_DHCP CIOT_TCP_DHCP_CFG_NO_CHANGE
#define CIOT_CONFIG_TCP_IP 0, 0, 0, 0
#define CIOT_CONFIG_TCP_GATEWAY 0, 0, 0, 0
#define CIOT_CONFIG_TCP_MASK 0, 0, 0, 0
#define CIOT_CONFIG_TCP_DNS 0, 0, 0, 0

#define CIOT_CONFIG_WIFI_AP_SSID "Ciot AP"
#define CIOT_CONFIG_WIFI_AP_PASSWORD "administrator"
#define CIOT_CONFIG_WIFI_AP_TCP CIOT_CONFIG_TCP

#define CIOT_CONFIG_WIFI_STA_SSID "Ciot STA"
#define CIOT_CONFIG_WIFI_STA_PASSWORD "administrator"
#define CIOT_CONFIG_WIFI_STA_TCP CIOT_CONFIG_TCP

#define CIOT_CONFIG_ETH CIOT_CONFIG_TCP

#define CIOT_CONFIG_NTP_OP_MODE 0
#define CIOT_CONFIG_NTP_SYNC_MODE 0
#define CIOT_CONFIG_NTP_SYNC_INTERVAL 0
#define CIOT_CONFIG_NTP_SERVERS_COUNT 3
#define CIOT_CONFIG_NTP_SERVER1 "pool.ntp.org"
#define CIOT_CONFIG_NTP_SERVER2 "time.google.com"
#define CIOT_CONFIG_NTP_SERVER3 "gps.ntp.br"

#define CIOT_CONFIG_HTTPC_URL "http://127.0.0.1:8080/v1/ciot"
#define CIOT_CONFIG_HTTPC_TRANSPORT CIOT_HTTPC_TRANSPORT_TCP
#define CIOT_CONFIG_HTTPC_METHOD CIOT_HTTPC_METHOD_POST
#define CIOT_CONFIG_HTTPC_TIMEOUT 20000

#define CIOT_CONFIG_HTTPS_ADDRESS "http://127.0.0.1"
#define CIOT_CONFIG_HTTPS_ROUTE "/v1/ciot"
#define CIOT_CONFIG_HTTPS_PORT 8080

#define CIOT_CONFIG_MQTTC_URL "mqtt://test.mosquitto.org"
#define CIOT_CONFIG_MQTTC_PORT 1883
#define CIOT_CONFIG_MQTTC_QOS 0
#define CIOT_CONFIG_MQTTC_USER ""
#define CIOT_CONFIG_MQTTC_PASS ""
#define CIOT_CONFIG_MQTTC_TOPIC_D2B "v1/ciot/d2b"
#define CIOT_CONFIG_MQTTC_TOPIC_B2D "v1/ciot/b2d"

#define CIOT_CONFIG_SYS \
    {                      \
    }

#define CIOT_CONFIG_STORAGE          \
    {                                \
        .type = CIOT_STORAGE_TYPE_FS \
    }

#define CIOT_CONFIG_UART                               \
    {                                                  \
        .baud_rate = CIOT_CONFIG_UART_BAUD_RATE,       \
        .num = CIOT_CONFIG_UART_NUM,                   \
        .rx_pin = CIOT_CONFIG_UART_RX_PIN,             \
        .tx_pin = CIOT_CONFIG_UART_TX_PIN,             \
        .rts_pin = CIOT_CONFIG_UART_RTS_PIN,           \
        .cts_pin = CIOT_CONFIG_UART_CTS_PIN,           \
        .flow_control = CIOT_CONFIG_UART_FLOW_CONTROL, \
        .parity = CIOT_CONFIG_UART_PARITY,             \
        .dtr = CIOT_CONFIG_UART_DTR,                   \
        .bridge_mode = CIOT_CONFIG_UART_BRIDGE_MODE,   \
    }

#define CIOT_CONFIG_TCP                       \
    {                                         \
        .dhcp = CIOT_TCP_DHCP_CFG_NO_CHANGE,  \
        .ip = {CIOT_CONFIG_TCP_IP},           \
        .gateway = {CIOT_CONFIG_TCP_GATEWAY}, \
        .mask = {CIOT_CONFIG_TCP_MASK},       \
        .dns = {CIOT_CONFIG_TCP_DNS},         \
    }

#define CIOT_CONFIG_WIFI_AP                       \
    {                                             \
        .ssid = CIOT_CONFIG_WIFI_AP_SSID,         \
        .password = CIOT_CONFIG_WIFI_AP_PASSWORD, \
        .tcp = CIOT_CONFIG_WIFI_AP_TCP,           \
        .type = CIOT_WIFI_IF_AP,                  \
    }

#define CIOT_CONFIG_WIFI_STA                       \
    {                                              \
        .ssid = CIOT_CONFIG_WIFI_STA_SSID,         \
        .password = CIOT_CONFIG_WIFI_STA_PASSWORD, \
        .tcp = CIOT_CONFIG_WIFI_STA_TCP,           \
        .type = CIOT_WIFI_IF_STA,                  \
    }

#define HG_TCP_CONFIG_NTP                                 \
    {                                                     \
        .op_mode = HG_TCP_CONFIG_NTP_OP_MODE,             \
        .sync_mode = HG_TCP_CONFIG_NTP_SYNC_MODE,         \
        .sync_interval = HG_TCP_CONFIG_NTP_SYNC_INTERVAL, \
        .server = {                                       \
            {CIOT_CONFIG_NTP_SERVER1},                    \
            {CIOT_CONFIG_NTP_SERVER2},                    \
            {CIOT_CONFIG_NTP_SERVER3}                     \
        }                                                 \
    }

#define CIOT_CONFIG_HTTPC                         \
    {                                             \
        .url = CIOT_CONFIG_HTTPC_URL,             \
        .method = CIOT_CONFIG_HTTPC_METHOD,       \
        .transport = CIOT_CONFIG_HTTPC_TRANSPORT, \
        .timeout = CIOT_CONFIG_HTTPC_TIMEOUT,     \
    }

#define HG_TCP_CONFIG_HTTPS                     \
    {                                           \
        .address = HG_TCP_CONFIG_HTTPS_ADDRESS, \
        .route = HG_TCP_CONFIG_HTTPS_ROUTE,     \
        .port = HG_TCP_CONFIG_HTTPS_PORT,       \
    }

#define HG_TCP_CONFIG_MQTTC                     \
    {                                           \
        .url = CIOT_CONFIG_MQTTC_URL,           \
        .port = CIOT_CONFIG_MQTTC_PORT,         \
        .qos = CIOT_CONFIG_MQTTC_QOS,           \
        .topics = {                             \
            .b2d = CIOT_CONFIG_MQTTC_TOPIC_B2D, \
            .d2b = CIOT_CONFIG_MQTTC_TOPIC_D2B, \
        }                                       \
    }

#endif //!__CIOT_DEFAULT__H__
