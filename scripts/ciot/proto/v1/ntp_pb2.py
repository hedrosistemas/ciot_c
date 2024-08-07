# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ciot/proto/v1/ntp.proto
# Protobuf Python Version: 5.26.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x17\x63iot/proto/v1/ntp.proto\x12\x04\x43iot\"\x88\x01\n\x06NtpCfg\x12\x0f\n\x07op_mode\x18\x01 \x01(\x05\x12\x11\n\tsync_mode\x18\x02 \x01(\x05\x12\x15\n\rsync_interval\x18\x03 \x01(\x05\x12\x10\n\x08timezone\x18\x04 \x01(\t\x12\x0f\n\x07server1\x18\x05 \x01(\t\x12\x0f\n\x07server2\x18\x06 \x01(\t\x12\x0f\n\x07server3\x18\x07 \x01(\t\"m\n\tNtpStatus\x12\x1d\n\x05state\x18\x01 \x01(\x0e\x32\x0e.Ciot.NtpState\x12\x11\n\tlast_sync\x18\x02 \x01(\x04\x12\x12\n\nsync_count\x18\x03 \x01(\r\x12\x0c\n\x04init\x18\x04 \x01(\x08\x12\x0c\n\x04sync\x18\x05 \x01(\x08\"\x0c\n\nNtpReqData\"H\n\x06NtpReq\x12\x1e\n\x04type\x18\x01 \x01(\x0e\x32\x10.Ciot.NtpReqType\x12\x1e\n\x04\x64\x61ta\x18\x02 \x01(\x0b\x32\x10.Ciot.NtpReqData\"g\n\x07NtpData\x12\x1c\n\x06\x63onfig\x18\x01 \x01(\x0b\x32\x0c.Ciot.NtpCfg\x12\x1f\n\x06status\x18\x02 \x01(\x0b\x32\x0f.Ciot.NtpStatus\x12\x1d\n\x07request\x18\x03 \x01(\x0b\x32\x0c.Ciot.NtpReq*S\n\x08NtpState\x12\x13\n\x0fNTP_STATE_RESET\x10\x00\x12\x17\n\x13NTP_STATE_COMPLETED\x10\x01\x12\x19\n\x15NTP_STATE_IN_PROGRESS\x10\x02*%\n\nNtpReqType\x12\x17\n\x13NTP_REQ_TYPE_UNKOWN\x10\x00\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ciot.proto.v1.ntp_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_NTPSTATE']._serialized_start=476
  _globals['_NTPSTATE']._serialized_end=559
  _globals['_NTPREQTYPE']._serialized_start=561
  _globals['_NTPREQTYPE']._serialized_end=598
  _globals['_NTPCFG']._serialized_start=34
  _globals['_NTPCFG']._serialized_end=170
  _globals['_NTPSTATUS']._serialized_start=172
  _globals['_NTPSTATUS']._serialized_end=281
  _globals['_NTPREQDATA']._serialized_start=283
  _globals['_NTPREQDATA']._serialized_end=295
  _globals['_NTPREQ']._serialized_start=297
  _globals['_NTPREQ']._serialized_end=369
  _globals['_NTPDATA']._serialized_start=371
  _globals['_NTPDATA']._serialized_end=474
# @@protoc_insertion_point(module_scope)
