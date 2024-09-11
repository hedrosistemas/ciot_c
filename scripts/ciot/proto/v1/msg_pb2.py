# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ciot/proto/v1/msg.proto

from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from ciot.proto.v1 import ble_adv_pb2 as ciot_dot_proto_dot_v1_dot_ble__adv__pb2
from ciot.proto.v1 import ble_scn_pb2 as ciot_dot_proto_dot_v1_dot_ble__scn__pb2
from ciot.proto.v1 import ble_pb2 as ciot_dot_proto_dot_v1_dot_ble__pb2
from ciot.proto.v1 import ciot_pb2 as ciot_dot_proto_dot_v1_dot_ciot__pb2
from ciot.proto.v1 import dfu_pb2 as ciot_dot_proto_dot_v1_dot_dfu__pb2
from ciot.proto.v1 import errors_pb2 as ciot_dot_proto_dot_v1_dot_errors__pb2
from ciot.proto.v1 import http_client_pb2 as ciot_dot_proto_dot_v1_dot_http__client__pb2
from ciot.proto.v1 import http_server_pb2 as ciot_dot_proto_dot_v1_dot_http__server__pb2
from ciot.proto.v1 import logger_pb2 as ciot_dot_proto_dot_v1_dot_logger__pb2
from ciot.proto.v1 import model_pb2 as ciot_dot_proto_dot_v1_dot_model__pb2
from ciot.proto.v1 import mqtt_client_pb2 as ciot_dot_proto_dot_v1_dot_mqtt__client__pb2
from ciot.proto.v1 import ntp_pb2 as ciot_dot_proto_dot_v1_dot_ntp__pb2
from ciot.proto.v1 import ota_pb2 as ciot_dot_proto_dot_v1_dot_ota__pb2
from ciot.proto.v1 import storage_pb2 as ciot_dot_proto_dot_v1_dot_storage__pb2
from ciot.proto.v1 import socket_pb2 as ciot_dot_proto_dot_v1_dot_socket__pb2
from ciot.proto.v1 import sys_pb2 as ciot_dot_proto_dot_v1_dot_sys__pb2
from ciot.proto.v1 import tcp_pb2 as ciot_dot_proto_dot_v1_dot_tcp__pb2
from ciot.proto.v1 import uart_pb2 as ciot_dot_proto_dot_v1_dot_uart__pb2
from ciot.proto.v1 import usb_pb2 as ciot_dot_proto_dot_v1_dot_usb__pb2
from ciot.proto.v1 import wifi_pb2 as ciot_dot_proto_dot_v1_dot_wifi__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='ciot/proto/v1/msg.proto',
  package='Ciot',
  syntax='proto3',
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\x17\x63iot/proto/v1/msg.proto\x12\x04\x43iot\x1a\x1b\x63iot/proto/v1/ble_adv.proto\x1a\x1b\x63iot/proto/v1/ble_scn.proto\x1a\x17\x63iot/proto/v1/ble.proto\x1a\x18\x63iot/proto/v1/ciot.proto\x1a\x17\x63iot/proto/v1/dfu.proto\x1a\x1a\x63iot/proto/v1/errors.proto\x1a\x1f\x63iot/proto/v1/http_client.proto\x1a\x1f\x63iot/proto/v1/http_server.proto\x1a\x1a\x63iot/proto/v1/logger.proto\x1a\x19\x63iot/proto/v1/model.proto\x1a\x1f\x63iot/proto/v1/mqtt_client.proto\x1a\x17\x63iot/proto/v1/ntp.proto\x1a\x17\x63iot/proto/v1/ota.proto\x1a\x1b\x63iot/proto/v1/storage.proto\x1a\x1a\x63iot/proto/v1/socket.proto\x1a\x17\x63iot/proto/v1/sys.proto\x1a\x17\x63iot/proto/v1/tcp.proto\x1a\x18\x63iot/proto/v1/uart.proto\x1a\x17\x63iot/proto/v1/usb.proto\x1a\x18\x63iot/proto/v1/wifi.proto\"6\n\tIfaceInfo\x12\n\n\x02id\x18\x01 \x01(\r\x12\x1d\n\x04type\x18\x02 \x01(\x0e\x32\x0f.Ciot.IfaceType\"`\n\x08MsgError\x12\x1c\n\x03msg\x18\x01 \x01(\x0b\x32\x0f.Ciot.MsgHeader\x12\x1e\n\x05iface\x18\x02 \x01(\x0b\x32\x0f.Ciot.IfaceInfo\x12\x16\n\x04\x63ode\x18\x03 \x01(\x0e\x32\x08.CiotErr\"\xb8\x05\n\x07MsgData\x12\x1d\n\x05\x65rror\x18\x01 \x01(\x0b\x32\x0e.Ciot.MsgError\x12\x0f\n\x07payload\x18\x02 \x01(\x0c\x12\x1e\n\x05model\x18\x03 \x01(\x0b\x32\x0f.Ciot.ModelData\x12\x16\n\x03log\x18\x04 \x01(\x0b\x32\t.Ciot.Log\x12\x1c\n\x04\x63iot\x18\x05 \x01(\x0b\x32\x0e.Ciot.CiotData\x12\"\n\x07storage\x18\x06 \x01(\x0b\x32\x11.Ciot.StorageData\x12\x1a\n\x03sys\x18\x07 \x01(\x0b\x32\r.Ciot.SysData\x12\x1c\n\x04uart\x18\x08 \x01(\x0b\x32\x0e.Ciot.UartData\x12\x1a\n\x03usb\x18\t \x01(\x0b\x32\r.Ciot.UsbData\x12\x1a\n\x03tcp\x18\n \x01(\x0b\x32\r.Ciot.TcpData\x12\x1a\n\x03\x65th\x18\x0b \x01(\x0b\x32\r.Ciot.TcpData\x12\x1c\n\x04wifi\x18\x0c \x01(\x0b\x32\x0e.Ciot.WifiData\x12\x1a\n\x03\x62le\x18\r \x01(\x0b\x32\r.Ciot.BleData\x12!\n\x07\x62le_scn\x18\x0e \x01(\x0b\x32\x10.Ciot.BleScnData\x12!\n\x07\x62le_adv\x18\x0f \x01(\x0b\x32\x10.Ciot.BleAdvData\x12\x1a\n\x03ntp\x18\x10 \x01(\x0b\x32\r.Ciot.NtpData\x12\x1a\n\x03ota\x18\x11 \x01(\x0b\x32\r.Ciot.OtaData\x12\x1a\n\x03\x64\x66u\x18\x12 \x01(\x0b\x32\r.Ciot.DfuData\x12)\n\x0bhttp_server\x18\x13 \x01(\x0b\x32\x14.Ciot.HttpServerData\x12)\n\x0bhttp_client\x18\x14 \x01(\x0b\x32\x14.Ciot.HttpClientData\x12)\n\x0bmqtt_client\x18\x15 \x01(\x0b\x32\x14.Ciot.MqttClientData\x12 \n\x06socket\x18\x16 \x01(\x0b\x32\x10.Ciot.SocketData\"T\n\tMsgHeader\x12\n\n\x02id\x18\x01 \x01(\r\x12\x1b\n\x04type\x18\x02 \x01(\x0e\x32\r.Ciot.MsgType\x12\x1e\n\x05iface\x18\x03 \x01(\x0b\x32\x0f.Ciot.IfaceInfo\"k\n\x03Msg\x12\n\n\x02id\x18\x01 \x01(\r\x12\x1b\n\x04type\x18\x02 \x01(\x0e\x32\r.Ciot.MsgType\x12\x1e\n\x05iface\x18\x03 \x01(\x0b\x32\x0f.Ciot.IfaceInfo\x12\x1b\n\x04\x64\x61ta\x18\x04 \x01(\x0b\x32\r.Ciot.MsgData*\x83\x02\n\x07MsgType\x12\x14\n\x10MSG_TYPE_UNKNOWN\x10\x00\x12\x13\n\x0fMSG_TYPE_CUSTOM\x10\x01\x12\x12\n\x0eMSG_TYPE_START\x10\x02\x12\x11\n\rMSG_TYPE_STOP\x10\x03\x12\x13\n\x0fMSG_TYPE_CONFIG\x10\x04\x12\x11\n\rMSG_TYPE_INFO\x10\x05\x12\x13\n\x0fMSG_TYPE_STATUS\x10\x06\x12\x14\n\x10MSG_TYPE_REQUEST\x10\x07\x12\x19\n\x15MSG_TYPE_SEND_PAYLOAD\x10\x08\x12\x12\n\x0eMSG_TYPE_ERROR\x10\t\x12\x12\n\x0eMSG_TYPE_EVENT\x10\n\x12\x10\n\x0cMSG_TYPE_LOG\x10\x0b*\xf1\x03\n\tIfaceType\x12\x16\n\x12IFACE_TYPE_UNKNOWN\x10\x00\x12\x15\n\x11IFACE_TYPE_CUSTOM\x10\x01\x12\x13\n\x0fIFACE_TYPE_CIOT\x10\x02\x12\x16\n\x12IFACE_TYPE_STORAGE\x10\x03\x12\x12\n\x0eIFACE_TYPE_SYS\x10\x04\x12\x13\n\x0fIFACE_TYPE_UART\x10\x05\x12\x12\n\x0eIFACE_TYPE_USB\x10\x06\x12\x12\n\x0eIFACE_TYPE_TCP\x10\x07\x12\x12\n\x0eIFACE_TYPE_ETH\x10\x08\x12\x13\n\x0fIFACE_TYPE_WIFI\x10\t\x12\x12\n\x0eIFACE_TYPE_BLE\x10\n\x12\x16\n\x12IFACE_TYPE_BLE_SCN\x10\x0b\x12\x16\n\x12IFACE_TYPE_BLE_ADV\x10\x0c\x12\x13\n\x0fIFACE_TYPE_GPIO\x10\r\x12\x12\n\x0eIFACE_TYPE_NTP\x10\x0e\x12\x12\n\x0eIFACE_TYPE_OTA\x10\x0f\x12\x12\n\x0eIFACE_TYPE_DFU\x10\x10\x12\x1a\n\x16IFACE_TYPE_HTTP_CLIENT\x10\x11\x12\x1a\n\x16IFACE_TYPE_HTTP_SERVER\x10\x12\x12\x13\n\x0fIFACE_TYPE_MQTT\x10\x13\x12\x15\n\x11IFACE_TYPE_SOCKET\x10\x14\x12\x15\n\x11IFACE_TYPE_BRIDGE\x10\x15\x62\x06proto3'
  ,
  dependencies=[ciot_dot_proto_dot_v1_dot_ble__adv__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_ble__scn__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_ble__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_ciot__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_dfu__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_errors__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_http__client__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_http__server__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_logger__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_model__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_mqtt__client__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_ntp__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_ota__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_storage__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_socket__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_sys__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_tcp__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_uart__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_usb__pb2.DESCRIPTOR,ciot_dot_proto_dot_v1_dot_wifi__pb2.DESCRIPTOR,])

