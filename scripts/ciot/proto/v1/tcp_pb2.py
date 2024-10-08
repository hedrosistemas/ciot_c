# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ciot/proto/v1/tcp.proto

from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='ciot/proto/v1/tcp.proto',
  package='Ciot',
  syntax='proto3',
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\x17\x63iot/proto/v1/tcp.proto\x12\x04\x43iot\"`\n\x06TcpCfg\x12\x1e\n\x04\x64hcp\x18\x01 \x01(\x0e\x32\x10.Ciot.TcpDhcpCfg\x12\n\n\x02ip\x18\x02 \x01(\x0c\x12\x0f\n\x07gateway\x18\x03 \x01(\x0c\x12\x0c\n\x04mask\x18\x04 \x01(\x0c\x12\x0b\n\x03\x64ns\x18\x05 \x01(\x0c\"W\n\rTcpDhcpStatus\x12\"\n\x06\x63lient\x18\x01 \x01(\x0e\x32\x12.Ciot.TcpDhcpState\x12\"\n\x06server\x18\x02 \x01(\x0e\x32\x12.Ciot.TcpDhcpState\"\"\n\x07TcpInfo\x12\x0b\n\x03mac\x18\x01 \x01(\x0c\x12\n\n\x02ip\x18\x02 \x01(\x0c\"a\n\tTcpStatus\x12\x1d\n\x05state\x18\x01 \x01(\x0e\x32\x0e.Ciot.TcpState\x12\x12\n\nconn_count\x18\x02 \x01(\r\x12!\n\x04\x64hcp\x18\x03 \x01(\x0b\x32\x13.Ciot.TcpDhcpStatus\"(\n\x06TcpReq\x12\x1e\n\x04type\x18\x01 \x01(\x0e\x32\x10.Ciot.TcpReqType\"\x84\x01\n\x07TcpData\x12\x1c\n\x06\x63onfig\x18\x01 \x01(\x0b\x32\x0c.Ciot.TcpCfg\x12\x1f\n\x06status\x18\x02 \x01(\x0b\x32\x0f.Ciot.TcpStatus\x12\x1d\n\x07request\x18\x03 \x01(\x0b\x32\x0c.Ciot.TcpReq\x12\x1b\n\x04info\x18\x04 \x01(\x0b\x32\r.Ciot.TcpInfo*\xa5\x01\n\x08TcpState\x12\x15\n\x11TCP_STATE_STARTED\x10\x00\x12\x15\n\x11TCP_STATE_STOPPED\x10\x01\x12\x1a\n\x16TCP_STATE_DISCONNECTED\x10\x02\x12\x18\n\x14TCP_STATE_CONNECTING\x10\x03\x12\x17\n\x13TCP_STATE_CONNECTED\x10\x04\x12\x1c\n\x0fTCP_STATE_ERROR\x10\xff\xff\xff\xff\xff\xff\xff\xff\xff\x01*_\n\x0cTcpDhcpState\x12\x17\n\x13TCP_DHCP_STATE_IDLE\x10\x00\x12\x1a\n\x16TCP_DHCP_STATE_STARTED\x10\x01\x12\x1a\n\x16TCP_DHCP_STATE_STOPPED\x10\x02*u\n\nTcpDhcpCfg\x12\x1a\n\x16TCP_DHCP_CFG_NO_CHANGE\x10\x00\x12\x17\n\x13TCP_DHCP_CFG_CLIENT\x10\x01\x12\x17\n\x13TCP_DHCP_CFG_SERVER\x10\x02\x12\x19\n\x15TCP_DHCP_CFG_DISABLED\x10\x03*%\n\nTcpReqType\x12\x17\n\x13TCP_REQ_TYPE_UNKOWN\x10\x00\x62\x06proto3'
)

_TCPSTATE = _descriptor.EnumDescriptor(
  name='TcpState',
  full_name='Ciot.TcpState',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='TCP_STATE_STARTED', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='TCP_STATE_STOPPED', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='TCP_STATE_DISCONNECTED', index=2, number=2,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='TCP_STATE_CONNECTING', index=3, number=3,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='TCP_STATE_CONNECTED', index=4, number=4,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='TCP_STATE_ERROR', index=5, number=-1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=533,
  serialized_end=698,
)
_sym_db.RegisterEnumDescriptor(_TCPSTATE)

