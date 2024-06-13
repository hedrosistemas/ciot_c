# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ciot/proto/v1/mqtt_client.proto
# Protobuf Python Version: 5.26.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1f\x63iot/proto/v1/mqtt_client.proto\x12\x04\x43iot\"\x91\x01\n\x0fMqttClientError\x12\x14\n\x0ctls_last_err\x18\x01 \x01(\x05\x12\x15\n\rtls_stack_err\x18\x02 \x01(\x05\x12\x1d\n\x15tls_cert_verify_flags\x18\x03 \x01(\x05\x12\x0c\n\x04type\x18\x04 \x01(\x05\x12\x0c\n\x04\x63ode\x18\x05 \x01(\x05\x12\x16\n\x0etransport_sock\x18\x06 \x01(\x05\"/\n\x13MqttClientTopicsCfg\x12\x0b\n\x03\x64\x32\x62\x18\x01 \x01(\t\x12\x0b\n\x03\x62\x32\x64\x18\x02 \x01(\t\"\xc3\x01\n\rMqttClientCfg\x12\x11\n\tclient_id\x18\x01 \x01(\t\x12\x0b\n\x03url\x18\x02 \x01(\t\x12\x0c\n\x04user\x18\x03 \x01(\t\x12\x10\n\x08password\x18\x04 \x01(\t\x12\x0c\n\x04port\x18\x05 \x01(\r\x12\x0b\n\x03qos\x18\x06 \x01(\r\x12,\n\ttransport\x18\x07 \x01(\x0e\x32\x19.Ciot.MqttClientTransport\x12)\n\x06topics\x18\x08 \x01(\x0b\x32\x19.Ciot.MqttClientTopicsCfg\"\x9c\x01\n\x10MqttClientStatus\x12$\n\x05state\x18\x01 \x01(\x0e\x32\x15.Ciot.MqttClientState\x12\x12\n\nconn_count\x18\x02 \x01(\r\x12\x11\n\tdata_rate\x18\x03 \x01(\r\x12\x15\n\rlast_msg_time\x18\x04 \x01(\x04\x12$\n\x05\x65rror\x18\x05 \x01(\x0b\x32\x15.Ciot.MqttClientError\"C\n\x14MqttClientReqPublish\x12\r\n\x05topic\x18\x01 \x01(\t\x12\x0f\n\x07message\x18\x02 \x01(\x0c\x12\x0b\n\x03qos\x18\x03 \x01(\x05\"4\n\x16MqttClientReqSubscribe\x12\r\n\x05topic\x18\x01 \x01(\t\x12\x0b\n\x03qos\x18\x02 \x01(\x05\"\x94\x01\n\rMqttClientReq\x12%\n\x04type\x18\x01 \x01(\x0e\x32\x17.Ciot.MqttClientReqType\x12+\n\x07publish\x18\x02 \x01(\x0b\x32\x1a.Ciot.MqttClientReqPublish\x12/\n\tsubscribe\x18\x03 \x01(\x0b\x32\x1c.Ciot.MqttClientReqSubscribe\"\x83\x01\n\x0eMqttClientData\x12#\n\x06\x63onfig\x18\x01 \x01(\x0b\x32\x13.Ciot.MqttClientCfg\x12&\n\x06status\x18\x02 \x01(\x0b\x32\x16.Ciot.MqttClientStatus\x12$\n\x07request\x18\x03 \x01(\x0b\x32\x13.Ciot.MqttClientReq*\xa0\x01\n\x0fMqttClientState\x12\x1b\n\x17MQTT_STATE_DISCONNECTED\x10\x00\x12\x19\n\x15MQTT_STATE_CONNECTING\x10\x01\x12\x1c\n\x18MQTT_STATE_DISCONNECTING\x10\x02\x12\x18\n\x14MQTT_STATE_CONNECTED\x10\x03\x12\x1d\n\x10MQTT_STATE_ERROR\x10\xff\xff\xff\xff\xff\xff\xff\xff\xff\x01*\xa4\x01\n\x13MqttClientTransport\x12\x1a\n\x16MQTT_TRANSPORT_UNKNOWN\x10\x00\x12\x1b\n\x17MQTT_TRANSPORT_OVER_TCP\x10\x01\x12\x1b\n\x17MQTT_TRANSPORT_OVER_SSL\x10\x02\x12\x1a\n\x16MQTT_TRANSPORT_OVER_WS\x10\x03\x12\x1b\n\x17MQTT_TRANSPORT_OVER_WSS\x10\x04*e\n\x11MqttClientReqType\x12\x18\n\x14MQTT_REQ_TYPE_UNKOWN\x10\x00\x12\x19\n\x15MQTT_REQ_TYPE_PUBLISH\x10\x01\x12\x1b\n\x17MQTT_REQ_TYPE_SUBSCRIBE\x10\x02\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ciot.proto.v1.mqtt_client_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_MQTTCLIENTSTATE']._serialized_start=1004
  _globals['_MQTTCLIENTSTATE']._serialized_end=1164
  _globals['_MQTTCLIENTTRANSPORT']._serialized_start=1167
  _globals['_MQTTCLIENTTRANSPORT']._serialized_end=1331
  _globals['_MQTTCLIENTREQTYPE']._serialized_start=1333
  _globals['_MQTTCLIENTREQTYPE']._serialized_end=1434
  _globals['_MQTTCLIENTERROR']._serialized_start=42
  _globals['_MQTTCLIENTERROR']._serialized_end=187
  _globals['_MQTTCLIENTTOPICSCFG']._serialized_start=189
  _globals['_MQTTCLIENTTOPICSCFG']._serialized_end=236
  _globals['_MQTTCLIENTCFG']._serialized_start=239
  _globals['_MQTTCLIENTCFG']._serialized_end=434
  _globals['_MQTTCLIENTSTATUS']._serialized_start=437
  _globals['_MQTTCLIENTSTATUS']._serialized_end=593
  _globals['_MQTTCLIENTREQPUBLISH']._serialized_start=595
  _globals['_MQTTCLIENTREQPUBLISH']._serialized_end=662
  _globals['_MQTTCLIENTREQSUBSCRIBE']._serialized_start=664
  _globals['_MQTTCLIENTREQSUBSCRIBE']._serialized_end=716
  _globals['_MQTTCLIENTREQ']._serialized_start=719
  _globals['_MQTTCLIENTREQ']._serialized_end=867
  _globals['_MQTTCLIENTDATA']._serialized_start=870
  _globals['_MQTTCLIENTDATA']._serialized_end=1001
# @@protoc_insertion_point(module_scope)