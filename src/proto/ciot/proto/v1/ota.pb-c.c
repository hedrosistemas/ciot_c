/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/ota.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "ciot/proto/v1/ota.pb-c.h"
void   ciot__ota_cfg__init
                     (Ciot__OtaCfg         *message)
{
  static const Ciot__OtaCfg init_value = CIOT__OTA_CFG__INIT;
  *message = init_value;
}
size_t ciot__ota_cfg__get_packed_size
                     (const Ciot__OtaCfg *message)
{
  assert(message->base.descriptor == &ciot__ota_cfg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__ota_cfg__pack
                     (const Ciot__OtaCfg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__ota_cfg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__ota_cfg__pack_to_buffer
                     (const Ciot__OtaCfg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__ota_cfg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__OtaCfg *
       ciot__ota_cfg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__OtaCfg *)
     protobuf_c_message_unpack (&ciot__ota_cfg__descriptor,
                                allocator, len, data);
}
void   ciot__ota_cfg__free_unpacked
                     (Ciot__OtaCfg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__ota_cfg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__ota_status__init
                     (Ciot__OtaStatus         *message)
{
  static const Ciot__OtaStatus init_value = CIOT__OTA_STATUS__INIT;
  *message = init_value;
}
size_t ciot__ota_status__get_packed_size
                     (const Ciot__OtaStatus *message)
{
  assert(message->base.descriptor == &ciot__ota_status__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__ota_status__pack
                     (const Ciot__OtaStatus *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__ota_status__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__ota_status__pack_to_buffer
                     (const Ciot__OtaStatus *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__ota_status__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__OtaStatus *
       ciot__ota_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__OtaStatus *)
     protobuf_c_message_unpack (&ciot__ota_status__descriptor,
                                allocator, len, data);
}
void   ciot__ota_status__free_unpacked
                     (Ciot__OtaStatus *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__ota_status__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__ota_req_data__init
                     (Ciot__OtaReqData         *message)
{
  static const Ciot__OtaReqData init_value = CIOT__OTA_REQ_DATA__INIT;
  *message = init_value;
}
size_t ciot__ota_req_data__get_packed_size
                     (const Ciot__OtaReqData *message)
{
  assert(message->base.descriptor == &ciot__ota_req_data__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__ota_req_data__pack
                     (const Ciot__OtaReqData *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__ota_req_data__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__ota_req_data__pack_to_buffer
                     (const Ciot__OtaReqData *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__ota_req_data__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__OtaReqData *
       ciot__ota_req_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__OtaReqData *)
     protobuf_c_message_unpack (&ciot__ota_req_data__descriptor,
                                allocator, len, data);
}
void   ciot__ota_req_data__free_unpacked
                     (Ciot__OtaReqData *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__ota_req_data__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__ota_req__init
                     (Ciot__OtaReq         *message)
{
  static const Ciot__OtaReq init_value = CIOT__OTA_REQ__INIT;
  *message = init_value;
}
size_t ciot__ota_req__get_packed_size
                     (const Ciot__OtaReq *message)
{
  assert(message->base.descriptor == &ciot__ota_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__ota_req__pack
                     (const Ciot__OtaReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__ota_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__ota_req__pack_to_buffer
                     (const Ciot__OtaReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__ota_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__OtaReq *
       ciot__ota_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__OtaReq *)
     protobuf_c_message_unpack (&ciot__ota_req__descriptor,
                                allocator, len, data);
}
void   ciot__ota_req__free_unpacked
                     (Ciot__OtaReq *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__ota_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__ota_data__init
                     (Ciot__OtaData         *message)
{
  static const Ciot__OtaData init_value = CIOT__OTA_DATA__INIT;
  *message = init_value;
}
size_t ciot__ota_data__get_packed_size
                     (const Ciot__OtaData *message)
{
  assert(message->base.descriptor == &ciot__ota_data__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__ota_data__pack
                     (const Ciot__OtaData *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__ota_data__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__ota_data__pack_to_buffer
                     (const Ciot__OtaData *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__ota_data__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__OtaData *
       ciot__ota_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__OtaData *)
     protobuf_c_message_unpack (&ciot__ota_data__descriptor,
                                allocator, len, data);
}
void   ciot__ota_data__free_unpacked
                     (Ciot__OtaData *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__ota_data__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor ciot__ota_cfg__field_descriptors[4] =
{
  {
    "url",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ciot__OtaCfg, url),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "force",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(Ciot__OtaCfg, force),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "encrypted",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(Ciot__OtaCfg, encrypted),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "restart",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(Ciot__OtaCfg, restart),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__ota_cfg__field_indices_by_name[] = {
  2,   /* field[2] = encrypted */
  1,   /* field[1] = force */
  3,   /* field[3] = restart */
  0,   /* field[0] = url */
};
static const ProtobufCIntRange ciot__ota_cfg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor ciot__ota_cfg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.OtaCfg",
  "OtaCfg",
  "Ciot__OtaCfg",
  "Ciot",
  sizeof(Ciot__OtaCfg),
  4,
  ciot__ota_cfg__field_descriptors,
  ciot__ota_cfg__field_indices_by_name,
  1,  ciot__ota_cfg__number_ranges,
  (ProtobufCMessageInit) ciot__ota_cfg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__ota_status__field_descriptors[4] =
{
  {
    "state",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__OtaStatus, state),
    &ciot__ota_state__descriptor,
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
    offsetof(Ciot__OtaStatus, error),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "image_size",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Ciot__OtaStatus, image_size),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "image_read",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Ciot__OtaStatus, image_read),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__ota_status__field_indices_by_name[] = {
  1,   /* field[1] = error */
  3,   /* field[3] = image_read */
  2,   /* field[2] = image_size */
  0,   /* field[0] = state */
};
static const ProtobufCIntRange ciot__ota_status__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor ciot__ota_status__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.OtaStatus",
  "OtaStatus",
  "Ciot__OtaStatus",
  "Ciot",
  sizeof(Ciot__OtaStatus),
  4,
  ciot__ota_status__field_descriptors,
  ciot__ota_status__field_indices_by_name,
  1,  ciot__ota_status__number_ranges,
  (ProtobufCMessageInit) ciot__ota_status__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define ciot__ota_req_data__field_descriptors NULL
#define ciot__ota_req_data__field_indices_by_name NULL
#define ciot__ota_req_data__number_ranges NULL
const ProtobufCMessageDescriptor ciot__ota_req_data__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.OtaReqData",
  "OtaReqData",
  "Ciot__OtaReqData",
  "Ciot",
  sizeof(Ciot__OtaReqData),
  0,
  ciot__ota_req_data__field_descriptors,
  ciot__ota_req_data__field_indices_by_name,
  0,  ciot__ota_req_data__number_ranges,
  (ProtobufCMessageInit) ciot__ota_req_data__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__ota_req__field_descriptors[2] =
{
  {
    "type",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__OtaReq, type),
    &ciot__ota_req_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "data",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__OtaReq, data),
    &ciot__ota_req_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__ota_req__field_indices_by_name[] = {
  1,   /* field[1] = data */
  0,   /* field[0] = type */
};
static const ProtobufCIntRange ciot__ota_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor ciot__ota_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.OtaReq",
  "OtaReq",
  "Ciot__OtaReq",
  "Ciot",
  sizeof(Ciot__OtaReq),
  2,
  ciot__ota_req__field_descriptors,
  ciot__ota_req__field_indices_by_name,
  1,  ciot__ota_req__number_ranges,
  (ProtobufCMessageInit) ciot__ota_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__ota_data__field_descriptors[3] =
{
  {
    "config",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__OtaData, config),
    &ciot__ota_cfg__descriptor,
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
    offsetof(Ciot__OtaData, status),
    &ciot__ota_status__descriptor,
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
    offsetof(Ciot__OtaData, request),
    &ciot__ota_req__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__ota_data__field_indices_by_name[] = {
  0,   /* field[0] = config */
  2,   /* field[2] = request */
  1,   /* field[1] = status */
};
static const ProtobufCIntRange ciot__ota_data__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor ciot__ota_data__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.OtaData",
  "OtaData",
  "Ciot__OtaData",
  "Ciot",
  sizeof(Ciot__OtaData),
  3,
  ciot__ota_data__field_descriptors,
  ciot__ota_data__field_indices_by_name,
  1,  ciot__ota_data__number_ranges,
  (ProtobufCMessageInit) ciot__ota_data__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue ciot__ota_state__enum_values_by_number[11] =
{
  { "OTA_STATE_ERROR", "CIOT__OTA_STATE__OTA_STATE_ERROR", -1 },
  { "OTA_STATE_IDLE", "CIOT__OTA_STATE__OTA_STATE_IDLE", 0 },
  { "OTA_STATE_INIT", "CIOT__OTA_STATE__OTA_STATE_INIT", 1 },
  { "OTA_STATE_IN_PROGRESS", "CIOT__OTA_STATE__OTA_STATE_IN_PROGRESS", 2 },
  { "OTA_STATE_START", "CIOT__OTA_STATE__OTA_STATE_START", 3 },
  { "OTA_STATE_CONNECTED", "CIOT__OTA_STATE__OTA_STATE_CONNECTED", 4 },
  { "OTA_STATE_CHECKING_DATA", "CIOT__OTA_STATE__OTA_STATE_CHECKING_DATA", 5 },
  { "OTA_STATE_DECRYPTING", "CIOT__OTA_STATE__OTA_STATE_DECRYPTING", 6 },
  { "OTA_STATE_FLASHING", "CIOT__OTA_STATE__OTA_STATE_FLASHING", 7 },
  { "OTA_STATE_UPDATE_BOOT_PARTITION", "CIOT__OTA_STATE__OTA_STATE_UPDATE_BOOT_PARTITION", 8 },
  { "OTA_STATE_STATE_DONE", "CIOT__OTA_STATE__OTA_STATE_STATE_DONE", 9 },
};
static const ProtobufCIntRange ciot__ota_state__value_ranges[] = {
{-1, 0},{0, 11}
};
static const ProtobufCEnumValueIndex ciot__ota_state__enum_values_by_name[11] =
{
  { "OTA_STATE_CHECKING_DATA", 6 },
  { "OTA_STATE_CONNECTED", 5 },
  { "OTA_STATE_DECRYPTING", 7 },
  { "OTA_STATE_ERROR", 0 },
  { "OTA_STATE_FLASHING", 8 },
  { "OTA_STATE_IDLE", 1 },
  { "OTA_STATE_INIT", 2 },
  { "OTA_STATE_IN_PROGRESS", 3 },
  { "OTA_STATE_START", 4 },
  { "OTA_STATE_STATE_DONE", 10 },
  { "OTA_STATE_UPDATE_BOOT_PARTITION", 9 },
};
const ProtobufCEnumDescriptor ciot__ota_state__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.OtaState",
  "OtaState",
  "Ciot__OtaState",
  "Ciot",
  11,
  ciot__ota_state__enum_values_by_number,
  11,
  ciot__ota_state__enum_values_by_name,
  1,
  ciot__ota_state__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCEnumValue ciot__ota_req_type__enum_values_by_number[1] =
{
  { "OTA_REQ_TYPE_UNKOWN", "CIOT__OTA_REQ_TYPE__OTA_REQ_TYPE_UNKOWN", 0 },
};
static const ProtobufCIntRange ciot__ota_req_type__value_ranges[] = {
{0, 0},{0, 1}
};
static const ProtobufCEnumValueIndex ciot__ota_req_type__enum_values_by_name[1] =
{
  { "OTA_REQ_TYPE_UNKOWN", 0 },
};
const ProtobufCEnumDescriptor ciot__ota_req_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.OtaReqType",
  "OtaReqType",
  "Ciot__OtaReqType",
  "Ciot",
  1,
  ciot__ota_req_type__enum_values_by_number,
  1,
  ciot__ota_req_type__enum_values_by_name,
  1,
  ciot__ota_req_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};