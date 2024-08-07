/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/logger.proto */

#ifndef PROTOBUF_C_ciot_2fproto_2fv1_2flogger_2eproto__INCLUDED
#define PROTOBUF_C_ciot_2fproto_2fv1_2flogger_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Ciot__Log Ciot__Log;


/* --- enums --- */

typedef enum _Ciot__LogLevel {
  CIOT__LOG_LEVEL__LOG_LEVEL_NONE = 0,
  CIOT__LOG_LEVEL__LOG_LEVEL_ERROR = 1,
  CIOT__LOG_LEVEL__LOG_LEVEL_WARNING = 2,
  CIOT__LOG_LEVEL__LOG_LEVEL_INFO = 3,
  CIOT__LOG_LEVEL__LOG_LEVEL_VERBOSE = 4,
  CIOT__LOG_LEVEL__LOG_LEVEL_DEBUG = 5
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__LOG_LEVEL)
} Ciot__LogLevel;

/* --- messages --- */

struct  _Ciot__Log
{
  ProtobufCMessage base;
  Ciot__LogLevel level;
  char *tag;
  char *message;
};
#define CIOT__LOG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__log__descriptor) \
    , CIOT__LOG_LEVEL__LOG_LEVEL_NONE, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string }


/* Ciot__Log methods */
void   ciot__log__init
                     (Ciot__Log         *message);
size_t ciot__log__get_packed_size
                     (const Ciot__Log   *message);
size_t ciot__log__pack
                     (const Ciot__Log   *message,
                      uint8_t             *out);
size_t ciot__log__pack_to_buffer
                     (const Ciot__Log   *message,
                      ProtobufCBuffer     *buffer);
Ciot__Log *
       ciot__log__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__log__free_unpacked
                     (Ciot__Log *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Ciot__Log_Closure)
                 (const Ciot__Log *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    ciot__log_level__descriptor;
extern const ProtobufCMessageDescriptor ciot__log__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_ciot_2fproto_2fv1_2flogger_2eproto__INCLUDED */
