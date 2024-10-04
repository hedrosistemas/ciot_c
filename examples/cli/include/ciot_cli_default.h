/**
 * @file ciot_cli_default.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-09-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __CIOT_CLI_DEFAULT__H__
#define __CIOT_CLI_DEFAULT__H__

#define DEFAULT_ARGC_LIST 2
#define DEFAULT_ARGV_LIST { \
    "ciot_cli",             \
    "list",                 \
}

#define DEFAULT_ARGC_CONN_GET 3
#define DEFAULT_ARGV_CONN_GET { \
    "ciot_cli",                 \
    "conn",                     \
    "get",                      \
}

#define DEFAULT_ARGC_CONN_TEST 3
#define DEFAULT_ARGV_CONN_TEST { \
    "ciot_cli",                  \
    "conn",                      \
    "test",                      \
}

#define DEFAULT_ARGC_CONN_HTTP 4
#define DEFAULT_ARGV_CONN_HTTP {       \
    "ciot_cli",                        \
    "conn",                            \
    "http",                            \
    "http://192.168.4.1:8080/v1/ciot", \
}

#define DEFAULT_ARGC_SYS_RST 4
#define DEFAULT_ARGV_SYS_RST { \
    "ciot_cli",                \
    "sys",                     \
    "rst",                     \
    "1",                       \
}

#define DEFAULT_ARGC_SYS_INF 4
#define DEFAULT_ARGV_SYS_INF { \
    "ciot_cli",                \
    "sys",                     \
    "info",                    \
    "1",                       \
}

#define DEFAULT_ARGC_WIFI_STA_STOP 5
#define DEFAULT_ARGV_WIFI_STA_STOP { \
    "ciot_cli",                      \
    "wifi",                          \
    "sta",                           \
    "stop",                          \
    "5",                             \
}

#define DEFAULT_ARGC_WIFI_STA_START 7
#define DEFAULT_ARGV_WIFI_STA_START { \
    "ciot_cli",                       \
    "wifi",                           \
    "sta",                            \
    "start",                          \
    "WIFI SSID",                      \
    "WIFI PASS",                      \
    "5",                              \
}

#define DEFAULT_ARGC_MQTTC_START 10
#define DEFAULT_ARGV_MQTTC_START {    \
    "ciot_cli",                       \
    "mqttc",                          \
    "start",                          \
    "ciot-client-id-1253",            \
    "mqtt://test.mosquitto.org:1883", \
    "",                               \
    "",                               \
    "ciot/pub",                       \
    "ciot/sub",                       \
    "7",                              \
}

#endif //!__CIOT_CLI_DEFAULT__H__