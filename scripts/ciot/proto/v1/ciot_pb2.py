# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ciot/proto/v1/ciot.proto
# Protobuf Python Version: 5.26.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x18\x63iot/proto/v1/ciot.proto\x12\x04\x43iot\"\t\n\x07\x43iotCfg\"\x1b\n\x08\x43iotInfo\x12\x0f\n\x07version\x18\x01 \x01(\x0c\"J\n\nCiotStatus\x12\x1e\n\x05state\x18\x01 \x01(\x0e\x32\x0f.Ciot.CiotState\x12\x1c\n\x04info\x18\x03 \x01(\x0b\x32\x0e.Ciot.CiotInfo\"0\n\x0b\x43iotReqData\x12\x10\n\x08iface_id\x18\x01 \x01(\r\x12\x0f\n\x07payload\x18\x02 \x01(\x0c\"K\n\x07\x43iotReq\x12\x1f\n\x04type\x18\x01 \x01(\x0e\x32\x11.Ciot.CiotReqType\x12\x1f\n\x04\x64\x61ta\x18\x02 \x01(\x0b\x32\x11.Ciot.CiotReqData\"k\n\x08\x43iotData\x12\x1d\n\x06\x63onfig\x18\x01 \x01(\x0b\x32\r.Ciot.CiotCfg\x12 \n\x06status\x18\x02 \x01(\x0b\x32\x10.Ciot.CiotStatus\x12\x1e\n\x07request\x18\x03 \x01(\x0b\x32\r.Ciot.CiotReq*\x85\x01\n\tCiotState\x12\x13\n\x0f\x43IOT_STATE_IDLE\x10\x00\x12\x17\n\x13\x43IOT_STATE_STARTING\x10\x01\x12\x16\n\x12\x43IOT_STATE_STARTED\x10\x02\x12\x13\n\x0f\x43IOT_STATE_BUSY\x10\x03\x12\x1d\n\x10\x43IOT_STATE_ERROR\x10\xff\xff\xff\xff\xff\xff\xff\xff\xff\x01*\x8a\x01\n\x0b\x43iotReqType\x12\x18\n\x14\x43IOT_REQ_TYPE_UNKOWN\x10\x00\x12 \n\x1c\x43IOT_REQ_TYPE_SAVE_IFACE_CFG\x10\x01\x12\"\n\x1e\x43IOT_REQ_TYPE_DELETE_IFACE_CFG\x10\x02\x12\x1b\n\x17\x43IOT_REQ_TYPE_PROXY_MSG\x10\x03*8\n\x15\x43iotSerializationType\x12\x1f\n\x1b\x43IOT_SERIALIZATION_PROTOBUF\x10\x00\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ciot.proto.v1.ciot_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_CIOTSTATE']._serialized_start=387
  _globals['_CIOTSTATE']._serialized_end=520
  _globals['_CIOTREQTYPE']._serialized_start=523
  _globals['_CIOTREQTYPE']._serialized_end=661
  _globals['_CIOTSERIALIZATIONTYPE']._serialized_start=663
  _globals['_CIOTSERIALIZATIONTYPE']._serialized_end=719
  _globals['_CIOTCFG']._serialized_start=34
  _globals['_CIOTCFG']._serialized_end=43
  _globals['_CIOTINFO']._serialized_start=45
  _globals['_CIOTINFO']._serialized_end=72
  _globals['_CIOTSTATUS']._serialized_start=74
  _globals['_CIOTSTATUS']._serialized_end=148
  _globals['_CIOTREQDATA']._serialized_start=150
  _globals['_CIOTREQDATA']._serialized_end=198
  _globals['_CIOTREQ']._serialized_start=200
  _globals['_CIOTREQ']._serialized_end=275
  _globals['_CIOTDATA']._serialized_start=277
  _globals['_CIOTDATA']._serialized_end=384
# @@protoc_insertion_point(module_scope)