_MSGTYPE = _descriptor.EnumDescriptor(
  name='MsgType',
  full_name='Ciot.MsgType',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_UNKNOWN', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_CUSTOM', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_START', index=2, number=2,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_STOP', index=3, number=3,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_CONFIG', index=4, number=4,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_INFO', index=5, number=5,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_STATUS', index=6, number=6,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_REQUEST', index=7, number=7,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_SEND_PAYLOAD', index=8, number=8,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_ERROR', index=9, number=9,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_EVENT', index=10, number=10,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='MSG_TYPE_LOG', index=11, number=11,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1632,
  serialized_end=1891,
)
_sym_db.RegisterEnumDescriptor(_MSGTYPE)

MsgType = enum_type_wrapper.EnumTypeWrapper(_MSGTYPE)
_IFACETYPE = _descriptor.EnumDescriptor(
  name='IfaceType',
  full_name='Ciot.IfaceType',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_UNKNOWN', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_CUSTOM', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_CIOT', index=2, number=2,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_STORAGE', index=3, number=3,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_SYS', index=4, number=4,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_UART', index=5, number=5,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_USB', index=6, number=6,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_TCP', index=7, number=7,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_ETH', index=8, number=8,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_WIFI', index=9, number=9,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_BLE', index=10, number=10,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_BLE_SCN', index=11, number=11,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_BLE_ADV', index=12, number=12,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_GPIO', index=13, number=13,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_NTP', index=14, number=14,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_OTA', index=15, number=15,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_DFU', index=16, number=16,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_HTTP_CLIENT', index=17, number=17,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_HTTP_SERVER', index=18, number=18,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_MQTT', index=19, number=19,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_SOCKET', index=20, number=20,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='IFACE_TYPE_BRIDGE', index=21, number=21,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=1894,
  serialized_end=2391,
)
_sym_db.RegisterEnumDescriptor(_IFACETYPE)

