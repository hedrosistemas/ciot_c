# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ciot/proto/v1/model.proto
# Protobuf Python Version: 5.26.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x19\x63iot/proto/v1/model.proto\x12\x04\x43iot\"\n\n\x08ModelCfg\"=\n\x0bModelStatus\x12\x1f\n\x05state\x18\x01 \x01(\x0e\x32\x10.Ciot.ModelState\x12\r\n\x05\x65rror\x18\x02 \x01(\x05\"\x0b\n\tModelInfo\",\n\x08ModelReq\x12 \n\x04type\x18\x01 \x01(\x0e\x32\x12.Ciot.ModelReqType\"\x8e\x01\n\tModelData\x12\x1e\n\x06\x63onfig\x18\x01 \x01(\x0b\x32\x0e.Ciot.ModelCfg\x12!\n\x06status\x18\x02 \x01(\x0b\x32\x11.Ciot.ModelStatus\x12\x1f\n\x07request\x18\x03 \x01(\x0b\x32\x0e.Ciot.ModelReq\x12\x1d\n\x04info\x18\x04 \x01(\x0b\x32\x0f.Ciot.ModelInfo*\"\n\nModelState\x12\x14\n\x10MODEL_STATE_IDLE\x10\x00*)\n\x0cModelReqType\x12\x19\n\x15MODEL_REQ_TYPE_UNKOWN\x10\x00\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ciot.proto.v1.model_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_MODELSTATE']._serialized_start=314
  _globals['_MODELSTATE']._serialized_end=348
  _globals['_MODELREQTYPE']._serialized_start=350
  _globals['_MODELREQTYPE']._serialized_end=391
  _globals['_MODELCFG']._serialized_start=35
  _globals['_MODELCFG']._serialized_end=45
  _globals['_MODELSTATUS']._serialized_start=47
  _globals['_MODELSTATUS']._serialized_end=108
  _globals['_MODELINFO']._serialized_start=110
  _globals['_MODELINFO']._serialized_end=121
  _globals['_MODELREQ']._serialized_start=123
  _globals['_MODELREQ']._serialized_end=167
  _globals['_MODELDATA']._serialized_start=170
  _globals['_MODELDATA']._serialized_end=312
# @@protoc_insertion_point(module_scope)