TcpState = enum_type_wrapper.EnumTypeWrapper(_TCPSTATE)
_TCPDHCPSTATE = _descriptor.EnumDescriptor(
  name='TcpDhcpState',
  full_name='Ciot.TcpDhcpState',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='TCP_DHCP_STATE_IDLE', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='TCP_DHCP_STATE_STARTED', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='TCP_DHCP_STATE_STOPPED', index=2, number=2,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=700,
  serialized_end=795,
)
_sym_db.RegisterEnumDescriptor(_TCPDHCPSTATE)

TcpDhcpState = enum_type_wrapper.EnumTypeWrapper(_TCPDHCPSTATE)
_TCPDHCPCFG = _descriptor.EnumDescriptor(
  name='TcpDhcpCfg',
  full_name='Ciot.TcpDhcpCfg',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='TCP_DHCP_CFG_NO_CHANGE', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='TCP_DHCP_CFG_CLIENT', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='TCP_DHCP_CFG_SERVER', index=2, number=2,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='TCP_DHCP_CFG_DISABLED', index=3, number=3,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=797,
  serialized_end=914,
)
_sym_db.RegisterEnumDescriptor(_TCPDHCPCFG)

TcpDhcpCfg = enum_type_wrapper.EnumTypeWrapper(_TCPDHCPCFG)
_TCPREQTYPE = _descriptor.EnumDescriptor(
  name='TcpReqType',
  full_name='Ciot.TcpReqType',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='TCP_REQ_TYPE_UNKOWN', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=916,
  serialized_end=953,
)
_sym_db.RegisterEnumDescriptor(_TCPREQTYPE)

TcpReqType = enum_type_wrapper.EnumTypeWrapper(_TCPREQTYPE)
TCP_STATE_STARTED = 0
TCP_STATE_STOPPED = 1
TCP_STATE_DISCONNECTED = 2
TCP_STATE_CONNECTING = 3
TCP_STATE_CONNECTED = 4
TCP_STATE_ERROR = -1
TCP_DHCP_STATE_IDLE = 0
TCP_DHCP_STATE_STARTED = 1
TCP_DHCP_STATE_STOPPED = 2
TCP_DHCP_CFG_NO_CHANGE = 0
TCP_DHCP_CFG_CLIENT = 1
TCP_DHCP_CFG_SERVER = 2
TCP_DHCP_CFG_DISABLED = 3
TCP_REQ_TYPE_UNKOWN = 0



_TCPCFG = _descriptor.Descriptor(
  name='TcpCfg',
  full_name='Ciot.TcpCfg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='dhcp', full_name='Ciot.TcpCfg.dhcp', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='ip', full_name='Ciot.TcpCfg.ip', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='gateway', full_name='Ciot.TcpCfg.gateway', index=2,
      number=3, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='mask', full_name='Ciot.TcpCfg.mask', index=3,
      number=4, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='dns', full_name='Ciot.TcpCfg.dns', index=4,
      number=5, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
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
  serialized_end=129,
)


_TCPDHCPSTATUS = _descriptor.Descriptor(
  name='TcpDhcpStatus',
  full_name='Ciot.TcpDhcpStatus',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='client', full_name='Ciot.TcpDhcpStatus.client', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='server', full_name='Ciot.TcpDhcpStatus.server', index=1,
      number=2, type=14, cpp_type=8, label=1,
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
  serialized_start=131,
  serialized_end=218,
)


_TCPINFO = _descriptor.Descriptor(
  name='TcpInfo',
  full_name='Ciot.TcpInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='mac', full_name='Ciot.TcpInfo.mac', index=0,
      number=1, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='ip', full_name='Ciot.TcpInfo.ip', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
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
  serialized_start=220,
  serialized_end=254,
)


_TCPSTATUS = _descriptor.Descriptor(
  name='TcpStatus',
  full_name='Ciot.TcpStatus',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='state', full_name='Ciot.TcpStatus.state', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='conn_count', full_name='Ciot.TcpStatus.conn_count', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='dhcp', full_name='Ciot.TcpStatus.dhcp', index=2,
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
  serialized_start=256,
  serialized_end=353,
)


_TCPREQ = _descriptor.Descriptor(
  name='TcpReq',
  full_name='Ciot.TcpReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='Ciot.TcpReq.type', index=0,
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
  serialized_start=355,
  serialized_end=395,
)


