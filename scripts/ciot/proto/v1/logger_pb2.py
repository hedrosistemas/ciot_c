# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ciot/proto/v1/logger.proto

from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='ciot/proto/v1/logger.proto',
  package='Ciot',
  syntax='proto3',
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\x1a\x63iot/proto/v1/logger.proto\x12\x04\x43iot\"B\n\x03Log\x12\x1d\n\x05level\x18\x01 \x01(\x0e\x32\x0e.Ciot.LogLevel\x12\x0b\n\x03tag\x18\x02 \x01(\t\x12\x0f\n\x07message\x18\x03 \x01(\t*\x8a\x01\n\x08LogLevel\x12\x12\n\x0eLOG_LEVEL_NONE\x10\x00\x12\x13\n\x0fLOG_LEVEL_ERROR\x10\x01\x12\x15\n\x11LOG_LEVEL_WARNING\x10\x02\x12\x12\n\x0eLOG_LEVEL_INFO\x10\x03\x12\x15\n\x11LOG_LEVEL_VERBOSE\x10\x04\x12\x13\n\x0fLOG_LEVEL_DEBUG\x10\x05\x62\x06proto3'
)

_LOGLEVEL = _descriptor.EnumDescriptor(
  name='LogLevel',
  full_name='Ciot.LogLevel',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='LOG_LEVEL_NONE', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='LOG_LEVEL_ERROR', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='LOG_LEVEL_WARNING', index=2, number=2,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='LOG_LEVEL_INFO', index=3, number=3,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='LOG_LEVEL_VERBOSE', index=4, number=4,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='LOG_LEVEL_DEBUG', index=5, number=5,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=105,
  serialized_end=243,
)
_sym_db.RegisterEnumDescriptor(_LOGLEVEL)

LogLevel = enum_type_wrapper.EnumTypeWrapper(_LOGLEVEL)
LOG_LEVEL_NONE = 0
LOG_LEVEL_ERROR = 1
LOG_LEVEL_WARNING = 2
LOG_LEVEL_INFO = 3
LOG_LEVEL_VERBOSE = 4
LOG_LEVEL_DEBUG = 5



_LOG = _descriptor.Descriptor(
  name='Log',
  full_name='Ciot.Log',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='level', full_name='Ciot.Log.level', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='tag', full_name='Ciot.Log.tag', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='message', full_name='Ciot.Log.message', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=b"".decode('utf-8'),
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
  serialized_start=36,
  serialized_end=102,
)

_LOG.fields_by_name['level'].enum_type = _LOGLEVEL
DESCRIPTOR.message_types_by_name['Log'] = _LOG
DESCRIPTOR.enum_types_by_name['LogLevel'] = _LOGLEVEL
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Log = _reflection.GeneratedProtocolMessageType('Log', (_message.Message,), {
  'DESCRIPTOR' : _LOG,
  '__module__' : 'ciot.proto.v1.logger_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.Log)
  })
_sym_db.RegisterMessage(Log)


# @@protoc_insertion_point(module_scope)
