/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/mqtt_client.proto */

#ifndef PROTOBUF_C_ciot_2fproto_2fv1_2fmqtt_5fclient_2eproto__INCLUDED
#define PROTOBUF_C_ciot_2fproto_2fv1_2fmqtt_5fclient_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Ciot__MqttClientError Ciot__MqttClientError;
typedef struct _Ciot__MqttClientTopicsCfg Ciot__MqttClientTopicsCfg;
typedef struct _Ciot__MqttClientCfg Ciot__MqttClientCfg;
typedef struct _Ciot__MqttClientStatus Ciot__MqttClientStatus;
typedef struct _Ciot__MqttClientReqPublish Ciot__MqttClientReqPublish;
typedef struct _Ciot__MqttClientReqSubscribe Ciot__MqttClientReqSubscribe;
typedef struct _Ciot__MqttClientReq Ciot__MqttClientReq;
typedef struct _Ciot__MqttClientData Ciot__MqttClientData;


/* --- enums --- */

/*
 * Enum representing the state of the MQTT client.
 */
typedef enum _Ciot__MqttClientState {
  /*
   * The MQTT client is disconnected.
   */
  CIOT__MQTT_CLIENT_STATE__MQTT_STATE_DISCONNECTED = 0,
  /*
   * The MQTT client is connecting.
   */
  CIOT__MQTT_CLIENT_STATE__MQTT_STATE_CONNECTING = 1,
  /*
   * The MQTT client is disconnecting.
   */
  CIOT__MQTT_CLIENT_STATE__MQTT_STATE_DISCONNECTING = 2,
  /*
   * The MQTT client is connected.
   */
  CIOT__MQTT_CLIENT_STATE__MQTT_STATE_CONNECTED = 3,
  /*
   * The MQTT client encountered an error.
   */
  CIOT__MQTT_CLIENT_STATE__MQTT_STATE_ERROR = -1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__MQTT_CLIENT_STATE)
} Ciot__MqttClientState;
/*
 * Enum representing different transports for MQTT communication.
 */
typedef enum _Ciot__MqttClientTransport {
  /*
   * Unknown MQTT transport.
   */
  CIOT__MQTT_CLIENT_TRANSPORT__MQTT_TRANSPORT_UNKNOWN = 0,
  /*
   * MQTT over TCP.
   */
  CIOT__MQTT_CLIENT_TRANSPORT__MQTT_TRANSPORT_OVER_TCP = 1,
  /*
   * MQTT over SSL.
   */
  CIOT__MQTT_CLIENT_TRANSPORT__MQTT_TRANSPORT_OVER_SSL = 2,
  /*
   * MQTT over WebSocket.
   */
  CIOT__MQTT_CLIENT_TRANSPORT__MQTT_TRANSPORT_OVER_WS = 3,
  /*
   * MQTT over Secure WebSocket.
   */
  CIOT__MQTT_CLIENT_TRANSPORT__MQTT_TRANSPORT_OVER_WSS = 4
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__MQTT_CLIENT_TRANSPORT)
} Ciot__MqttClientTransport;
/*
 * Enum representing different types of MQTT client requests.
 */
typedef enum _Ciot__MqttClientReqType {
  /*
   * Unknown MQTT request type.
   */
  CIOT__MQTT_CLIENT_REQ_TYPE__MQTT_REQ_TYPE_UNKOWN = 0,
  /*
   * MQTT publish request.
   */
  CIOT__MQTT_CLIENT_REQ_TYPE__MQTT_REQ_TYPE_PUBLISH = 1,
  /*
   * MQTT subscribe request.
   */
  CIOT__MQTT_CLIENT_REQ_TYPE__MQTT_REQ_TYPE_SUBSCRIBE = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__MQTT_CLIENT_REQ_TYPE)
} Ciot__MqttClientReqType;

/* --- messages --- */

/*
 * Message representing error details for the MQTT client.
 */
struct  _Ciot__MqttClientError
{
  ProtobufCMessage base;
  /*
   * TLS last error code.
   */
  int32_t tls_last_err;
  /*
   * TLS stack error code.
   */
  int32_t tls_stack_err;
  /*
   * TLS certificate verification flags.
   */
  int32_t tls_cert_verify_flags;
  /*
   * Type of the error.
   */
  int32_t type;
  /*
   * Error code.
   */
  int32_t code;
  /*
   * Transport socket error.
   */
  int32_t transport_sock;
};
#define CIOT__MQTT_CLIENT_ERROR__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__mqtt_client_error__descriptor) \
    , 0, 0, 0, 0, 0, 0 }


