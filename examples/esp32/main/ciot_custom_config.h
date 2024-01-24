/**
 * @file ciot_custom_config.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-11-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_CUSTOM_CONFIG__H__
#define __CIOT_CUSTOM_CONFIG__H__

#define CIOT_CONFIG_LOG_LEVEL CIOT_LOG_LEVEL_INFO
#define CIOT_CONFIG_APP_VER 0,3,0
#define CIOT_CONFIG_HARDWARE_NAME "CIOT BOARD ESP32"
#define CIOT_CONFIG_FEATURE_STORAGE 1  ///!< Enable Storage
#define CIOT_CONFIG_FEATURE_SYSTEM 1   ///!< Enable System
#define CIOT_CONFIG_FEATURE_UART 1     ///!< Enable UART
#define CIOT_CONFIG_FEATURE_USB 0      ///!< Enable USB
#define CIOT_CONFIG_FEATURE_BLE 0      ///!< Enable Bluetooth
#define CIOT_CONFIG_FEATURE_BLE_SCN 0  ///!< Enable Bluetooth Scanner
#define CIOT_CONFIG_FEATURE_ETHERNET 1 ///!< Enable Ethernet
#define CIOT_CONFIG_FEATURE_WIFI 1     ///!< Enable WiFi
#define CIOT_CONFIG_FEATURE_NTP 1      ///!< Enable NTP
#define CIOT_CONFIG_FEATURE_OTA 1      ///!< Enable OTA
#define CIOT_CONFIG_FEATURE_HTTPS 1    ///!< Enable HTTP Server
#define CIOT_CONFIG_FEATURE_HTTPC 1    ///!< Enable HTTP Client
#define CIOT_CONFIG_FEATURE_MQTTC 1    ///!< Enable MQTT Client
#define CIOT_CONFIG_MESSAGE_LEN 330    ///!< Ciot expected message size
#define CIOT_CONFIG_MESSAGE_PAYLOAD_LEN 300 ///! Ciot expected message payload size

#define CIOT_CONFIG_ETH_PHY_KSZ8081 1
#define CIOT_CONFIG_ETH_PHY_NEW(x) esp_eth_phy_new_ksz80xx(&x)
#define CIOT_CONFIG_ETH_PHY_ADDR 0
#define CIOT_CONFIG_ETH_GPIO_PHY_RST 5
#define CIOT_CONFIG_ETH_GPIO_MDC 23
#define CIOT_CONFIG_ETH_GPIO_MDIO 18

#define CIOT_CONFIG_WIFI_AP_SSID_MASK "CIOT BOARD %s"
#define CIOT_CONFIG_WIFI_AP_PASS "administrator"
#define CIOT_CONFIG_WIFI_AP_AUTH WIFI_AUTH_WPA_WPA2_PSK
#define CIOT_CONFIG_WIFI_AP_MAX_CONN 1

#define CIOT_CONFIG_UART_RX_BUF_SIZE 256
#define CIOT_CONFIG_UART_TX_BUF_SIZE 256
#define CIOT_CONFIG_UART_QUEUE_SIZE 20
#define CIOT_CONFIG_UART_TASK_SIZE 2048
#define CIOT_CONFIG_UART_TASK_PRIO 12
#define CIOT_CONFIG_UART_TASK_CORE 0
#define CIOT_CONFIG_UART_BAUD 115200
#define CIOT_CONFIG_UART_PORT 20
#define CIOT_CONFIG_UART_DTR true

#define CIOT_CONFIG_NTP_OP_MODE 0
#define CIOT_CONFIG_NTP_SYNC_MODE 0
#define CIOT_CONFIG_NTP_SYNC_INTERVAL (3600 * 1000)
#define CIOT_CONFIG_NTP_TZ "<-03>3"
#define CIOT_CONFIG_NTP_SERVERS_COUNT 3
#define CIOT_CONFIG_NTP_SERVER1 "pool.ntp.org"
#define CIOT_CONFIG_NTP_SERVER2 "time.google.com"
#define CIOT_CONFIG_NTP_SERVER3 "gps.ntp.br"

#define CIOT_CONFIG_HTTPS_ADDRESS "http://127.0.0.1:8080"
#define CIOT_CONFIG_HTTPS_ROUTE "/v1/ciot"

#define CIOT_CONFIG_HTTPC_URL "http://127.0.0.1:8181"
#define CIOT_CONFIG_HTTPC_TRANSPORT CIOT_HTTPC_TRANSPORT_TCP
#define CIOT_CONFIG_HTTPC_METHOD CIOT_HTTPC_METHOD_POST
#define CIOT_CONFIG_HTTPC_TIMEOUT 5000

#define CIOT_CONFIG_MQTTC_ID "ciot_esp32_sample"
#define CIOT_CONFIG_MQTTC_URL "mqtt://test.mosquitto.org"
#define CIOT_CONFIG_MQTTC_PORT 1883
#define CIOT_CONFIG_MQTTC_QOS 0
#define CIOT_CONFIG_MQTTC_TOPIC_B2D "CIOT/B2D/esp32"
#define CIOT_CONFIG_MQTTC_TOPIC_D2B "CIOT/D2B/esp32"

#endif //!__CIOT_CUSTOM_CONFIG__H__