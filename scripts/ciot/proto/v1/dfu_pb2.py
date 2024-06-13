# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ciot/proto/v1/dfu.proto
# Protobuf Python Version: 5.26.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x17\x63iot/proto/v1/dfu.proto\x12\x04\x43iot\"%\n\x06\x44\x66uCfg\x12\x1b\n\x04type\x18\x01 \x01(\x0e\x32\r.Ciot.DfuType\"r\n\tDfuStatus\x12\x1d\n\x05state\x18\x01 \x01(\x0e\x32\x0e.Ciot.DfuState\x12\x0c\n\x04\x63ode\x18\x02 \x01(\x05\x12\r\n\x05\x65rror\x18\x03 \x01(\x05\x12\x12\n\nimage_size\x18\x04 \x01(\r\x12\x15\n\rimage_written\x18\x05 \x01(\r\",\n\nDfuRequest\x12\x1e\n\x04type\x18\x01 \x01(\x0e\x32\x10.Ciot.DfuReqType\"k\n\x07\x44\x66uData\x12\x1c\n\x06\x63onfig\x18\x01 \x01(\x0b\x32\x0c.Ciot.DfuCfg\x12\x1f\n\x06status\x18\x02 \x01(\x0b\x32\x0f.Ciot.DfuStatus\x12!\n\x07request\x18\x03 \x01(\x0b\x32\x10.Ciot.DfuRequest*R\n\x08\x44\x66uState\x12\x12\n\x0e\x44\x46U_STATE_IDLE\x10\x00\x12\x19\n\x15\x44\x46U_STATE_IN_PROGRESS\x10\x01\x12\x17\n\x13\x44\x46U_STATE_COMPLETED\x10\x02*@\n\nDfuReqType\x12\x17\n\x13\x44\x46U_REQ_TYPE_UNKOWN\x10\x00\x12\x19\n\x15\x44\x46U_REQ_SEND_FIRMWARE\x10\x01*V\n\x07\x44\x66uType\x12\x14\n\x10\x44\x46U_TYPE_UNKNOWN\x10\x00\x12\x11\n\rDFU_TYPE_UART\x10\x01\x12\x10\n\x0c\x44\x46U_TYPE_USB\x10\x02\x12\x10\n\x0c\x44\x46U_TYPE_BLE\x10\x03\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ciot.proto.v1.dfu_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_DFUSTATE']._serialized_start=343
  _globals['_DFUSTATE']._serialized_end=425
  _globals['_DFUREQTYPE']._serialized_start=427
  _globals['_DFUREQTYPE']._serialized_end=491
  _globals['_DFUTYPE']._serialized_start=493
  _globals['_DFUTYPE']._serialized_end=579
  _globals['_DFUCFG']._serialized_start=33
  _globals['_DFUCFG']._serialized_end=70
  _globals['_DFUSTATUS']._serialized_start=72
  _globals['_DFUSTATUS']._serialized_end=186
  _globals['_DFUREQUEST']._serialized_start=188
  _globals['_DFUREQUEST']._serialized_end=232
  _globals['_DFUDATA']._serialized_start=234
  _globals['_DFUDATA']._serialized_end=341
# @@protoc_insertion_point(module_scope)