/*
 * Message representing configuration for MQTT client topics.
 */
struct  _Ciot__MqttClientTopicsCfg
{
  ProtobufCMessage base;
  /*
   * Device to broker topic.
   */
  char *d2b;
  /*
   * Broker to device topic.
   */
  char *b2d;
};
#define CIOT__MQTT_CLIENT_TOPICS_CFG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__mqtt_client_topics_cfg__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


/*
 * Message representing configuration for the MQTT client.
 */
struct  _Ciot__MqttClientCfg
{
  ProtobufCMessage base;
  /*
   * Client ID for MQTT connection.
   */
  char *client_id;
  /*
   * URL for MQTT connection.
   */
  char *url;
  /*
   * Username for MQTT authentication.
   */
  char *user;
  /*
   * Password for MQTT authentication.
   */
  char *password;
  /*
   * Port for MQTT connection.
   */
  uint32_t port;
  /*
   * Quality of Service level for MQTT communication.
   */
  uint32_t qos;
  /*
   * Transport type for MQTT communication.
   */
  Ciot__MqttClientTransport transport;
  /*
   * Topics configuration for MQTT communication.
   */
  Ciot__MqttClientTopicsCfg *topics;
};
#define CIOT__MQTT_CLIENT_CFG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__mqtt_client_cfg__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, 0, 0, CIOT__MQTT_CLIENT_TRANSPORT__MQTT_TRANSPORT_UNKNOWN, NULL }


/*
 * Message representing status information for the MQTT client.
 */
struct  _Ciot__MqttClientStatus
{
  ProtobufCMessage base;
  /*
   * State of the MQTT client.
   */
  Ciot__MqttClientState state;
  /*
   * Connection count.
   */
  uint32_t conn_count;
  /*
   * Data rate.
   */
  uint32_t data_rate;
  /*
   * Timestamp of the last message.
   */
  uint64_t last_msg_time;
  /*
   * Error details for the MQTT client.
   */
  Ciot__MqttClientError *error;
};
#define CIOT__MQTT_CLIENT_STATUS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__mqtt_client_status__descriptor) \
    , CIOT__MQTT_CLIENT_STATE__MQTT_STATE_DISCONNECTED, 0, 0, 0, NULL }


/*
 * Message representing a publish request for the MQTT client.
 */
struct  _Ciot__MqttClientReqPublish
{
  ProtobufCMessage base;
  /*
   * Topic for publishing.
   */
  char *topic;
  /*
   * Message payload.
   */
  ProtobufCBinaryData message;
  /*
   * Quality of Service level for the publish request.
   */
  int32_t qos;
};
#define CIOT__MQTT_CLIENT_REQ_PUBLISH__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__mqtt_client_req_publish__descriptor) \
    , (char *)protobuf_c_empty_string, {0,NULL}, 0 }


/*
 * Message representing a subscribe request for the MQTT client.
 */
struct  _Ciot__MqttClientReqSubscribe
{
  ProtobufCMessage base;
  /*
   * Topic to subscribe to.
   */
  char *topic;
  /*
   * Quality of Service level for the subscribe request.
   */
  int32_t qos;
};
#define CIOT__MQTT_CLIENT_REQ_SUBSCRIBE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__mqtt_client_req_subscribe__descriptor) \
    , (char *)protobuf_c_empty_string, 0 }


/*
 * Message representing a request for the MQTT client.
 */
struct  _Ciot__MqttClientReq
{
  ProtobufCMessage base;
  /*
   * Type of the MQTT client request.
   */
  Ciot__MqttClientReqType type;
  /*
   * Publish request.
   */
  Ciot__MqttClientReqPublish *publish;
  /*
   * Subscribe request.
   */
  Ciot__MqttClientReqSubscribe *subscribe;
};
#define CIOT__MQTT_CLIENT_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__mqtt_client_req__descriptor) \
    , CIOT__MQTT_CLIENT_REQ_TYPE__MQTT_REQ_TYPE_UNKOWN, NULL, NULL }


/*
 * Message representing data for the MQTT client.
 */
