/**
 * @file ciot_mqttc_types.h
 * @ingroup software_types
 * @brief Defines data types and structures for CIOT MQTT client.
 * @version 0.1
 * @date 2023-10-09
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_MQTT_DATA__H__
#define __CIOT_MQTT_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <time.h>

#include "ciot_common_types.h"

/** Default length of MQTT client ID */
#ifndef CIOT_CONFIG_MQTT_CLIENT_ID_LEN
#define CIOT_CONFIG_MQTT_CLIENT_ID_LEN 32
#endif
/** Default length of MQTT URL */
#ifndef CIOT_CONFIG_MQTT_URL_LEN
#define CIOT_CONFIG_MQTT_URL_LEN 64
#endif
/** Default length of MQTT username */
#ifndef CIOT_CONFIG_MQTT_USER_LEN
#define CIOT_CONFIG_MQTT_USER_LEN 32
#endif
/** Default length of MQTT password */
#ifndef CIOT_CONFIG_MQTT_PASS_LEN
#define CIOT_CONFIG_MQTT_PASS_LEN 32
#endif
/** Default length of MQTT topic */
#ifndef CIOT_CONFIG_MQTT_TOPIC_LEN
#define CIOT_CONFIG_MQTT_TOPIC_LEN 48
#endif
/** Default length of MQTT message */
#ifndef CIOT_CONFIG_MQTT_MSG_LEN
#define CIOT_CONFIG_MQTT_MSG_LEN 256
#endif

/**
 * @brief Enumeration for CIOT MQTT client states.
 */
typedef enum __attribute__((packed))
{
    CIOT_MQTT_STATE_ERROR = -1, /**< Error state */
    CIOT_MQTT_STATE_DISCONNECTED, /**< Disconnected state */
    CIOT_MQTT_STATE_CONNECTING, /**< Connecting state */
    CIOT_MQTT_STATE_DISCONNECTING, /**< Disconnecting state */
    CIOT_MQTT_STATE_CONNECTED, /**< Connected state */
} ciot_mqttc_state_t;

/**
 * @brief Enumeration for CIOT MQTT client transport types.
 */
typedef enum __attribute__((packed))
{
    CIOT_MQTT_TRANSPORT_UNKNOWN, /**< Unknown transport type */
    CIOT_MQTT_TRANSPORT_OVER_TCP, /**< TCP transport type */
    CIOT_MQTT_TRANSPORT_OVER_SSL, /**< SSL transport type */
    CIOT_MQTT_TRANSPORT_OVER_WS, /**< WebSocket transport type */
    CIOT_MQTT_TRANSPORT_OVER_WSS, /**< Secure WebSocket transport type */
} ciot_mqttc_transport_t;

/**
 * @brief Enumeration for CIOT MQTT client request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_MQTT_REQ_UNKNONW, /**< Unknown request type */
    CIOT_MQTT_REQ_PUBLISH, /**< Publish request type */
    CIOT_MQTT_REQ_SUBSCRIBE, /**< Subscribe request type */
} ciot_mqttc_req_type_t;

/**
 * @brief Structure for CIOT MQTT client error information.
 */
typedef struct __attribute__((packed))
{
    int tls_last_err; /**< Last TLS error */
    int tls_stack_err; /**< TLS stack error */
    int tls_cert_verify_flags; /**< TLS certificate verification flags */
    int type; /**< Error type */
    int code; /**< Error code */
    int transport_sock; /**< Transport socket */
} ciot_mqttc_error_t;

/**
 * @brief Structure for CIOT MQTT client topics configuration.
 */
typedef struct __attribute__((packed))
{
    char d2b[CIOT_CONFIG_MQTT_TOPIC_LEN]; /**< Device to broker topic */
    char b2d[CIOT_CONFIG_MQTT_TOPIC_LEN]; /**< Broker to device topic */
} ciot_mqttc_topics_cfg_t;

/**
 * @brief Structure for CIOT MQTT client configuration.
 */
typedef struct __attribute__((packed))
{
    char client_id[CIOT_CONFIG_MQTT_CLIENT_ID_LEN]; /**< Client ID */
    char url[CIOT_CONFIG_MQTT_URL_LEN]; /**< MQTT URL */
    char user[CIOT_CONFIG_MQTT_USER_LEN]; /**< MQTT username */
    char pass[CIOT_CONFIG_MQTT_PASS_LEN]; /**< MQTT password */
    uint32_t port; /**< MQTT port */
    uint8_t qos; /**< MQTT quality of service */
    ciot_mqttc_transport_t transport; /**< MQTT transport type */
    ciot_mqttc_topics_cfg_t topics; /**< MQTT topics configuration */
} ciot_mqttc_cfg_t;

/**
 * @brief Structure for CIOT MQTT client status.
 */
typedef struct __attribute__((packed))
{
    ciot_mqttc_state_t state; /**< MQTT client state */
    uint8_t conn_count; /**< Connection count */
    uint16_t data_rate; /**< Data rate */
    time_t last_msg_time; /**< Last message time */
    ciot_mqttc_error_t error; /**< Error information */
} ciot_mqttc_status_t;

/**
 * @brief Structure for CIOT MQTT client publish request.
 */
typedef struct __attribute__((packed))
{
    char topic[CIOT_CONFIG_MQTT_TOPIC_LEN]; /**< MQTT topic */
    uint8_t msg[CIOT_CONFIG_MQTT_MSG_LEN]; /**< MQTT message */
    int size; /**< Size of message */
    uint8_t qos; /**< Quality of service */
} ciot_mqttc_req_publish_t;

/**
 * @brief Structure for CIOT MQTT client subscribe request.
 */
typedef struct __attribute__((packed))
{
    char topic[CIOT_CONFIG_MQTT_TOPIC_LEN]; /**< MQTT topic */
    uint8_t qos; /**< Quality of service */
} ciot_mqttc_req_subscribe_t;

/**
 * @brief Union for CIOT MQTT client request data.
 */
typedef union __attribute__((packed))
{
    ciot_mqttc_req_publish_t publish; /**< Publish request data */
    ciot_mqttc_req_subscribe_t subscribe; /**< Subscribe request data */
} ciot_mqttc_req_data_u;

/**
 * @brief Structure for CIOT MQTT client request.
 */
typedef struct __attribute__((packed))
{
    ciot_mqttc_req_type_t type; /**< Request type */
    ciot_mqttc_req_data_u data; /**< Request data */
} ciot_mqttc_req_t;

/**
 * @brief Structure for CIOT MQTT client event data.
 */
typedef struct ciot_mqttc_event_data
{
    ciot_event_data_t payload; /**< Event payload */
    char *topic; /**< Event topic */
} ciot_mqttc_event_data_t;

/**
 * @brief Union for CIOT MQTT client event.
 */
typedef struct ciot_mqttc_event
{
    ciot_mqttc_event_data_t data; /**< Event data */
} ciot_mqttc_event_u;

/**
 * @brief Union for CIOT MQTT client data.
 */
typedef union __attribute__((packed))
{
    ciot_mqttc_cfg_t config; /**< Configuration data */
    ciot_mqttc_status_t status; /**< Status data */
    ciot_mqttc_req_t request; /**< Request data */
    ciot_mqttc_event_u event; /**< Event data */
} ciot_mqttc_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_MQTT_DATA__H__