IfaceType = enum_type_wrapper.EnumTypeWrapper(_IFACETYPE)
MSG_TYPE_UNKNOWN = 0
MSG_TYPE_CUSTOM = 1
MSG_TYPE_START = 2
MSG_TYPE_STOP = 3
MSG_TYPE_CONFIG = 4
MSG_TYPE_INFO = 5
MSG_TYPE_STATUS = 6
MSG_TYPE_REQUEST = 7
MSG_TYPE_SEND_PAYLOAD = 8
MSG_TYPE_ERROR = 9
MSG_TYPE_EVENT = 10
MSG_TYPE_LOG = 11
IFACE_TYPE_UNKNOWN = 0
IFACE_TYPE_CUSTOM = 1
IFACE_TYPE_CIOT = 2
IFACE_TYPE_STORAGE = 3
IFACE_TYPE_SYS = 4
IFACE_TYPE_UART = 5
IFACE_TYPE_USB = 6
IFACE_TYPE_TCP = 7
IFACE_TYPE_ETH = 8
IFACE_TYPE_WIFI = 9
IFACE_TYPE_BLE = 10
IFACE_TYPE_BLE_SCN = 11
IFACE_TYPE_BLE_ADV = 12
IFACE_TYPE_GPIO = 13
IFACE_TYPE_NTP = 14
IFACE_TYPE_OTA = 15
IFACE_TYPE_DFU = 16
IFACE_TYPE_HTTP_CLIENT = 17
IFACE_TYPE_HTTP_SERVER = 18
IFACE_TYPE_MQTT = 19
IFACE_TYPE_SOCKET = 20
IFACE_TYPE_BRIDGE = 21



