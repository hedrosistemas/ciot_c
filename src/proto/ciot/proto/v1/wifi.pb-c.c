/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/wifi.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "ciot/proto/v1/wifi.pb-c.h"
void   ciot__wifi_ap_info__init
                     (Ciot__WifiApInfo         *message)
{
  static const Ciot__WifiApInfo init_value = CIOT__WIFI_AP_INFO__INIT;
  *message = init_value;
}
size_t ciot__wifi_ap_info__get_packed_size
                     (const Ciot__WifiApInfo *message)
{
  assert(message->base.descriptor == &ciot__wifi_ap_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__wifi_ap_info__pack
                     (const Ciot__WifiApInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__wifi_ap_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__wifi_ap_info__pack_to_buffer
                     (const Ciot__WifiApInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__wifi_ap_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__WifiApInfo *
       ciot__wifi_ap_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__WifiApInfo *)
     protobuf_c_message_unpack (&ciot__wifi_ap_info__descriptor,
                                allocator, len, data);
}
void   ciot__wifi_ap_info__free_unpacked
                     (Ciot__WifiApInfo *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__wifi_ap_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__wifi_cfg__init
                     (Ciot__WifiCfg         *message)
{
  static const Ciot__WifiCfg init_value = CIOT__WIFI_CFG__INIT;
  *message = init_value;
}
size_t ciot__wifi_cfg__get_packed_size
                     (const Ciot__WifiCfg *message)
{
  assert(message->base.descriptor == &ciot__wifi_cfg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__wifi_cfg__pack
                     (const Ciot__WifiCfg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__wifi_cfg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__wifi_cfg__pack_to_buffer
                     (const Ciot__WifiCfg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__wifi_cfg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__WifiCfg *
       ciot__wifi_cfg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__WifiCfg *)
     protobuf_c_message_unpack (&ciot__wifi_cfg__descriptor,
                                allocator, len, data);
}
void   ciot__wifi_cfg__free_unpacked
                     (Ciot__WifiCfg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__wifi_cfg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__wifi_status__init
                     (Ciot__WifiStatus         *message)
{
  static const Ciot__WifiStatus init_value = CIOT__WIFI_STATUS__INIT;
  *message = init_value;
}
size_t ciot__wifi_status__get_packed_size
                     (const Ciot__WifiStatus *message)
{
  assert(message->base.descriptor == &ciot__wifi_status__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__wifi_status__pack
                     (const Ciot__WifiStatus *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__wifi_status__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__wifi_status__pack_to_buffer
                     (const Ciot__WifiStatus *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__wifi_status__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__WifiStatus *
       ciot__wifi_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__WifiStatus *)
     protobuf_c_message_unpack (&ciot__wifi_status__descriptor,
                                allocator, len, data);
}
void   ciot__wifi_status__free_unpacked
                     (Ciot__WifiStatus *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__wifi_status__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__wifi_info__init
                     (Ciot__WifiInfo         *message)
{
  static const Ciot__WifiInfo init_value = CIOT__WIFI_INFO__INIT;
  *message = init_value;
}
size_t ciot__wifi_info__get_packed_size
                     (const Ciot__WifiInfo *message)
{
  assert(message->base.descriptor == &ciot__wifi_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__wifi_info__pack
                     (const Ciot__WifiInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__wifi_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__wifi_info__pack_to_buffer
                     (const Ciot__WifiInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__wifi_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__WifiInfo *
       ciot__wifi_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__WifiInfo *)
     protobuf_c_message_unpack (&ciot__wifi_info__descriptor,
                                allocator, len, data);
}
void   ciot__wifi_info__free_unpacked
                     (Ciot__WifiInfo *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__wifi_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__wifi_scan_result__init
                     (Ciot__WifiScanResult         *message)
{
  static const Ciot__WifiScanResult init_value = CIOT__WIFI_SCAN_RESULT__INIT;
  *message = init_value;
}
size_t ciot__wifi_scan_result__get_packed_size
                     (const Ciot__WifiScanResult *message)
{
  assert(message->base.descriptor == &ciot__wifi_scan_result__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__wifi_scan_result__pack
                     (const Ciot__WifiScanResult *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__wifi_scan_result__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__wifi_scan_result__pack_to_buffer
                     (const Ciot__WifiScanResult *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__wifi_scan_result__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__WifiScanResult *
       ciot__wifi_scan_result__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__WifiScanResult *)
     protobuf_c_message_unpack (&ciot__wifi_scan_result__descriptor,
                                allocator, len, data);
}
void   ciot__wifi_scan_result__free_unpacked
                     (Ciot__WifiScanResult *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__wifi_scan_result__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__wifi_req__init
                     (Ciot__WifiReq         *message)
{
  static const Ciot__WifiReq init_value = CIOT__WIFI_REQ__INIT;
  *message = init_value;
}
size_t ciot__wifi_req__get_packed_size
                     (const Ciot__WifiReq *message)
{
  assert(message->base.descriptor == &ciot__wifi_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__wifi_req__pack
                     (const Ciot__WifiReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__wifi_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__wifi_req__pack_to_buffer
                     (const Ciot__WifiReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__wifi_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__WifiReq *
       ciot__wifi_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__WifiReq *)
     protobuf_c_message_unpack (&ciot__wifi_req__descriptor,
                                allocator, len, data);
}
void   ciot__wifi_req__free_unpacked
                     (Ciot__WifiReq *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__wifi_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   ciot__wifi_data__init
                     (Ciot__WifiData         *message)
{
  static const Ciot__WifiData init_value = CIOT__WIFI_DATA__INIT;
  *message = init_value;
}
size_t ciot__wifi_data__get_packed_size
                     (const Ciot__WifiData *message)
{
  assert(message->base.descriptor == &ciot__wifi_data__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t ciot__wifi_data__pack
                     (const Ciot__WifiData *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &ciot__wifi_data__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t ciot__wifi_data__pack_to_buffer
                     (const Ciot__WifiData *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &ciot__wifi_data__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Ciot__WifiData *
       ciot__wifi_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Ciot__WifiData *)
     protobuf_c_message_unpack (&ciot__wifi_data__descriptor,
                                allocator, len, data);
}
void   ciot__wifi_data__free_unpacked
                     (Ciot__WifiData *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &ciot__wifi_data__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor ciot__wifi_ap_info__field_descriptors[4] =
{
  {
    "bssid",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiApInfo, bssid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ssid",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiApInfo, ssid),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "rssi",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiApInfo, rssi),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "authmode",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiApInfo, authmode),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__wifi_ap_info__field_indices_by_name[] = {
  3,   /* field[3] = authmode */
  0,   /* field[0] = bssid */
  2,   /* field[2] = rssi */
  1,   /* field[1] = ssid */
};
static const ProtobufCIntRange ciot__wifi_ap_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor ciot__wifi_ap_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.WifiApInfo",
  "WifiApInfo",
  "Ciot__WifiApInfo",
  "Ciot",
  sizeof(Ciot__WifiApInfo),
  4,
  ciot__wifi_ap_info__field_descriptors,
  ciot__wifi_ap_info__field_indices_by_name,
  1,  ciot__wifi_ap_info__number_ranges,
  (ProtobufCMessageInit) ciot__wifi_ap_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__wifi_cfg__field_descriptors[5] =
{
  {
    "disabled",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiCfg, disabled),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ssid",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiCfg, ssid),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "password",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiCfg, password),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "type",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiCfg, type),
    &ciot__wifi_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "tcp",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiCfg, tcp),
    &ciot__tcp_cfg__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__wifi_cfg__field_indices_by_name[] = {
  0,   /* field[0] = disabled */
  2,   /* field[2] = password */
  1,   /* field[1] = ssid */
  4,   /* field[4] = tcp */
  3,   /* field[3] = type */
};
static const ProtobufCIntRange ciot__wifi_cfg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 5 }
};
const ProtobufCMessageDescriptor ciot__wifi_cfg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.WifiCfg",
  "WifiCfg",
  "Ciot__WifiCfg",
  "Ciot",
  sizeof(Ciot__WifiCfg),
  5,
  ciot__wifi_cfg__field_descriptors,
  ciot__wifi_cfg__field_indices_by_name,
  1,  ciot__wifi_cfg__number_ranges,
  (ProtobufCMessageInit) ciot__wifi_cfg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__wifi_status__field_descriptors[2] =
{
  {
    "disconnect_reason",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiStatus, disconnect_reason),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "tcp",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiStatus, tcp),
    &ciot__tcp_status__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__wifi_status__field_indices_by_name[] = {
  0,   /* field[0] = disconnect_reason */
  1,   /* field[1] = tcp */
};
static const ProtobufCIntRange ciot__wifi_status__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor ciot__wifi_status__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.WifiStatus",
  "WifiStatus",
  "Ciot__WifiStatus",
  "Ciot",
  sizeof(Ciot__WifiStatus),
  2,
  ciot__wifi_status__field_descriptors,
  ciot__wifi_status__field_indices_by_name,
  1,  ciot__wifi_status__number_ranges,
  (ProtobufCMessageInit) ciot__wifi_status__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__wifi_info__field_descriptors[2] =
{
  {
    "tcp",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiInfo, tcp),
    &ciot__tcp_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ap",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiInfo, ap),
    &ciot__wifi_ap_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__wifi_info__field_indices_by_name[] = {
  1,   /* field[1] = ap */
  0,   /* field[0] = tcp */
};
static const ProtobufCIntRange ciot__wifi_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor ciot__wifi_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.WifiInfo",
  "WifiInfo",
  "Ciot__WifiInfo",
  "Ciot",
  sizeof(Ciot__WifiInfo),
  2,
  ciot__wifi_info__field_descriptors,
  ciot__wifi_info__field_indices_by_name,
  1,  ciot__wifi_info__number_ranges,
  (ProtobufCMessageInit) ciot__wifi_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__wifi_scan_result__field_descriptors[2] =
{
  {
    "count",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiScanResult, count),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ap_list",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Ciot__WifiScanResult, n_ap_list),
    offsetof(Ciot__WifiScanResult, ap_list),
    &ciot__wifi_ap_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__wifi_scan_result__field_indices_by_name[] = {
  1,   /* field[1] = ap_list */
  0,   /* field[0] = count */
};
static const ProtobufCIntRange ciot__wifi_scan_result__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor ciot__wifi_scan_result__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.WifiScanResult",
  "WifiScanResult",
  "Ciot__WifiScanResult",
  "Ciot",
  sizeof(Ciot__WifiScanResult),
  2,
  ciot__wifi_scan_result__field_descriptors,
  ciot__wifi_scan_result__field_indices_by_name,
  1,  ciot__wifi_scan_result__number_ranges,
  (ProtobufCMessageInit) ciot__wifi_scan_result__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__wifi_req__field_descriptors[2] =
{
  {
    "type",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiReq, type),
    &ciot__wifi_req_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "scan_result",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiReq, scan_result),
    &ciot__wifi_scan_result__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__wifi_req__field_indices_by_name[] = {
  1,   /* field[1] = scan_result */
  0,   /* field[0] = type */
};
static const ProtobufCIntRange ciot__wifi_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor ciot__wifi_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.WifiReq",
  "WifiReq",
  "Ciot__WifiReq",
  "Ciot",
  sizeof(Ciot__WifiReq),
  2,
  ciot__wifi_req__field_descriptors,
  ciot__wifi_req__field_indices_by_name,
  1,  ciot__wifi_req__number_ranges,
  (ProtobufCMessageInit) ciot__wifi_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor ciot__wifi_data__field_descriptors[4] =
{
  {
    "config",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Ciot__WifiData, config),
    &ciot__wifi_cfg__descriptor,
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
    offsetof(Ciot__WifiData, status),
    &ciot__wifi_status__descriptor,
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
    offsetof(Ciot__WifiData, request),
    &ciot__wifi_req__descriptor,
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
    offsetof(Ciot__WifiData, info),
    &ciot__wifi_info__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned ciot__wifi_data__field_indices_by_name[] = {
  0,   /* field[0] = config */
  3,   /* field[3] = info */
  2,   /* field[2] = request */
  1,   /* field[1] = status */
};
static const ProtobufCIntRange ciot__wifi_data__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor ciot__wifi_data__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Ciot.WifiData",
  "WifiData",
  "Ciot__WifiData",
  "Ciot",
  sizeof(Ciot__WifiData),
  4,
  ciot__wifi_data__field_descriptors,
  ciot__wifi_data__field_indices_by_name,
  1,  ciot__wifi_data__number_ranges,
  (ProtobufCMessageInit) ciot__wifi_data__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue ciot__wifi_type__enum_values_by_number[2] =
{
  { "WIFI_TYPE_STA", "CIOT__WIFI_TYPE__WIFI_TYPE_STA", 0 },
  { "WIFI_TYPE_AP", "CIOT__WIFI_TYPE__WIFI_TYPE_AP", 1 },
};
static const ProtobufCIntRange ciot__wifi_type__value_ranges[] = {
{0, 0},{0, 2}
};
static const ProtobufCEnumValueIndex ciot__wifi_type__enum_values_by_name[2] =
{
  { "WIFI_TYPE_AP", 1 },
  { "WIFI_TYPE_STA", 0 },
};
const ProtobufCEnumDescriptor ciot__wifi_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.WifiType",
  "WifiType",
  "Ciot__WifiType",
  "Ciot",
  2,
  ciot__wifi_type__enum_values_by_number,
  2,
  ciot__wifi_type__enum_values_by_name,
  1,
  ciot__wifi_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCEnumValue ciot__wifi_scan_state__enum_values_by_number[4] =
{
  { "WIFI_SCAN_STATE_IDLE", "CIOT__WIFI_SCAN_STATE__WIFI_SCAN_STATE_IDLE", 0 },
  { "WIFI_SCAN_STATE_SCANNING", "CIOT__WIFI_SCAN_STATE__WIFI_SCAN_STATE_SCANNING", 1 },
  { "WIFI_SCAN_STATE_SCANNED", "CIOT__WIFI_SCAN_STATE__WIFI_SCAN_STATE_SCANNED", 2 },
  { "WIFI_SCAN_STATE_ERROR", "CIOT__WIFI_SCAN_STATE__WIFI_SCAN_STATE_ERROR", 3 },
};
static const ProtobufCIntRange ciot__wifi_scan_state__value_ranges[] = {
{0, 0},{0, 4}
};
static const ProtobufCEnumValueIndex ciot__wifi_scan_state__enum_values_by_name[4] =
{
  { "WIFI_SCAN_STATE_ERROR", 3 },
  { "WIFI_SCAN_STATE_IDLE", 0 },
  { "WIFI_SCAN_STATE_SCANNED", 2 },
  { "WIFI_SCAN_STATE_SCANNING", 1 },
};
const ProtobufCEnumDescriptor ciot__wifi_scan_state__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.WifiScanState",
  "WifiScanState",
  "Ciot__WifiScanState",
  "Ciot",
  4,
  ciot__wifi_scan_state__enum_values_by_number,
  4,
  ciot__wifi_scan_state__enum_values_by_name,
  1,
  ciot__wifi_scan_state__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCEnumValue ciot__wifi_state__enum_values_by_number[1] =
{
  { "WIFI_STATE_IDLE", "CIOT__WIFI_STATE__WIFI_STATE_IDLE", 0 },
};
static const ProtobufCIntRange ciot__wifi_state__value_ranges[] = {
{0, 0},{0, 1}
};
static const ProtobufCEnumValueIndex ciot__wifi_state__enum_values_by_name[1] =
{
  { "WIFI_STATE_IDLE", 0 },
};
const ProtobufCEnumDescriptor ciot__wifi_state__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.WifiState",
  "WifiState",
  "Ciot__WifiState",
  "Ciot",
  1,
  ciot__wifi_state__enum_values_by_number,
  1,
  ciot__wifi_state__enum_values_by_name,
  1,
  ciot__wifi_state__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCEnumValue ciot__wifi_req_type__enum_values_by_number[2] =
{
  { "WIFI_REQ_TYPE_UNKOWN", "CIOT__WIFI_REQ_TYPE__WIFI_REQ_TYPE_UNKOWN", 0 },
  { "WIFI_REQ_SCAN", "CIOT__WIFI_REQ_TYPE__WIFI_REQ_SCAN", 1 },
};
static const ProtobufCIntRange ciot__wifi_req_type__value_ranges[] = {
{0, 0},{0, 2}
};
static const ProtobufCEnumValueIndex ciot__wifi_req_type__enum_values_by_name[2] =
{
  { "WIFI_REQ_SCAN", 1 },
  { "WIFI_REQ_TYPE_UNKOWN", 0 },
};
const ProtobufCEnumDescriptor ciot__wifi_req_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "Ciot.WifiReqType",
  "WifiReqType",
  "Ciot__WifiReqType",
  "Ciot",
  2,
  ciot__wifi_req_type__enum_values_by_number,
  2,
  ciot__wifi_req_type__enum_values_by_name,
  1,
  ciot__wifi_req_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