struct  _Ciot__MqttClientData
{
  ProtobufCMessage base;
  /*
   * Configuration for the MQTT client.
   */
  Ciot__MqttClientCfg *config;
  /*
   * Status of the MQTT client.
   */
  Ciot__MqttClientStatus *status;
  /*
   * MQTT client request data.
   */
  Ciot__MqttClientReq *request;
};
#define CIOT__MQTT_CLIENT_DATA__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__mqtt_client_data__descriptor) \
    , NULL, NULL, NULL }


/* Ciot__MqttClientError methods */
void   ciot__mqtt_client_error__init
                     (Ciot__MqttClientError         *message);
size_t ciot__mqtt_client_error__get_packed_size
                     (const Ciot__MqttClientError   *message);
size_t ciot__mqtt_client_error__pack
                     (const Ciot__MqttClientError   *message,
                      uint8_t             *out);
size_t ciot__mqtt_client_error__pack_to_buffer
                     (const Ciot__MqttClientError   *message,
                      ProtobufCBuffer     *buffer);
Ciot__MqttClientError *
       ciot__mqtt_client_error__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__mqtt_client_error__free_unpacked
                     (Ciot__MqttClientError *message,
                      ProtobufCAllocator *allocator);
/* Ciot__MqttClientTopicsCfg methods */
void   ciot__mqtt_client_topics_cfg__init
                     (Ciot__MqttClientTopicsCfg         *message);
size_t ciot__mqtt_client_topics_cfg__get_packed_size
                     (const Ciot__MqttClientTopicsCfg   *message);
size_t ciot__mqtt_client_topics_cfg__pack
                     (const Ciot__MqttClientTopicsCfg   *message,
                      uint8_t             *out);
size_t ciot__mqtt_client_topics_cfg__pack_to_buffer
                     (const Ciot__MqttClientTopicsCfg   *message,
                      ProtobufCBuffer     *buffer);
Ciot__MqttClientTopicsCfg *
       ciot__mqtt_client_topics_cfg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__mqtt_client_topics_cfg__free_unpacked
                     (Ciot__MqttClientTopicsCfg *message,
                      ProtobufCAllocator *allocator);
/* Ciot__MqttClientCfg methods */
void   ciot__mqtt_client_cfg__init
                     (Ciot__MqttClientCfg         *message);
size_t ciot__mqtt_client_cfg__get_packed_size
                     (const Ciot__MqttClientCfg   *message);
size_t ciot__mqtt_client_cfg__pack
                     (const Ciot__MqttClientCfg   *message,
                      uint8_t             *out);
size_t ciot__mqtt_client_cfg__pack_to_buffer
                     (const Ciot__MqttClientCfg   *message,
                      ProtobufCBuffer     *buffer);
Ciot__MqttClientCfg *
       ciot__mqtt_client_cfg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__mqtt_client_cfg__free_unpacked
                     (Ciot__MqttClientCfg *message,
                      ProtobufCAllocator *allocator);
/* Ciot__MqttClientStatus methods */
void   ciot__mqtt_client_status__init
                     (Ciot__MqttClientStatus         *message);
size_t ciot__mqtt_client_status__get_packed_size
                     (const Ciot__MqttClientStatus   *message);
size_t ciot__mqtt_client_status__pack
                     (const Ciot__MqttClientStatus   *message,
                      uint8_t             *out);
size_t ciot__mqtt_client_status__pack_to_buffer
                     (const Ciot__MqttClientStatus   *message,
                      ProtobufCBuffer     *buffer);
Ciot__MqttClientStatus *
       ciot__mqtt_client_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__mqtt_client_status__free_unpacked
                     (Ciot__MqttClientStatus *message,
                      ProtobufCAllocator *allocator);
/* Ciot__MqttClientReqPublish methods */
void   ciot__mqtt_client_req_publish__init
                     (Ciot__MqttClientReqPublish         *message);
size_t ciot__mqtt_client_req_publish__get_packed_size
                     (const Ciot__MqttClientReqPublish   *message);
size_t ciot__mqtt_client_req_publish__pack
                     (const Ciot__MqttClientReqPublish   *message,
                      uint8_t             *out);
size_t ciot__mqtt_client_req_publish__pack_to_buffer
                     (const Ciot__MqttClientReqPublish   *message,
                      ProtobufCBuffer     *buffer);
Ciot__MqttClientReqPublish *
       ciot__mqtt_client_req_publish__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__mqtt_client_req_publish__free_unpacked
                     (Ciot__MqttClientReqPublish *message,
                      ProtobufCAllocator *allocator);
/* Ciot__MqttClientReqSubscribe methods */
void   ciot__mqtt_client_req_subscribe__init
                     (Ciot__MqttClientReqSubscribe         *message);
