/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/msg.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "ciot/proto/v1/msg.pb-c.h"
void   ciot__iface_info__init
                     (Ciot__IfaceInfo         *message)
{
  static const Ciot__IfaceInfo init_value = CIOT__IFACE_INFO__INIT;
  *message = init_value;
}
size_t ciot__iface_info__get_packed_size
                     (const Ciot__IfaceInfo *message)
{
  assert(message->base.descriptor == &ciot__iface_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__iface_info__pack
                     (const Ciot__IfaceInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__iface_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__iface_info__pack_to_buffer
                     (const Ciot__IfaceInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__iface_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__IfaceInfo *
       ciot__iface_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__IfaceInfo *)
     protobuf_c_message_unpack (&ciot__iface_info__descriptor,
                                allocator, len, data);
}
void   ciot__iface_info__free_unpacked
                     (Ciot__IfaceInfo *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__iface_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__msg_error__init
                     (Ciot__MsgError         *message)
{
  static const Ciot__MsgError init_value = CIOT__MSG_ERROR__INIT;
  *message = init_value;
}
size_t ciot__msg_error__get_packed_size
                     (const Ciot__MsgError *message)
{
  assert(message->base.descriptor == &ciot__msg_error__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__msg_error__pack
                     (const Ciot__MsgError *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__msg_error__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__msg_error__pack_to_buffer
                     (const Ciot__MsgError *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__msg_error__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__MsgError *
       ciot__msg_error__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__MsgError *)
     protobuf_c_message_unpack (&ciot__msg_error__descriptor,
                                allocator, len, data);
}
void   ciot__msg_error__free_unpacked
                     (Ciot__MsgError *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__msg_error__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__msg_data__init
                     (Ciot__MsgData         *message)
{
  static const Ciot__MsgData init_value = CIOT__MSG_DATA__INIT;
  *message = init_value;
}
size_t ciot__msg_data__get_packed_size
                     (const Ciot__MsgData *message)
{
  assert(message->base.descriptor == &ciot__msg_data__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__msg_data__pack
                     (const Ciot__MsgData *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__msg_data__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__msg_data__pack_to_buffer
                     (const Ciot__MsgData *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__msg_data__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__MsgData *
       ciot__msg_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__MsgData *)
     protobuf_c_message_unpack (&ciot__msg_data__descriptor,
                                allocator, len, data);
}
void   ciot__msg_data__free_unpacked
                     (Ciot__MsgData *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__msg_data__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__msg_header__init
                     (Ciot__MsgHeader         *message)
{
  static const Ciot__MsgHeader init_value = CIOT__MSG_HEADER__INIT;
  *message = init_value;
}
size_t ciot__msg_header__get_packed_size
                     (const Ciot__MsgHeader *message)
{
  assert(message->base.descriptor == &ciot__msg_header__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__msg_header__pack
                     (const Ciot__MsgHeader *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__msg_header__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__msg_header__pack_to_buffer
                     (const Ciot__MsgHeader *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__msg_header__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__MsgHeader *
       ciot__msg_header__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__MsgHeader *)
     protobuf_c_message_unpack (&ciot__msg_header__descriptor,
                                allocator, len, data);
}
void   ciot__msg_header__free_unpacked
                     (Ciot__MsgHeader *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__msg_header__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__msg__init
                     (Ciot__Msg         *message)
{
  static const Ciot__Msg init_value = CIOT__MSG__INIT;
  *message = init_value;
}
size_t ciot__msg__get_packed_size
                     (const Ciot__Msg *message)
{
  assert(message->base.descriptor == &ciot__msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__msg__pack
                     (const Ciot__Msg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__msg__pack_to_buffer
                     (const Ciot__Msg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__Msg *
       ciot__msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__Msg *)
     protobuf_c_message_unpack (&ciot__msg__descriptor,
                                allocator, len, data);
}
void   ciot__msg__free_unpacked
                     (Ciot__Msg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor ciot__iface_info__field_descriptors[2] =
{
  {
    "id",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Ciot__IfaceInfo, id),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "type",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__IfaceInfo, type),
    &ciot__iface_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__iface_info__field_indices_by_name[] = {
  0,   /* field[0] = id */
  1,   /* field[1] = type */
};
static const ProtobufCIntRange ciot__iface_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor ciot__iface_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.IfaceInfo",
  "IfaceInfo",
  "Ciot__IfaceInfo",
  "Ciot",
  sizeof(Ciot__IfaceInfo),
  2,
  ciot__iface_info__field_descriptors,
  ciot__iface_info__field_indices_by_name,
  1,  ciot__iface_info__number_ranges,
  (ProtobufCMessageInit) ciot__iface_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__msg_error__field_descriptors[3] =
{
  {
    "msg",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgError, msg),
    &ciot__msg_header__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "iface",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgError, iface),
    &ciot__iface_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "code",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgError, code),
    &ciot_err__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__msg_error__field_indices_by_name[] = {
  2,   /* field[2] = code */
  1,   /* field[1] = iface */
  0,   /* field[0] = msg */
};
static const ProtobufCIntRange ciot__msg_error__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor ciot__msg_error__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.MsgError",
  "MsgError",
  "Ciot__MsgError",
  "Ciot",
  sizeof(Ciot__MsgError),
  3,
  ciot__msg_error__field_descriptors,
  ciot__msg_error__field_indices_by_name,
  1,  ciot__msg_error__number_ranges,
  (ProtobufCMessageInit) ciot__msg_error__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__msg_data__field_descriptors[21] =
{
  {
    "ciot",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, ciot),
    &ciot__ciot_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "storage",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, storage),
    &ciot__storage_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "sys",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, sys),
    &ciot__sys_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "uart",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, uart),
    &ciot__uart_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "usb",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, usb),
    &ciot__usb_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "tcp",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, tcp),
    &ciot__tcp_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "eth",
    7,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, eth),
    &ciot__tcp_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "wifi",
    8,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, wifi),
    &ciot__wifi_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ble",
    9,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, ble),
    &ciot__ble_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ble_scn",
    10,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, ble_scn),
    &ciot__ble_scn_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ble_adv",
    11,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, ble_adv),
    &ciot__ble_adv_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ntp",
    12,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, ntp),
    &ciot__ntp_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ota",
    13,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, ota),
    &ciot__ota_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "dfu",
    14,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, dfu),
    &ciot__dfu_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "http_server",
    15,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, http_server),
    &ciot__http_server_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "http_client",
    16,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, http_client),
    &ciot__http_client_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "mqtt_client",
    17,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, mqtt_client),
    &ciot__mqtt_client_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "error",
    18,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, error),
    &ciot__msg_error__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "raw",
    19,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, raw),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "model",
    20,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, model),
    &ciot__model_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "log",
    21,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgData, log),
    &ciot__log__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__msg_data__field_indices_by_name[] = {
  8,   /* field[8] = ble */
  10,   /* field[10] = ble_adv */
  9,   /* field[9] = ble_scn */
  0,   /* field[0] = ciot */
  13,   /* field[13] = dfu */
  17,   /* field[17] = error */
  6,   /* field[6] = eth */
  15,   /* field[15] = http_client */
  14,   /* field[14] = http_server */
  20,   /* field[20] = log */
  19,   /* field[19] = model */
  16,   /* field[16] = mqtt_client */
  11,   /* field[11] = ntp */
  12,   /* field[12] = ota */
  18,   /* field[18] = raw */
  1,   /* field[1] = storage */
  2,   /* field[2] = sys */
  5,   /* field[5] = tcp */
  3,   /* field[3] = uart */
  4,   /* field[4] = usb */
  7,   /* field[7] = wifi */
};
static const ProtobufCIntRange ciot__msg_data__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 21 }
};
const ProtobufCMessageDescriptor ciot__msg_data__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.MsgData",
  "MsgData",
  "Ciot__MsgData",
  "Ciot",
  sizeof(Ciot__MsgData),
  21,
  ciot__msg_data__field_descriptors,
  ciot__msg_data__field_indices_by_name,
  1,  ciot__msg_data__number_ranges,
  (ProtobufCMessageInit) ciot__msg_data__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__msg_header__field_descriptors[3] =
{
  {
    "id",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgHeader, id),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "type",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgHeader, type),
    &ciot__msg_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "iface",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__MsgHeader, iface),
    &ciot__iface_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__msg_header__field_indices_by_name[] = {
  0,   /* field[0] = id */
  2,   /* field[2] = iface */
  1,   /* field[1] = type */
};
static const ProtobufCIntRange ciot__msg_header__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor ciot__msg_header__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.MsgHeader",
  "MsgHeader",
  "Ciot__MsgHeader",
  "Ciot",
  sizeof(Ciot__MsgHeader),
  3,
  ciot__msg_header__field_descriptors,
  ciot__msg_header__field_indices_by_name,
  1,  ciot__msg_header__number_ranges,
  (ProtobufCMessageInit) ciot__msg_header__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__msg__field_descriptors[4] =
{
  {
    "id",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Ciot__Msg, id),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "type",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__Msg, type),
    &ciot__msg_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "iface",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__Msg, iface),
    &ciot__iface_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "data",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__Msg, data),
    &ciot__msg_data__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__msg__field_indices_by_name[] = {
  3,   /* field[3] = data */
  0,   /* field[0] = id */
  2,   /* field[2] = iface */
  1,   /* field[1] = type */
};
static const ProtobufCIntRange ciot__msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor ciot__msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.Msg",
  "Msg",
  "Ciot__Msg",
  "Ciot",
  sizeof(Ciot__Msg),
  4,
  ciot__msg__field_descriptors,
  ciot__msg__field_indices_by_name,
  1,  ciot__msg__number_ranges,
  (ProtobufCMessageInit) ciot__msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue ciot__msg_type__enum_values_by_number[11] =
{
  { "MSG_TYPE_UNKNOWN", "CIOT__MSG_TYPE__MSG_TYPE_UNKNOWN", 0 },
  { "MSG_TYPE_START", "CIOT__MSG_TYPE__MSG_TYPE_START", 1 },
  { "MSG_TYPE_STOP", "CIOT__MSG_TYPE__MSG_TYPE_STOP", 2 },
  { "MSG_TYPE_CONFIG", "CIOT__MSG_TYPE__MSG_TYPE_CONFIG", 3 },
  { "MSG_TYPE_INFO", "CIOT__MSG_TYPE__MSG_TYPE_INFO", 4 },
  { "MSG_TYPE_STATUS", "CIOT__MSG_TYPE__MSG_TYPE_STATUS", 5 },
  { "MSG_TYPE_REQUEST", "CIOT__MSG_TYPE__MSG_TYPE_REQUEST", 6 },
  { "MSG_TYPE_ERROR", "CIOT__MSG_TYPE__MSG_TYPE_ERROR", 7 },
  { "MSG_TYPE_EVENT", "CIOT__MSG_TYPE__MSG_TYPE_EVENT", 8 },
  { "MSG_TYPE_CUSTOM", "CIOT__MSG_TYPE__MSG_TYPE_CUSTOM", 9 },
  { "MSG_TYPE_LOG", "CIOT__MSG_TYPE__MSG_TYPE_LOG", 10 },
};
static const ProtobufCIntRange ciot__msg_type__value_ranges[] = {
{0, 0},{0, 11}
};
static const ProtobufCEnumValueIndex ciot__msg_type__enum_values_by_name[11] =
{
  { "MSG_TYPE_CONFIG", 3 },
  { "MSG_TYPE_CUSTOM", 9 },
  { "MSG_TYPE_ERROR", 7 },
  { "MSG_TYPE_EVENT", 8 },
  { "MSG_TYPE_INFO", 4 },
  { "MSG_TYPE_LOG", 10 },
  { "MSG_TYPE_REQUEST", 6 },
  { "MSG_TYPE_START", 1 },
  { "MSG_TYPE_STATUS", 5 },
  { "MSG_TYPE_STOP", 2 },
  { "MSG_TYPE_UNKNOWN", 0 },
};
const ProtobufCEnumDescriptor ciot__msg_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.MsgType",
  "MsgType",
  "Ciot__MsgType",
  "Ciot",
  11,
  ciot__msg_type__enum_values_by_number,
  11,
  ciot__msg_type__enum_values_by_name,
  1,
  ciot__msg_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCEnumValue ciot__iface_type__enum_values_by_number[21] =
{
  { "IFACE_TYPE_UNKNOWN", "CIOT__IFACE_TYPE__IFACE_TYPE_UNKNOWN", 0 },
  { "IFACE_TYPE_CIOT", "CIOT__IFACE_TYPE__IFACE_TYPE_CIOT", 1 },
  { "IFACE_TYPE_STORAGE", "CIOT__IFACE_TYPE__IFACE_TYPE_STORAGE", 2 },
  { "IFACE_TYPE_SYS", "CIOT__IFACE_TYPE__IFACE_TYPE_SYS", 3 },
  { "IFACE_TYPE_UART", "CIOT__IFACE_TYPE__IFACE_TYPE_UART", 4 },
  { "IFACE_TYPE_USB", "CIOT__IFACE_TYPE__IFACE_TYPE_USB", 5 },
  { "IFACE_TYPE_TCP", "CIOT__IFACE_TYPE__IFACE_TYPE_TCP", 6 },
  { "IFACE_TYPE_ETH", "CIOT__IFACE_TYPE__IFACE_TYPE_ETH", 7 },
  { "IFACE_TYPE_WIFI", "CIOT__IFACE_TYPE__IFACE_TYPE_WIFI", 8 },
  { "IFACE_TYPE_BLE", "CIOT__IFACE_TYPE__IFACE_TYPE_BLE", 9 },
  { "IFACE_TYPE_BLE_SCN", "CIOT__IFACE_TYPE__IFACE_TYPE_BLE_SCN", 10 },
  { "IFACE_TYPE_BLE_ADV", "CIOT__IFACE_TYPE__IFACE_TYPE_BLE_ADV", 11 },
  { "IFACE_TYPE_GPIO", "CIOT__IFACE_TYPE__IFACE_TYPE_GPIO", 12 },
  { "IFACE_TYPE_NTP", "CIOT__IFACE_TYPE__IFACE_TYPE_NTP", 127 },
  { "IFACE_TYPE_OTA", "CIOT__IFACE_TYPE__IFACE_TYPE_OTA", 128 },
  { "IFACE_TYPE_DFU", "CIOT__IFACE_TYPE__IFACE_TYPE_DFU", 129 },
  { "IFACE_TYPE_HTTP_CLIENT", "CIOT__IFACE_TYPE__IFACE_TYPE_HTTP_CLIENT", 130 },
  { "IFACE_TYPE_HTTP_SERVER", "CIOT__IFACE_TYPE__IFACE_TYPE_HTTP_SERVER", 131 },
  { "IFACE_TYPE_MQTT", "CIOT__IFACE_TYPE__IFACE_TYPE_MQTT", 132 },
  { "IFACE_TYPE_BRIDGE", "CIOT__IFACE_TYPE__IFACE_TYPE_BRIDGE", 253 },
  { "IFACE_TYPE_CUSTOM", "CIOT__IFACE_TYPE__IFACE_TYPE_CUSTOM", 254 },
};
static const ProtobufCIntRange ciot__iface_type__value_ranges[] = {
{0, 0},{127, 13},{253, 19},{0, 21}
};
static const ProtobufCEnumValueIndex ciot__iface_type__enum_values_by_name[21] =
{
  { "IFACE_TYPE_BLE", 9 },
  { "IFACE_TYPE_BLE_ADV", 11 },
  { "IFACE_TYPE_BLE_SCN", 10 },
  { "IFACE_TYPE_BRIDGE", 19 },
  { "IFACE_TYPE_CIOT", 1 },
  { "IFACE_TYPE_CUSTOM", 20 },
  { "IFACE_TYPE_DFU", 15 },
  { "IFACE_TYPE_ETH", 7 },
  { "IFACE_TYPE_GPIO", 12 },
  { "IFACE_TYPE_HTTP_CLIENT", 16 },
  { "IFACE_TYPE_HTTP_SERVER", 17 },
  { "IFACE_TYPE_MQTT", 18 },
  { "IFACE_TYPE_NTP", 13 },
  { "IFACE_TYPE_OTA", 14 },
  { "IFACE_TYPE_STORAGE", 2 },
  { "IFACE_TYPE_SYS", 3 },
  { "IFACE_TYPE_TCP", 6 },
  { "IFACE_TYPE_UART", 4 },
  { "IFACE_TYPE_UNKNOWN", 0 },
  { "IFACE_TYPE_USB", 5 },
  { "IFACE_TYPE_WIFI", 8 },
};
const ProtobufCEnumDescriptor ciot__iface_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.IfaceType",
  "IfaceType",
  "Ciot__IfaceType",
  "Ciot",
  21,
  ciot__iface_type__enum_values_by_number,
  21,
  ciot__iface_type__enum_values_by_name,
  3,
  ciot__iface_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
