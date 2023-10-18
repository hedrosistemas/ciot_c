/**
 * @file ciot_config.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_CONFIG__H__
#define __CIOT_CONFIG__H__

#define CIOT_CONFIG_FEATURE_SERIAL 1   ///!< Enable Serial
#define CIOT_CONFIG_FEATURE_ETHERNET 1 ///!< Enable Ethernet
#define CIOT_CONFIG_FEATURE_WIFI 1     ///!< Enable WiFi
#define CIOT_CONFIG_FEATURE_HTTPS 1    ///!< Enable HTTP Server
#define CIOT_CONFIG_FEATURE_HTTPC 1    ///!< Enable HTTP Client
#define CIOT_CONFIG_FEATURE_MQTTC 1    ///!< Enable MQTT Client
#define CIOT_CONFIG_MESSAGE_LEN 240    ///!< CIOT expected message size
// #define CIOT_CONFIG_MESSAGE_LEN sizeof(ciot_msg_u)

#define CIOT_CONFIG_ETH_PHY_KSZ8081 1
#define CIOT_CONFIG_ETH_PHY_NEW(x) esp_eth_phy_new_ksz80xx(&x)
#define CIOT_CONFIG_ETH_PHY_ADDR 0
#define CIOT_CONFIG_ETH_GPIO_PHY_RST 5
#define CIOT_CONFIG_ETH_GPIO_MDC 23
#define CIOT_CONFIG_ETH_GPIO_MDIO 18

#define CIOT_CONFIG_WIFI_AP_SSID_MASK "HEDRO HG3 %s"
#define CIOT_CONFIG_WIFI_AP_PASS "administrator"
#define CIOT_CONFIG_WIFI_AP_AUTH WIFI_AUTH_WPA_WPA2_PSK
#define CIOT_CONFIG_WIFI_AP_MAX_CONN 1

#define CIOT_CONFIG_WIFI_STA_SSID "CABO CANAVERAL"
#define CIOT_CONFIG_WIFI_STA_PASS "16192020"

#endif //!__CIOT_CONFIG__H__