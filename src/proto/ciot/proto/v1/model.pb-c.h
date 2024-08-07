/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/model.proto */

#ifndef PROTOBUF_C_ciot_2fproto_2fv1_2fmodel_2eproto__INCLUDED
#define PROTOBUF_C_ciot_2fproto_2fv1_2fmodel_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Ciot__ModelCfg Ciot__ModelCfg;
typedef struct _Ciot__ModelStatus Ciot__ModelStatus;
typedef struct _Ciot__ModelInfo Ciot__ModelInfo;
typedef struct _Ciot__ModelReq Ciot__ModelReq;
typedef struct _Ciot__ModelData Ciot__ModelData;


/* --- enums --- */

/*
 * Enum representing the state of the Model.
 */
typedef enum _Ciot__ModelState {
  /*
   * Model is idle.
   */
  CIOT__MODEL_STATE__MODEL_STATE_IDLE = 0
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__MODEL_STATE)
} Ciot__ModelState;
/*
 * Enum representing different types of Model requests.
 */
typedef enum _Ciot__ModelReqType {
  /*
   * Unknown request type.
   */
  CIOT__MODEL_REQ_TYPE__MODEL_REQ_TYPE_UNKOWN = 0
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__MODEL_REQ_TYPE)
} Ciot__ModelReqType;

/* --- messages --- */

/*
 * Message representing Model configuration.
 */
struct  _Ciot__ModelCfg
{
  ProtobufCMessage base;
};
#define CIOT__MODEL_CFG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__model_cfg__descriptor) \
     }


/*
 * Message representing Model status.
 */
struct  _Ciot__ModelStatus
{
  ProtobufCMessage base;
  /*
   * State of the Model.
   */
  Ciot__ModelState state;
  /*
   * Error code, if any.
   */
  int32_t error;
};
#define CIOT__MODEL_STATUS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__model_status__descriptor) \
    , CIOT__MODEL_STATE__MODEL_STATE_IDLE, 0 }


struct  _Ciot__ModelInfo
{
  ProtobufCMessage base;
};
#define CIOT__MODEL_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__model_info__descriptor) \
     }


/*
 * Message representing an Model request.
 */
struct  _Ciot__ModelReq
{
  ProtobufCMessage base;
  /*
   * Type of the Model request.
   */
  Ciot__ModelReqType type;
};
#define CIOT__MODEL_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__model_req__descriptor) \
    , CIOT__MODEL_REQ_TYPE__MODEL_REQ_TYPE_UNKOWN }


/*
 * Message representing Model data.
 */
struct  _Ciot__ModelData
{
  ProtobufCMessage base;
  /*
   * Configuration for the Model.
   */
  Ciot__ModelCfg *config;
  /*
   * Status of the Model.
   */
  Ciot__ModelStatus *status;
  /*
   * Model request.
   */
  Ciot__ModelReq *request;
  /*
   * Info of the Model.
   */
  Ciot__ModelInfo *info;
};
#define CIOT__MODEL_DATA__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__model_data__descriptor) \
    , NULL, NULL, NULL, NULL }


/* Ciot__ModelCfg methods */
void   ciot__model_cfg__init
                     (Ciot__ModelCfg         *message);
size_t ciot__model_cfg__get_packed_size
                     (const Ciot__ModelCfg   *message);
size_t ciot__model_cfg__pack
                     (const Ciot__ModelCfg   *message,
                      uint8_t             *out);
size_t ciot__model_cfg__pack_to_buffer
                     (const Ciot__ModelCfg   *message,
                      ProtobufCBuffer     *buffer);
Ciot__ModelCfg *
       ciot__model_cfg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__model_cfg__free_unpacked
                     (Ciot__ModelCfg *message,
                      ProtobufCAllocator *allocator);
/* Ciot__ModelStatus methods */
void   ciot__model_status__init
                     (Ciot__ModelStatus         *message);
size_t ciot__model_status__get_packed_size
                     (const Ciot__ModelStatus   *message);
size_t ciot__model_status__pack
                     (const Ciot__ModelStatus   *message,
                      uint8_t             *out);
size_t ciot__model_status__pack_to_buffer
                     (const Ciot__ModelStatus   *message,
                      ProtobufCBuffer     *buffer);
Ciot__ModelStatus *
       ciot__model_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__model_status__free_unpacked
                     (Ciot__ModelStatus *message,
                      ProtobufCAllocator *allocator);
/* Ciot__ModelInfo methods */
void   ciot__model_info__init
                     (Ciot__ModelInfo         *message);
size_t ciot__model_info__get_packed_size
                     (const Ciot__ModelInfo   *message);
size_t ciot__model_info__pack
                     (const Ciot__ModelInfo   *message,
                      uint8_t             *out);
size_t ciot__model_info__pack_to_buffer
                     (const Ciot__ModelInfo   *message,
                      ProtobufCBuffer     *buffer);
Ciot__ModelInfo *
       ciot__model_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__model_info__free_unpacked
                     (Ciot__ModelInfo *message,
                      ProtobufCAllocator *allocator);
/* Ciot__ModelReq methods */
void   ciot__model_req__init
                     (Ciot__ModelReq         *message);
size_t ciot__model_req__get_packed_size
                     (const Ciot__ModelReq   *message);
size_t ciot__model_req__pack
                     (const Ciot__ModelReq   *message,
                      uint8_t             *out);
size_t ciot__model_req__pack_to_buffer
                     (const Ciot__ModelReq   *message,
                      ProtobufCBuffer     *buffer);
Ciot__ModelReq *
       ciot__model_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__model_req__free_unpacked
                     (Ciot__ModelReq *message,
                      ProtobufCAllocator *allocator);
/* Ciot__ModelData methods */
void   ciot__model_data__init
                     (Ciot__ModelData         *message);
size_t ciot__model_data__get_packed_size
                     (const Ciot__ModelData   *message);
size_t ciot__model_data__pack
                     (const Ciot__ModelData   *message,
                      uint8_t             *out);
size_t ciot__model_data__pack_to_buffer
                     (const Ciot__ModelData   *message,
                      ProtobufCBuffer     *buffer);
Ciot__ModelData *
       ciot__model_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__model_data__free_unpacked
                     (Ciot__ModelData *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Ciot__ModelCfg_Closure)
                 (const Ciot__ModelCfg *message,
                  void *closure_data);
typedef void (*Ciot__ModelStatus_Closure)
                 (const Ciot__ModelStatus *message,
                  void *closure_data);
typedef void (*Ciot__ModelInfo_Closure)
                 (const Ciot__ModelInfo *message,
                  void *closure_data);
typedef void (*Ciot__ModelReq_Closure)
                 (const Ciot__ModelReq *message,
                  void *closure_data);
typedef void (*Ciot__ModelData_Closure)
                 (const Ciot__ModelData *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    ciot__model_state__descriptor;
extern const ProtobufCEnumDescriptor    ciot__model_req_type__descriptor;
extern const ProtobufCMessageDescriptor ciot__model_cfg__descriptor;
extern const ProtobufCMessageDescriptor ciot__model_status__descriptor;
extern const ProtobufCMessageDescriptor ciot__model_info__descriptor;
extern const ProtobufCMessageDescriptor ciot__model_req__descriptor;
extern const ProtobufCMessageDescriptor ciot__model_data__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_ciot_2fproto_2fv1_2fmodel_2eproto__INCLUDED */
