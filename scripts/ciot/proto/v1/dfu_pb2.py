# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ciot/proto/v1/dfu.proto

from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='ciot/proto/v1/dfu.proto',
  package='Ciot',
  syntax='proto3',
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\x17\x63iot/proto/v1/dfu.proto\x12\x04\x43iot\"%\n\x06\x44\x66uCfg\x12\x1b\n\x04type\x18\x01 \x01(\x0e\x32\r.Ciot.DfuType\"r\n\tDfuStatus\x12\x1d\n\x05state\x18\x01 \x01(\x0e\x32\x0e.Ciot.DfuState\x12\x0c\n\x04\x63ode\x18\x02 \x01(\x05\x12\r\n\x05\x65rror\x18\x03 \x01(\x05\x12\x12\n\nimage_size\x18\x04 \x01(\r\x12\x15\n\rimage_written\x18\x05 \x01(\r\"(\n\x06\x44\x66uReq\x12\x1e\n\x04type\x18\x01 \x01(\x0e\x32\x10.Ciot.DfuReqType\"g\n\x07\x44\x66uData\x12\x1c\n\x06\x63onfig\x18\x01 \x01(\x0b\x32\x0c.Ciot.DfuCfg\x12\x1f\n\x06status\x18\x02 \x01(\x0b\x32\x0f.Ciot.DfuStatus\x12\x1d\n\x07request\x18\x03 \x01(\x0b\x32\x0c.Ciot.DfuReq*p\n\x08\x44\x66uState\x12\x12\n\x0e\x44\x46U_STATE_IDLE\x10\x00\x12\x19\n\x15\x44\x46U_STATE_IN_PROGRESS\x10\x01\x12\x17\n\x13\x44\x46U_STATE_COMPLETED\x10\x02\x12\x1c\n\x0f\x44\x46U_STATE_ERROR\x10\xff\xff\xff\xff\xff\xff\xff\xff\xff\x01*@\n\nDfuReqType\x12\x17\n\x13\x44\x46U_REQ_TYPE_UNKOWN\x10\x00\x12\x19\n\x15\x44\x46U_REQ_SEND_FIRMWARE\x10\x01*V\n\x07\x44\x66uType\x12\x14\n\x10\x44\x46U_TYPE_UNKNOWN\x10\x00\x12\x11\n\rDFU_TYPE_UART\x10\x01\x12\x10\n\x0c\x44\x46U_TYPE_USB\x10\x02\x12\x10\n\x0c\x44\x46U_TYPE_BLE\x10\x03\x62\x06proto3'
)

_DFUSTATE = _descriptor.EnumDescriptor(
  name='DfuState',
  full_name='Ciot.DfuState',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='DFU_STATE_IDLE', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='DFU_STATE_IN_PROGRESS', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='DFU_STATE_COMPLETED', index=2, number=2,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='DFU_STATE_ERROR', index=3, number=-1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=335,
  serialized_end=447,
)
_sym_db.RegisterEnumDescriptor(_DFUSTATE)

DfuState = enum_type_wrapper.EnumTypeWrapper(_DFUSTATE)
_DFUREQTYPE = _descriptor.EnumDescriptor(
  name='DfuReqType',
  full_name='Ciot.DfuReqType',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='DFU_REQ_TYPE_UNKOWN', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='DFU_REQ_SEND_FIRMWARE', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=449,
  serialized_end=513,
)
_sym_db.RegisterEnumDescriptor(_DFUREQTYPE)

DfuReqType = enum_type_wrapper.EnumTypeWrapper(_DFUREQTYPE)
_DFUTYPE = _descriptor.EnumDescriptor(
  name='DfuType',
  full_name='Ciot.DfuType',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='DFU_TYPE_UNKNOWN', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='DFU_TYPE_UART', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='DFU_TYPE_USB', index=2, number=2,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='DFU_TYPE_BLE', index=3, number=3,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=515,
  serialized_end=601,
)
_sym_db.RegisterEnumDescriptor(_DFUTYPE)