_IFACEINFO = _descriptor.Descriptor(
  name='IfaceInfo',
  full_name='Ciot.IfaceInfo',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='Ciot.IfaceInfo.id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='type', full_name='Ciot.IfaceInfo.type', index=1,
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
  serialized_start=583,
  serialized_end=637,
)


_MSGERROR = _descriptor.Descriptor(
  name='MsgError',
  full_name='Ciot.MsgError',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='msg', full_name='Ciot.MsgError.msg', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='iface', full_name='Ciot.MsgError.iface', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='code', full_name='Ciot.MsgError.code', index=2,
      number=3, type=14, cpp_type=8, label=1,
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
  serialized_start=639,
  serialized_end=735,
)


_MSGDATA = _descriptor.Descriptor(
  name='MsgData',
  full_name='Ciot.MsgData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='error', full_name='Ciot.MsgData.error', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='payload', full_name='Ciot.MsgData.payload', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=b"",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='model', full_name='Ciot.MsgData.model', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='log', full_name='Ciot.MsgData.log', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='ciot', full_name='Ciot.MsgData.ciot', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='storage', full_name='Ciot.MsgData.storage', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='sys', full_name='Ciot.MsgData.sys', index=6,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='uart', full_name='Ciot.MsgData.uart', index=7,
      number=8, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='usb', full_name='Ciot.MsgData.usb', index=8,
      number=9, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='tcp', full_name='Ciot.MsgData.tcp', index=9,
      number=10, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='eth', full_name='Ciot.MsgData.eth', index=10,
      number=11, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='wifi', full_name='Ciot.MsgData.wifi', index=11,
      number=12, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='ble', full_name='Ciot.MsgData.ble', index=12,
      number=13, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='ble_scn', full_name='Ciot.MsgData.ble_scn', index=13,
      number=14, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='ble_adv', full_name='Ciot.MsgData.ble_adv', index=14,
      number=15, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='ntp', full_name='Ciot.MsgData.ntp', index=15,
      number=16, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='ota', full_name='Ciot.MsgData.ota', index=16,
      number=17, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='dfu', full_name='Ciot.MsgData.dfu', index=17,
      number=18, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='http_server', full_name='Ciot.MsgData.http_server', index=18,
      number=19, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='http_client', full_name='Ciot.MsgData.http_client', index=19,
      number=20, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='mqtt_client', full_name='Ciot.MsgData.mqtt_client', index=20,
      number=21, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='socket', full_name='Ciot.MsgData.socket', index=21,
      number=22, type=11, cpp_type=10, label=1,
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
  serialized_start=738,
  serialized_end=1434,
)