size_t ciot__mqtt_client_req_subscribe__get_packed_size
                     (const Ciot__MqttClientReqSubscribe   *message);
size_t ciot__mqtt_client_req_subscribe__pack
                     (const Ciot__MqttClientReqSubscribe   *message,
                      uint8_t             *out);
size_t ciot__mqtt_client_req_subscribe__pack_to_buffer
                     (const Ciot__MqttClientReqSubscribe   *message,
                      ProtobufCBuffer     *buffer);
Ciot__MqttClientReqSubscribe *
       ciot__mqtt_client_req_subscribe__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__mqtt_client_req_subscribe__free_unpacked
                     (Ciot__MqttClientReqSubscribe *message,
                      ProtobufCAllocator *allocator);
/* Ciot__MqttClientReq methods */
void   ciot__mqtt_client_req__init
                     (Ciot__MqttClientReq         *message);
size_t ciot__mqtt_client_req__get_packed_size
                     (const Ciot__MqttClientReq   *message);
size_t ciot__mqtt_client_req__pack
                     (const Ciot__MqttClientReq   *message,
                      uint8_t             *out);
size_t ciot__mqtt_client_req__pack_to_buffer
                     (const Ciot__MqttClientReq   *message,
                      ProtobufCBuffer     *buffer);
Ciot__MqttClientReq *
       ciot__mqtt_client_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__mqtt_client_req__free_unpacked
                     (Ciot__MqttClientReq *message,
                      ProtobufCAllocator *allocator);
/* Ciot__MqttClientData methods */
void   ciot__mqtt_client_data__init
                     (Ciot__MqttClientData         *message);
size_t ciot__mqtt_client_data__get_packed_size
                     (const Ciot__MqttClientData   *message);
size_t ciot__mqtt_client_data__pack
                     (const Ciot__MqttClientData   *message,
                      uint8_t             *out);
size_t ciot__mqtt_client_data__pack_to_buffer
                     (const Ciot__MqttClientData   *message,
                      ProtobufCBuffer     *buffer);
Ciot__MqttClientData *
       ciot__mqtt_client_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__mqtt_client_data__free_unpacked
                     (Ciot__MqttClientData *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Ciot__MqttClientError_Closure)
                 (const Ciot__MqttClientError *message,
                  void *closure_data);
typedef void (*Ciot__MqttClientTopicsCfg_Closure)
                 (const Ciot__MqttClientTopicsCfg *message,
                  void *closure_data);
typedef void (*Ciot__MqttClientCfg_Closure)
                 (const Ciot__MqttClientCfg *message,
                  void *closure_data);
typedef void (*Ciot__MqttClientStatus_Closure)
                 (const Ciot__MqttClientStatus *message,
                  void *closure_data);
typedef void (*Ciot__MqttClientReqPublish_Closure)
                 (const Ciot__MqttClientReqPublish *message,
                  void *closure_data);
typedef void (*Ciot__MqttClientReqSubscribe_Closure)
                 (const Ciot__MqttClientReqSubscribe *message,
                  void *closure_data);
typedef void (*Ciot__MqttClientReq_Closure)
                 (const Ciot__MqttClientReq *message,
                  void *closure_data);
typedef void (*Ciot__MqttClientData_Closure)
                 (const Ciot__MqttClientData *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    ciot__mqtt_client_state__descriptor;
extern const ProtobufCEnumDescriptor    ciot__mqtt_client_transport__descriptor;
extern const ProtobufCEnumDescriptor    ciot__mqtt_client_req_type__descriptor;
extern const ProtobufCMessageDescriptor ciot__mqtt_client_error__descriptor;
extern const ProtobufCMessageDescriptor ciot__mqtt_client_topics_cfg__descriptor;
extern const ProtobufCMessageDescriptor ciot__mqtt_client_cfg__descriptor;
extern const ProtobufCMessageDescriptor ciot__mqtt_client_status__descriptor;
extern const ProtobufCMessageDescriptor ciot__mqtt_client_req_publish__descriptor;
extern const ProtobufCMessageDescriptor ciot__mqtt_client_req_subscribe__descriptor;
extern const ProtobufCMessageDescriptor ciot__mqtt_client_req__descriptor;
extern const ProtobufCMessageDescriptor ciot__mqtt_client_data__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_ciot_2fproto_2fv1_2fmqtt_5fclient_2eproto__INCLUDED */