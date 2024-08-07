/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/model.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "ciot/proto/v1/model.pb-c.h"
void   ciot__model_cfg__init
                     (Ciot__ModelCfg         *message)
{
  static const Ciot__ModelCfg init_value = CIOT__MODEL_CFG__INIT;
  *message = init_value;
}
size_t ciot__model_cfg__get_packed_size
                     (const Ciot__ModelCfg *message)
{
  assert(message->base.descriptor == &ciot__model_cfg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__model_cfg__pack
                     (const Ciot__ModelCfg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__model_cfg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__model_cfg__pack_to_buffer
                     (const Ciot__ModelCfg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__model_cfg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__ModelCfg *
       ciot__model_cfg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__ModelCfg *)
     protobuf_c_message_unpack (&ciot__model_cfg__descriptor,
                                allocator, len, data);
}
void   ciot__model_cfg__free_unpacked
                     (Ciot__ModelCfg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__model_cfg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__model_status__init
                     (Ciot__ModelStatus         *message)
{
  static const Ciot__ModelStatus init_value = CIOT__MODEL_STATUS__INIT;
  *message = init_value;
}
size_t ciot__model_status__get_packed_size
                     (const Ciot__ModelStatus *message)
{
  assert(message->base.descriptor == &ciot__model_status__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__model_status__pack
                     (const Ciot__ModelStatus *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__model_status__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__model_status__pack_to_buffer
                     (const Ciot__ModelStatus *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__model_status__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__ModelStatus *
       ciot__model_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__ModelStatus *)
     protobuf_c_message_unpack (&ciot__model_status__descriptor,
                                allocator, len, data);
}
void   ciot__model_status__free_unpacked
                     (Ciot__ModelStatus *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__model_status__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__model_info__init
                     (Ciot__ModelInfo         *message)
{
  static const Ciot__ModelInfo init_value = CIOT__MODEL_INFO__INIT;
  *message = init_value;
}
size_t ciot__model_info__get_packed_size
                     (const Ciot__ModelInfo *message)
{
  assert(message->base.descriptor == &ciot__model_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__model_info__pack
                     (const Ciot__ModelInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__model_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__model_info__pack_to_buffer
                     (const Ciot__ModelInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__model_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__ModelInfo *
       ciot__model_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__ModelInfo *)
     protobuf_c_message_unpack (&ciot__model_info__descriptor,
                                allocator, len, data);
}
void   ciot__model_info__free_unpacked
                     (Ciot__ModelInfo *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__model_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__model_req__init
                     (Ciot__ModelReq         *message)
{
  static const Ciot__ModelReq init_value = CIOT__MODEL_REQ__INIT;
  *message = init_value;
}
size_t ciot__model_req__get_packed_size
                     (const Ciot__ModelReq *message)
{
  assert(message->base.descriptor == &ciot__model_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__model_req__pack
                     (const Ciot__ModelReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__model_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__model_req__pack_to_buffer
                     (const Ciot__ModelReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__model_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__ModelReq *
       ciot__model_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__ModelReq *)
     protobuf_c_message_unpack (&ciot__model_req__descriptor,
                                allocator, len, data);
}
void   ciot__model_req__free_unpacked
                     (Ciot__ModelReq *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__model_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__model_data__init
                     (Ciot__ModelData         *message)
{
  static const Ciot__ModelData init_value = CIOT__MODEL_DATA__INIT;
  *message = init_value;
}
size_t ciot__model_data__get_packed_size
                     (const Ciot__ModelData *message)
{
  assert(message->base.descriptor == &ciot__model_data__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__model_data__pack
                     (const Ciot__ModelData *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__model_data__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__model_data__pack_to_buffer
                     (const Ciot__ModelData *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__model_data__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__ModelData *
       ciot__model_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__ModelData *)
     protobuf_c_message_unpack (&ciot__model_data__descriptor,
                                allocator, len, data);
}
void   ciot__model_data__free_unpacked
                     (Ciot__ModelData *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__model_data__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
#define ciot__model_cfg__field_descriptors NULL
#define ciot__model_cfg__field_indices_by_name NULL
#define ciot__model_cfg__number_ranges NULL
const ProtobufCMessageDescriptor ciot__model_cfg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.ModelCfg",
  "ModelCfg",
  "Ciot__ModelCfg",
  "Ciot",
  sizeof(Ciot__ModelCfg),
  0,
  ciot__model_cfg__field_descriptors,
  ciot__model_cfg__field_indices_by_name,
  0,  ciot__model_cfg__number_ranges,
  (ProtobufCMessageInit) ciot__model_cfg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__model_status__field_descriptors[2] =
{
  {
    "state",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__ModelStatus, state),
    &ciot__model_state__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "error",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ciot__ModelStatus, error),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__model_status__field_indices_by_name[] = {
  1,   /* field[1] = error */
  0,   /* field[0] = state */
};
static const ProtobufCIntRange ciot__model_status__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor ciot__model_status__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.ModelStatus",
  "ModelStatus",
  "Ciot__ModelStatus",
  "Ciot",
  sizeof(Ciot__ModelStatus),
  2,
  ciot__model_status__field_descriptors,
  ciot__model_status__field_indices_by_name,
  1,  ciot__model_status__number_ranges,
  (ProtobufCMessageInit) ciot__model_status__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define ciot__model_info__field_descriptors NULL
#define ciot__model_info__field_indices_by_name NULL
#define ciot__model_info__number_ranges NULL
const ProtobufCMessageDescriptor ciot__model_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.ModelInfo",
  "ModelInfo",
  "Ciot__ModelInfo",
  "Ciot",
  sizeof(Ciot__ModelInfo),
  0,
  ciot__model_info__field_descriptors,
  ciot__model_info__field_indices_by_name,
  0,  ciot__model_info__number_ranges,
  (ProtobufCMessageInit) ciot__model_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__model_req__field_descriptors[1] =
{
  {
    "type",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__ModelReq, type),
    &ciot__model_req_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__model_req__field_indices_by_name[] = {
  0,   /* field[0] = type */
};
static const ProtobufCIntRange ciot__model_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor ciot__model_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.ModelReq",
  "ModelReq",
  "Ciot__ModelReq",
  "Ciot",
  sizeof(Ciot__ModelReq),
  1,
  ciot__model_req__field_descriptors,
  ciot__model_req__field_indices_by_name,
  1,  ciot__model_req__number_ranges,
  (ProtobufCMessageInit) ciot__model_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__model_data__field_descriptors[4] =
{
  {
    "config",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__ModelData, config),
    &ciot__model_cfg__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "status",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__ModelData, status),
    &ciot__model_status__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "request",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__ModelData, request),
    &ciot__model_req__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "info",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__ModelData, info),
    &ciot__model_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__model_data__field_indices_by_name[] = {
  0,   /* field[0] = config */
  3,   /* field[3] = info */
  2,   /* field[2] = request */
  1,   /* field[1] = status */
};
static const ProtobufCIntRange ciot__model_data__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor ciot__model_data__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.ModelData",
  "ModelData",
  "Ciot__ModelData",
  "Ciot",
  sizeof(Ciot__ModelData),
  4,
  ciot__model_data__field_descriptors,
  ciot__model_data__field_indices_by_name,
  1,  ciot__model_data__number_ranges,
  (ProtobufCMessageInit) ciot__model_data__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue ciot__model_state__enum_values_by_number[1] =
{
  { "MODEL_STATE_IDLE", "CIOT__MODEL_STATE__MODEL_STATE_IDLE", 0 },
};
static const ProtobufCIntRange ciot__model_state__value_ranges[] = {
{0, 0},{0, 1}
};
static const ProtobufCEnumValueIndex ciot__model_state__enum_values_by_name[1] =
{
  { "MODEL_STATE_IDLE", 0 },
};
const ProtobufCEnumDescriptor ciot__model_state__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.ModelState",
  "ModelState",
  "Ciot__ModelState",
  "Ciot",
  1,
  ciot__model_state__enum_values_by_number,
  1,
  ciot__model_state__enum_values_by_name,
  1,
  ciot__model_state__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCEnumValue ciot__model_req_type__enum_values_by_number[1] =
{
  { "MODEL_REQ_TYPE_UNKOWN", "CIOT__MODEL_REQ_TYPE__MODEL_REQ_TYPE_UNKOWN", 0 },
};
static const ProtobufCIntRange ciot__model_req_type__value_ranges[] = {
{0, 0},{0, 1}
};
static const ProtobufCEnumValueIndex ciot__model_req_type__enum_values_by_name[1] =
{
  { "MODEL_REQ_TYPE_UNKOWN", 0 },
};
const ProtobufCEnumDescriptor ciot__model_req_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.ModelReqType",
  "ModelReqType",
  "Ciot__ModelReqType",
  "Ciot",
  1,
  ciot__model_req_type__enum_values_by_number,
  1,
  ciot__model_req_type__enum_values_by_name,
  1,
  ciot__model_req_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
