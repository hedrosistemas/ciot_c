/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/logger.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "ciot/proto/v1/logger.pb-c.h"
void   ciot__log__init
                     (Ciot__Log         *message)
{
  static const Ciot__Log init_value = CIOT__LOG__INIT;
  *message = init_value;
}
size_t ciot__log__get_packed_size
                     (const Ciot__Log *message)
{
  assert(message->base.descriptor == &ciot__log__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__log__pack
                     (const Ciot__Log *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__log__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__log__pack_to_buffer
                     (const Ciot__Log *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__log__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__Log *
       ciot__log__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__Log *)
     protobuf_c_message_unpack (&ciot__log__descriptor,
                                allocator, len, data);
}
void   ciot__log__free_unpacked
                     (Ciot__Log *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__log__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor ciot__log__field_descriptors[3] =
{
  {
    "level",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__Log, level),
    &ciot__log_level__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "tag",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ciot__Log, tag),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "message",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ciot__Log, message),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__log__field_indices_by_name[] = {
  0,   /* field[0] = level */
  2,   /* field[2] = message */
  1,   /* field[1] = tag */
};
static const ProtobufCIntRange ciot__log__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor ciot__log__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.Log",
  "Log",
  "Ciot__Log",
  "Ciot",
  sizeof(Ciot__Log),
  3,
  ciot__log__field_descriptors,
  ciot__log__field_indices_by_name,
  1,  ciot__log__number_ranges,
  (ProtobufCMessageInit) ciot__log__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue ciot__log_level__enum_values_by_number[6] =
{
  { "LOG_LEVEL_NONE", "CIOT__LOG_LEVEL__LOG_LEVEL_NONE", 0 },
  { "LOG_LEVEL_ERROR", "CIOT__LOG_LEVEL__LOG_LEVEL_ERROR", 1 },
  { "LOG_LEVEL_WARNING", "CIOT__LOG_LEVEL__LOG_LEVEL_WARNING", 2 },
  { "LOG_LEVEL_INFO", "CIOT__LOG_LEVEL__LOG_LEVEL_INFO", 3 },
  { "LOG_LEVEL_VERBOSE", "CIOT__LOG_LEVEL__LOG_LEVEL_VERBOSE", 4 },
  { "LOG_LEVEL_DEBUG", "CIOT__LOG_LEVEL__LOG_LEVEL_DEBUG", 5 },
};
static const ProtobufCIntRange ciot__log_level__value_ranges[] = {
{0, 0},{0, 6}
};
static const ProtobufCEnumValueIndex ciot__log_level__enum_values_by_name[6] =
{
  { "LOG_LEVEL_DEBUG", 5 },
  { "LOG_LEVEL_ERROR", 1 },
  { "LOG_LEVEL_INFO", 3 },
  { "LOG_LEVEL_NONE", 0 },
  { "LOG_LEVEL_VERBOSE", 4 },
  { "LOG_LEVEL_WARNING", 2 },
};
const ProtobufCEnumDescriptor ciot__log_level__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.LogLevel",
  "LogLevel",
  "Ciot__LogLevel",
  "Ciot",
  6,
  ciot__log_level__enum_values_by_number,
  6,
  ciot__log_level__enum_values_by_name,
  1,
  ciot__log_level__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
