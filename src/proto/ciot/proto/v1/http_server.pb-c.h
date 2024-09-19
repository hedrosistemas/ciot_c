/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/http_server.proto */

#ifndef PROTOBUF_C_ciot_2fproto_2fv1_2fhttp_5fserver_2eproto__INCLUDED
#define PROTOBUF_C_ciot_2fproto_2fv1_2fhttp_5fserver_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Ciot__HttpServerCfg Ciot__HttpServerCfg;
typedef struct _Ciot__HttpServerStatus Ciot__HttpServerStatus;
typedef struct _Ciot__HttpServerReq Ciot__HttpServerReq;
typedef struct _Ciot__HttpServerData Ciot__HttpServerData;


/* --- enums --- */

/*
 * Enum representing the state of the HTTP server.
 */
typedef enum _Ciot__HttpServerState {
  /*
   * The HTTP server is stopped.
   */
  CIOT__HTTP_SERVER_STATE__HTTP_SERVER_STATE_STOPPED = 0,
  /*
   * The HTTP server is started.
   */
  CIOT__HTTP_SERVER_STATE__HTTP_SERVER_STATE_STARTED = 1,
  /*
   * The HTTP server encountered an error.
   */
  CIOT__HTTP_SERVER_STATE__HTTP_SERVER_STATE_ERROR = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__HTTP_SERVER_STATE)
} Ciot__HttpServerState;
/*
 * Enum representing different types of HTTP server requests.
 */
typedef enum _Ciot__HttpServerReqType {
  /*
   * Unknown request type for the HTTP server.
   */
  CIOT__HTTP_SERVER_REQ_TYPE__HTTP_SERVER_REQ_TYPE_UNKOWN = 0
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__HTTP_SERVER_REQ_TYPE)
} Ciot__HttpServerReqType;

/* --- messages --- */

/*
 * Message representing HTTP server configuration.
 */
struct  _Ciot__HttpServerCfg
{
  ProtobufCMessage base;
  /*
   * Address of the HTTP server.
   */
  char *address;
  /*
   * Route for the HTTP server.
   */
  char *route;
  /*
   * Port number for the HTTP server.
   */
  uint32_t port;
};
#define CIOT__HTTP_SERVER_CFG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__http_server_cfg__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, 0 }


/*
 * Message representing HTTP server status.
 */
struct  _Ciot__HttpServerStatus
{
  ProtobufCMessage base;
  /*
   * State of the HTTP server.
   */
  Ciot__HttpServerState state;
  /*
   * Error code, if any.
   */
  int32_t error;
};
#define CIOT__HTTP_SERVER_STATUS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__http_server_status__descriptor) \
    , CIOT__HTTP_SERVER_STATE__HTTP_SERVER_STATE_STOPPED, 0 }


/*
 * Message representing an HTTP server request.
 */
struct  _Ciot__HttpServerReq
{
  ProtobufCMessage base;
  /*
   * Type of the HTTP server request.
   */
  Ciot__HttpServerReqType type;
};
#define CIOT__HTTP_SERVER_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__http_server_req__descriptor) \
    , CIOT__HTTP_SERVER_REQ_TYPE__HTTP_SERVER_REQ_TYPE_UNKOWN }


/*
 * Message representing HTTP server data.
 */
struct  _Ciot__HttpServerData
{
  ProtobufCMessage base;
  /*
   * Configuration for the HTTP server.
   */
  Ciot__HttpServerCfg *config;
  /*
   * Status of the HTTP server.
   */
  Ciot__HttpServerStatus *status;
  /*
   * HTTP server request data.
   */
  Ciot__HttpServerReq *request;
};
#define CIOT__HTTP_SERVER_DATA__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__http_server_data__descriptor) \
    , NULL, NULL, NULL }


/* Ciot__HttpServerCfg methods */
void   ciot__http_server_cfg__init
                     (Ciot__HttpServerCfg         *message);
size_t ciot__http_server_cfg__get_packed_size
                     (const Ciot__HttpServerCfg   *message);
size_t ciot__http_server_cfg__pack
                     (const Ciot__HttpServerCfg   *message,
                      uint8_t             *out);
size_t ciot__http_server_cfg__pack_to_buffer
                     (const Ciot__HttpServerCfg   *message,
                      ProtobufCBuffer     *buffer);
Ciot__HttpServerCfg *
       ciot__http_server_cfg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__http_server_cfg__free_unpacked
                     (Ciot__HttpServerCfg *message,
                      ProtobufCAllocator *allocator);
/* Ciot__HttpServerStatus methods */
void   ciot__http_server_status__init
                     (Ciot__HttpServerStatus         *message);
size_t ciot__http_server_status__get_packed_size
                     (const Ciot__HttpServerStatus   *message);
size_t ciot__http_server_status__pack
                     (const Ciot__HttpServerStatus   *message,
                      uint8_t             *out);
size_t ciot__http_server_status__pack_to_buffer
                     (const Ciot__HttpServerStatus   *message,
                      ProtobufCBuffer     *buffer);
Ciot__HttpServerStatus *
       ciot__http_server_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__http_server_status__free_unpacked
                     (Ciot__HttpServerStatus *message,
                      ProtobufCAllocator *allocator);
/* Ciot__HttpServerReq methods */
void   ciot__http_server_req__init
                     (Ciot__HttpServerReq         *message);
size_t ciot__http_server_req__get_packed_size
                     (const Ciot__HttpServerReq   *message);
size_t ciot__http_server_req__pack
                     (const Ciot__HttpServerReq   *message,
                      uint8_t             *out);
size_t ciot__http_server_req__pack_to_buffer
                     (const Ciot__HttpServerReq   *message,
                      ProtobufCBuffer     *buffer);
Ciot__HttpServerReq *
       ciot__http_server_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__http_server_req__free_unpacked
                     (Ciot__HttpServerReq *message,
                      ProtobufCAllocator *allocator);
/* Ciot__HttpServerData methods */
void   ciot__http_server_data__init
                     (Ciot__HttpServerData         *message);
size_t ciot__http_server_data__get_packed_size
                     (const Ciot__HttpServerData   *message);
size_t ciot__http_server_data__pack
                     (const Ciot__HttpServerData   *message,
                      uint8_t             *out);
size_t ciot__http_server_data__pack_to_buffer
                     (const Ciot__HttpServerData   *message,
                      ProtobufCBuffer     *buffer);
Ciot__HttpServerData *
       ciot__http_server_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__http_server_data__free_unpacked
                     (Ciot__HttpServerData *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Ciot__HttpServerCfg_Closure)
                 (const Ciot__HttpServerCfg *message,
                  void *closure_data);
typedef void (*Ciot__HttpServerStatus_Closure)
                 (const Ciot__HttpServerStatus *message,
                  void *closure_data);
typedef void (*Ciot__HttpServerReq_Closure)
                 (const Ciot__HttpServerReq *message,
                  void *closure_data);
typedef void (*Ciot__HttpServerData_Closure)
                 (const Ciot__HttpServerData *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    ciot__http_server_state__descriptor;
extern const ProtobufCEnumDescriptor    ciot__http_server_req_type__descriptor;
extern const ProtobufCMessageDescriptor ciot__http_server_cfg__descriptor;
extern const ProtobufCMessageDescriptor ciot__http_server_status__descriptor;
extern const ProtobufCMessageDescriptor ciot__http_server_req__descriptor;
extern const ProtobufCMessageDescriptor ciot__http_server_data__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_ciot_2fproto_2fv1_2fhttp_5fserver_2eproto__INCLUDED */