_MSGHEADER = _descriptor.Descriptor(
  name='MsgHeader',
  full_name='Ciot.MsgHeader',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='Ciot.MsgHeader.id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='type', full_name='Ciot.MsgHeader.type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='iface', full_name='Ciot.MsgHeader.iface', index=2,
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
  serialized_start=1436,
  serialized_end=1520,
)


_MSG = _descriptor.Descriptor(
  name='Msg',
  full_name='Ciot.Msg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='Ciot.Msg.id', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='type', full_name='Ciot.Msg.type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='iface', full_name='Ciot.Msg.iface', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='data', full_name='Ciot.Msg.data', index=3,
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
  serialized_start=1522,
  serialized_end=1629,
)

_IFACEINFO.fields_by_name['type'].enum_type = _IFACETYPE
_MSGERROR.fields_by_name['msg'].message_type = _MSGHEADER
_MSGERROR.fields_by_name['iface'].message_type = _IFACEINFO
_MSGERROR.fields_by_name['code'].enum_type = ciot_dot_proto_dot_v1_dot_errors__pb2._CIOTERR
_MSGDATA.fields_by_name['error'].message_type = _MSGERROR
_MSGDATA.fields_by_name['model'].message_type = ciot_dot_proto_dot_v1_dot_model__pb2._MODELDATA
_MSGDATA.fields_by_name['log'].message_type = ciot_dot_proto_dot_v1_dot_logger__pb2._LOG
_MSGDATA.fields_by_name['ciot'].message_type = ciot_dot_proto_dot_v1_dot_ciot__pb2._CIOTDATA
_MSGDATA.fields_by_name['storage'].message_type = ciot_dot_proto_dot_v1_dot_storage__pb2._STORAGEDATA
_MSGDATA.fields_by_name['sys'].message_type = ciot_dot_proto_dot_v1_dot_sys__pb2._SYSDATA
_MSGDATA.fields_by_name['uart'].message_type = ciot_dot_proto_dot_v1_dot_uart__pb2._UARTDATA
_MSGDATA.fields_by_name['usb'].message_type = ciot_dot_proto_dot_v1_dot_usb__pb2._USBDATA
_MSGDATA.fields_by_name['tcp'].message_type = ciot_dot_proto_dot_v1_dot_tcp__pb2._TCPDATA
_MSGDATA.fields_by_name['eth'].message_type = ciot_dot_proto_dot_v1_dot_tcp__pb2._TCPDATA
_MSGDATA.fields_by_name['wifi'].message_type = ciot_dot_proto_dot_v1_dot_wifi__pb2._WIFIDATA
_MSGDATA.fields_by_name['ble'].message_type = ciot_dot_proto_dot_v1_dot_ble__pb2._BLEDATA
_MSGDATA.fields_by_name['ble_scn'].message_type = ciot_dot_proto_dot_v1_dot_ble__scn__pb2._BLESCNDATA
_MSGDATA.fields_by_name['ble_adv'].message_type = ciot_dot_proto_dot_v1_dot_ble__adv__pb2._BLEADVDATA
_MSGDATA.fields_by_name['ntp'].message_type = ciot_dot_proto_dot_v1_dot_ntp__pb2._NTPDATA
_MSGDATA.fields_by_name['ota'].message_type = ciot_dot_proto_dot_v1_dot_ota__pb2._OTADATA
_MSGDATA.fields_by_name['dfu'].message_type = ciot_dot_proto_dot_v1_dot_dfu__pb2._DFUDATA
_MSGDATA.fields_by_name['http_server'].message_type = ciot_dot_proto_dot_v1_dot_http__server__pb2._HTTPSERVERDATA
_MSGDATA.fields_by_name['http_client'].message_type = ciot_dot_proto_dot_v1_dot_http__client__pb2._HTTPCLIENTDATA
_MSGDATA.fields_by_name['mqtt_client'].message_type = ciot_dot_proto_dot_v1_dot_mqtt__client__pb2._MQTTCLIENTDATA
_MSGDATA.fields_by_name['socket'].message_type = ciot_dot_proto_dot_v1_dot_socket__pb2._SOCKETDATA
_MSGHEADER.fields_by_name['type'].enum_type = _MSGTYPE
_MSGHEADER.fields_by_name['iface'].message_type = _IFACEINFO
_MSG.fields_by_name['type'].enum_type = _MSGTYPE
_MSG.fields_by_name['iface'].message_type = _IFACEINFO
_MSG.fields_by_name['data'].message_type = _MSGDATA
DESCRIPTOR.message_types_by_name['IfaceInfo'] = _IFACEINFO
DESCRIPTOR.message_types_by_name['MsgError'] = _MSGERROR
DESCRIPTOR.message_types_by_name['MsgData'] = _MSGDATA
DESCRIPTOR.message_types_by_name['MsgHeader'] = _MSGHEADER
DESCRIPTOR.message_types_by_name['Msg'] = _MSG
DESCRIPTOR.enum_types_by_name['MsgType'] = _MSGTYPE
DESCRIPTOR.enum_types_by_name['IfaceType'] = _IFACETYPE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

