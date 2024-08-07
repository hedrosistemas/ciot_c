/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/errors.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "ciot/proto/v1/errors.pb-c.h"
static const ProtobufCEnumValue ciot_err__enum_values_by_number[30] =
{
  { "FAIL", "CIOT_ERR__FAIL", -1 },
  { "OK", "CIOT_ERR__OK", 0 },
  { "NULL_ARG", "CIOT_ERR__NULL_ARG", 1 },
  { "INVALID_ID", "CIOT_ERR__INVALID_ID", 2 },
  { "INVALID_TYPE", "CIOT_ERR__INVALID_TYPE", 3 },
  { "OVERFLOW", "CIOT_ERR__OVERFLOW", 4 },
  { "NOT_IMPLEMENTED", "CIOT_ERR__NOT_IMPLEMENTED", 5 },
  { "NOT_SUPPORTED", "CIOT_ERR__NOT_SUPPORTED", 6 },
  { "BUSY", "CIOT_ERR__BUSY", 7 },
  { "INVALID_STATE", "CIOT_ERR__INVALID_STATE", 8 },
  { "SERIALIZATION", "CIOT_ERR__SERIALIZATION", 9 },
  { "DESERIALIZATION", "CIOT_ERR__DESERIALIZATION", 10 },
  { "SEND_DATA", "CIOT_ERR__SEND_DATA", 11 },
  { "RECV_DATA", "CIOT_ERR__RECV_DATA", 12 },
  { "INVALID_SIZE", "CIOT_ERR__INVALID_SIZE", 13 },
  { "CLOSED", "CIOT_ERR__CLOSED", 14 },
  { "NOT_FOUND", "CIOT_ERR__NOT_FOUND", 15 },
  { "VALIDATION_FAILED", "CIOT_ERR__VALIDATION_FAILED", 16 },
  { "CONNECTION", "CIOT_ERR__CONNECTION", 17 },
  { "DISCONNECTION", "CIOT_ERR__DISCONNECTION", 18 },
  { "EXCEPTION", "CIOT_ERR__EXCEPTION", 19 },
  { "INVALID_ARG", "CIOT_ERR__INVALID_ARG", 20 },
  { "NO_MEMORY", "CIOT_ERR__NO_MEMORY", 21 },
  { "TIMEOUT", "CIOT_ERR__TIMEOUT", 22 },
  { "MONGOOSE", "CIOT_ERR__MONGOOSE", 23 },
  { "IMPOSSIBLE_OP", "CIOT_ERR__IMPOSSIBLE_OP", 24 },
  { "CHECKSUM", "CIOT_ERR__CHECKSUM", 25 },
  { "PROTOCOL_VIOLATION", "CIOT_ERR__PROTOCOL_VIOLATION", 26 },
  { "DATA_LOSS", "CIOT_ERR__DATA_LOSS", 27 },
  { "INVALID_HEADER", "CIOT_ERR__INVALID_HEADER", 28 },
};
static const ProtobufCIntRange ciot_err__value_ranges[] = {
{-1, 0},{0, 30}
};
static const ProtobufCEnumValueIndex ciot_err__enum_values_by_name[30] =
{
  { "BUSY", 8 },
  { "CHECKSUM", 26 },
  { "CLOSED", 15 },
  { "CONNECTION", 18 },
  { "DATA_LOSS", 28 },
  { "DESERIALIZATION", 11 },
  { "DISCONNECTION", 19 },
  { "EXCEPTION", 20 },
  { "FAIL", 0 },
  { "IMPOSSIBLE_OP", 25 },
  { "INVALID_ARG", 21 },
  { "INVALID_HEADER", 29 },
  { "INVALID_ID", 3 },
  { "INVALID_SIZE", 14 },
  { "INVALID_STATE", 9 },
  { "INVALID_TYPE", 4 },
  { "MONGOOSE", 24 },
  { "NOT_FOUND", 16 },
  { "NOT_IMPLEMENTED", 6 },
  { "NOT_SUPPORTED", 7 },
  { "NO_MEMORY", 22 },
  { "NULL_ARG", 2 },
  { "OK", 1 },
  { "OVERFLOW", 5 },
  { "PROTOCOL_VIOLATION", 27 },
  { "RECV_DATA", 13 },
  { "SEND_DATA", 12 },
  { "SERIALIZATION", 10 },
  { "TIMEOUT", 23 },
  { "VALIDATION_FAILED", 17 },
};
const ProtobufCEnumDescriptor ciot_err__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "CiotErr",
  "CiotErr",
  "CiotErr",
  "",
  30,
  ciot_err__enum_values_by_number,
  30,
  ciot_err__enum_values_by_name,
  1,
  ciot_err__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