DfuType = enum_type_wrapper.EnumTypeWrapper(_DFUTYPE)
DFU_STATE_IDLE = 0
DFU_STATE_IN_PROGRESS = 1
DFU_STATE_COMPLETED = 2
DFU_STATE_ERROR = -1
DFU_REQ_TYPE_UNKOWN = 0
DFU_REQ_SEND_FIRMWARE = 1
DFU_TYPE_UNKNOWN = 0
DFU_TYPE_UART = 1
DFU_TYPE_USB = 2
DFU_TYPE_BLE = 3



_DFUCFG = _descriptor.Descriptor(
  name='DfuCfg',
  full_name='Ciot.DfuCfg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='Ciot.DfuCfg.type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=33,
  serialized_end=70,
)


_DFUSTATUS = _descriptor.Descriptor(
  name='DfuStatus',
  full_name='Ciot.DfuStatus',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='state', full_name='Ciot.DfuStatus.state', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='code', full_name='Ciot.DfuStatus.code', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='error', full_name='Ciot.DfuStatus.error', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='image_size', full_name='Ciot.DfuStatus.image_size', index=3,
      number=4, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='image_written', full_name='Ciot.DfuStatus.image_written', index=4,
      number=5, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=72,
  serialized_end=186,
)


_DFUREQ = _descriptor.Descriptor(
  name='DfuReq',
  full_name='Ciot.DfuReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='Ciot.DfuReq.type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=188,
  serialized_end=228,
)


_DFUDATA = _descriptor.Descriptor(
  name='DfuData',
  full_name='Ciot.DfuData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='config', full_name='Ciot.DfuData.config', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='status', full_name='Ciot.DfuData.status', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='request', full_name='Ciot.DfuData.request', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=230,
  serialized_end=333,
)

_DFUCFG.fields_by_name['type'].enum_type = _DFUTYPE
_DFUSTATUS.fields_by_name['state'].enum_type = _DFUSTATE
_DFUREQ.fields_by_name['type'].enum_type = _DFUREQTYPE
_DFUDATA.fields_by_name['config'].message_type = _DFUCFG
_DFUDATA.fields_by_name['status'].message_type = _DFUSTATUS
_DFUDATA.fields_by_name['request'].message_type = _DFUREQ
DESCRIPTOR.message_types_by_name['DfuCfg'] = _DFUCFG
DESCRIPTOR.message_types_by_name['DfuStatus'] = _DFUSTATUS
DESCRIPTOR.message_types_by_name['DfuReq'] = _DFUREQ
DESCRIPTOR.message_types_by_name['DfuData'] = _DFUDATA
DESCRIPTOR.enum_types_by_name['DfuState'] = _DFUSTATE
DESCRIPTOR.enum_types_by_name['DfuReqType'] = _DFUREQTYPE
DESCRIPTOR.enum_types_by_name['DfuType'] = _DFUTYPE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

DfuCfg = _reflection.GeneratedProtocolMessageType('DfuCfg', (_message.Message,), {
  'DESCRIPTOR' : _DFUCFG,
  '__module__' : 'ciot.proto.v1.dfu_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.DfuCfg)
  })
_sym_db.RegisterMessage(DfuCfg)

DfuStatus = _reflection.GeneratedProtocolMessageType('DfuStatus', (_message.Message,), {
  'DESCRIPTOR' : _DFUSTATUS,
  '__module__' : 'ciot.proto.v1.dfu_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.DfuStatus)
  })
_sym_db.RegisterMessage(DfuStatus)

DfuReq = _reflection.GeneratedProtocolMessageType('DfuReq', (_message.Message,), {
  'DESCRIPTOR' : _DFUREQ,
  '__module__' : 'ciot.proto.v1.dfu_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.DfuReq)
  })
_sym_db.RegisterMessage(DfuReq)

DfuData = _reflection.GeneratedProtocolMessageType('DfuData', (_message.Message,), {
  'DESCRIPTOR' : _DFUDATA,
  '__module__' : 'ciot.proto.v1.dfu_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.DfuData)
  })
_sym_db.RegisterMessage(DfuData)


# @@protoc_insertion_point(module_scope)