IfaceInfo = _reflection.GeneratedProtocolMessageType('IfaceInfo', (_message.Message,), {
  'DESCRIPTOR' : _IFACEINFO,
  '__module__' : 'ciot.proto.v1.msg_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.IfaceInfo)
  })
_sym_db.RegisterMessage(IfaceInfo)

MsgError = _reflection.GeneratedProtocolMessageType('MsgError', (_message.Message,), {
  'DESCRIPTOR' : _MSGERROR,
  '__module__' : 'ciot.proto.v1.msg_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.MsgError)
  })
_sym_db.RegisterMessage(MsgError)

MsgData = _reflection.GeneratedProtocolMessageType('MsgData', (_message.Message,), {
  'DESCRIPTOR' : _MSGDATA,
  '__module__' : 'ciot.proto.v1.msg_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.MsgData)
  })
_sym_db.RegisterMessage(MsgData)

MsgHeader = _reflection.GeneratedProtocolMessageType('MsgHeader', (_message.Message,), {
  'DESCRIPTOR' : _MSGHEADER,
  '__module__' : 'ciot.proto.v1.msg_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.MsgHeader)
  })
_sym_db.RegisterMessage(MsgHeader)

Msg = _reflection.GeneratedProtocolMessageType('Msg', (_message.Message,), {
  'DESCRIPTOR' : _MSG,
  '__module__' : 'ciot.proto.v1.msg_pb2'
  # @@protoc_insertion_point(class_scope:Ciot.Msg)
  })
_sym_db.RegisterMessage(Msg)


# @@protoc_insertion_point(module_scope)