_TCPDATA = _descriptor.Descriptor(
  name='TcpData',
  full_name='Ciot.TcpData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='config', full_name='Ciot.TcpData.config', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='status', full_name='Ciot.TcpData.status', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='request', full_name='Ciot.TcpData.request', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='info', full_name='Ciot.TcpData.info', index=3,
      number=4, type=11, cpp_type=10, label=1,
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
  serialized_start=398,
  serialized_end=530,
)

_TCPCFG.fields_by_name['dhcp'].enum_type = _TCPDHCPCFG
_TCPDHCPSTATUS.fields_by_name['client'].enum_type = _TCPDHCPSTATE
_TCPDHCPSTATUS.fields_by_name['server'].enum_type = _TCPDHCPSTATE
_TCPSTATUS.fields_by_name['state'].enum_type = _TCPSTATE
_TCPSTATUS.fields_by_name['dhcp'].message_type = _TCPDHCPSTATUS
_TCPREQ.fields_by_name['type'].enum_type = _TCPREQTYPE
_TCPDATA.fields_by_name['config'].message_type = _TCPCFG
_TCPDATA.fields_by_name['status'].message_type = _TCPSTATUS
_TCPDATA.fields_by_name['request'].message_type = _TCPREQ
_TCPDATA.fields_by_name['info'].message_type = _TCPINFO
DESCRIPTOR.message_types_by_name['TcpCfg'] = _TCPCFG
DESCRIPTOR.message_types_by_name['TcpDhcpStatus'] = _TCPDHCPSTATUS
DESCRIPTOR.message_types_by_name['TcpInfo'] = _TCPINFO
DESCRIPTOR.message_types_by_name['TcpStatus'] = _TCPSTATUS
DESCRIPTOR.message_types_by_name['TcpReq'] = _TCPREQ
DESCRIPTOR.message_types_by_name['TcpData'] = _TCPDATA
DESCRIPTOR.enum_types_by_name['TcpState'] = _TCPSTATE
DESCRIPTOR.enum_types_by_name['TcpDhcpState'] = _TCPDHCPSTATE
DESCRIPTOR.enum_types_by_name['TcpDhcpCfg'] = _TCPDHCPCFG
DESCRIPTOR.enum_types_by_name['TcpReqType'] = _TCPREQTYPE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

TcpCfg = _reflection.GeneratedProtocolMessageType('TcpCfg', (_message.Message,), {
  'DESCRIPTOR' : _TCPCFG,
  '__module__' : 'ciot.proto.v1.tcp_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.TcpCfg)
  })
_sym_db.RegisterMessage(TcpCfg)

TcpDhcpStatus = _reflection.GeneratedProtocolMessageType('TcpDhcpStatus', (_message.Message,), {
  'DESCRIPTOR' : _TCPDHCPSTATUS,
  '__module__' : 'ciot.proto.v1.tcp_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.TcpDhcpStatus)
  })
_sym_db.RegisterMessage(TcpDhcpStatus)

TcpInfo = _reflection.GeneratedProtocolMessageType('TcpInfo', (_message.Message,), {
  'DESCRIPTOR' : _TCPINFO,
  '__module__' : 'ciot.proto.v1.tcp_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.TcpInfo)
  })
_sym_db.RegisterMessage(TcpInfo)

TcpStatus = _reflection.GeneratedProtocolMessageType('TcpStatus', (_message.Message,), {
  'DESCRIPTOR' : _TCPSTATUS,
  '__module__' : 'ciot.proto.v1.tcp_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.TcpStatus)
  })
_sym_db.RegisterMessage(TcpStatus)

TcpReq = _reflection.GeneratedProtocolMessageType('TcpReq', (_message.Message,), {
  'DESCRIPTOR' : _TCPREQ,
  '__module__' : 'ciot.proto.v1.tcp_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.TcpReq)
  })
_sym_db.RegisterMessage(TcpReq)

TcpData = _reflection.GeneratedProtocolMessageType('TcpData', (_message.Message,), {
  'DESCRIPTOR' : _TCPDATA,
  '__module__' : 'ciot.proto.v1.tcp_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.TcpData)
  })
_sym_db.RegisterMessage(TcpData)


# @@protoc_insertion_point(module_scope)
