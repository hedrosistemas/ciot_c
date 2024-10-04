/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ciot/proto/v1/gpio.proto */

#ifndef PROTOBUF_C_ciot_2fproto_2fv1_2fgpio_2eproto__INCLUDED
#define PROTOBUF_C_ciot_2fproto_2fv1_2fgpio_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Ciot__GpioCfg Ciot__GpioCfg;
typedef struct _Ciot__GpioStatus Ciot__GpioStatus;
typedef struct _Ciot__GpioStateInfo Ciot__GpioStateInfo;
typedef struct _Ciot__GpioReq Ciot__GpioReq;
typedef struct _Ciot__GpioData Ciot__GpioData;


/* --- enums --- */

/*
 * Enum representing the state of gpio
 */
typedef enum _Ciot__GpioState {
  /*
   * Gpio is low
   */
  CIOT__GPIO_STATE__GPIO_STATE_LOW = 0,
  /*
   * Gpio is high
   */
  CIOT__GPIO_STATE__GPIO_STATE_HIGH = 1,
  /*
   * Gpio is alternating it state once
   */
  CIOT__GPIO_STATE__GPIO_STATE_BLINK = 2,
  /*
   * Gpio alternated it state once
   */
  CIOT__GPIO_STATE__GPIO_STATE_BLINKED = 3,
  /*
   * Gpio is alternating it state
   */
  CIOT__GPIO_STATE__GPIO_STATE_BLINKING = 4,
  /*
   * Gpio is in error
   */
  CIOT__GPIO_STATE__GPIO_STATE_ERROR = 5
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__GPIO_STATE)
} Ciot__GpioState;
/*
 * Enum representing gpio requests
 */
typedef enum _Ciot__GpioReqType {
  /*
   * Unknown request
   */
  CIOT__GPIO_REQ_TYPE__GPIO_REQ_TYPE_UNKNOWN = 0,
  /*
   * Config request
   */
  CIOT__GPIO_REQ_TYPE__GPIO_REQ_TYPE_CONFIG = 1,
  /*
   * Set status request. Can be used to set all gpio states with a single message
   */
  CIOT__GPIO_REQ_TYPE__GPIO_REQ_TYPE_SET_STATUS = 2,
  /*
   * Set state request. Set the state of a single gpio
   */
  CIOT__GPIO_REQ_TYPE__GPIO_REQ_TYPE_SET_STATE = 3,
  /*
   * Get gpio status. Can be used to get all gpio states with a single message
   */
  CIOT__GPIO_REQ_TYPE__GPIO_REQ_TYPE_GET_STATUS = 4,
  /*
   * Get gpio state. Can be used to get the state of a single gpio
   */
  CIOT__GPIO_REQ_TYPE__GPIO_REQ_TYPE_GET_STATE = 5
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__GPIO_REQ_TYPE)
} Ciot__GpioReqType;
/*
 * Enum representing gpio modes 
 */
typedef enum _Ciot__GpioMode {
  /*
   * Disable gpio
   */
  CIOT__GPIO_MODE__GPIO_MODE_DISABLED = 0,
  /*
   * Enable gpio input mode
   */
  CIOT__GPIO_MODE__GPIO_MODE_INPUT = 1,
  /*
   * Enable gpio output mode
   */
  CIOT__GPIO_MODE__GPIO_MODE_OUTPUT = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__GPIO_MODE)
} Ciot__GpioMode;
/*
 * Enum representing gpio internal pullup/pulldown modes
 */
typedef enum _Ciot__GpioPull {
  /*
   * Disable gpio internal pullup/pulldown
   */
  CIOT__GPIO_PULL__GPIO_PULL_DISABLED = 0,
  /*
   * Enable gpio internal pullup
   */
  CIOT__GPIO_PULL__GPIO_PULL_UP = 1,
  /*
   * Enable gpio internal pulldown
   */
  CIOT__GPIO_PULL__GPIO_PULL_DOWN = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CIOT__GPIO_PULL)
} Ciot__GpioPull;

/* --- messages --- */

/*
 * Message representing gpio configuration
 */
struct  _Ciot__GpioCfg
{
  ProtobufCMessage base;
  /*
   * Gpio pin list
   */
  ProtobufCBinaryData pins;
  /*
   * Gpio pin modes list
   */
  ProtobufCBinaryData modes;
  /*
   * Gpio pull configurations list
   */
  ProtobufCBinaryData pull;
  /*
   * Interval between gpio blinks in miliseconds
   */
  uint32_t blink_interval;
};
#define CIOT__GPIO_CFG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__gpio_cfg__descriptor) \
    , {0,NULL}, {0,NULL}, {0,NULL}, 0 }


/*
 * Message used to read/set all gpio states
 */
struct  _Ciot__GpioStatus
{
  ProtobufCMessage base;
  /*
   * Gpio states list
   */
  ProtobufCBinaryData states;
};
#define CIOT__GPIO_STATUS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__gpio_status__descriptor) \
    , {0,NULL} }


/*
 * Message used to set/read signle gpio state info
 */
struct  _Ciot__GpioStateInfo
{
  ProtobufCMessage base;
  /*
   * Gpio num
   */
  uint32_t num;
  /*
   * Gpio state
   */
  Ciot__GpioState state;
};
#define CIOT__GPIO_STATE_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__gpio_state_info__descriptor) \
    , 0, CIOT__GPIO_STATE__GPIO_STATE_LOW }


/*
 * Message representing an gpio request
 */
struct  _Ciot__GpioReq
{
  ProtobufCMessage base;
  /*
   * Request type
   */
  Ciot__GpioReqType type;
  /*
   * Configuration request
   */
  Ciot__GpioCfg *config;
  /*
   * Set/read status request
   */
  Ciot__GpioStatus *status;
  /*
   * Set/read sate request
   */
  Ciot__GpioStateInfo *state;
};
#define CIOT__GPIO_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__gpio_req__descriptor) \
    , CIOT__GPIO_REQ_TYPE__GPIO_REQ_TYPE_UNKNOWN, NULL, NULL, NULL }


/*
 * Message representing gpio data
 */
struct  _Ciot__GpioData
{
  ProtobufCMessage base;
  /*
   * Configuration data
   */
  Ciot__GpioCfg *config;
  /*
   * Status data
   */
  Ciot__GpioStatus *status;
  /*
   * Request data
   */
  Ciot__GpioReq *request;
};
#define CIOT__GPIO_DATA__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ciot__gpio_data__descriptor) \
    , NULL, NULL, NULL }


/* Ciot__GpioCfg methods */
void   ciot__gpio_cfg__init
                     (Ciot__GpioCfg         *message);
size_t ciot__gpio_cfg__get_packed_size
                     (const Ciot__GpioCfg   *message);
size_t ciot__gpio_cfg__pack
                     (const Ciot__GpioCfg   *message,
                      uint8_t             *out);
size_t ciot__gpio_cfg__pack_to_buffer
                     (const Ciot__GpioCfg   *message,
                      ProtobufCBuffer     *buffer);
Ciot__GpioCfg *
       ciot__gpio_cfg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__gpio_cfg__free_unpacked
                     (Ciot__GpioCfg *message,
                      ProtobufCAllocator *allocator);
/* Ciot__GpioStatus methods */
void   ciot__gpio_status__init
                     (Ciot__GpioStatus         *message);
size_t ciot__gpio_status__get_packed_size
                     (const Ciot__GpioStatus   *message);
size_t ciot__gpio_status__pack
                     (const Ciot__GpioStatus   *message,
                      uint8_t             *out);
size_t ciot__gpio_status__pack_to_buffer
                     (const Ciot__GpioStatus   *message,
                      ProtobufCBuffer     *buffer);
Ciot__GpioStatus *
       ciot__gpio_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__gpio_status__free_unpacked
                     (Ciot__GpioStatus *message,
                      ProtobufCAllocator *allocator);
/* Ciot__GpioStateInfo methods */
void   ciot__gpio_state_info__init
                     (Ciot__GpioStateInfo         *message);
size_t ciot__gpio_state_info__get_packed_size
                     (const Ciot__GpioStateInfo   *message);
size_t ciot__gpio_state_info__pack
                     (const Ciot__GpioStateInfo   *message,
                      uint8_t             *out);
size_t ciot__gpio_state_info__pack_to_buffer
                     (const Ciot__GpioStateInfo   *message,
                      ProtobufCBuffer     *buffer);
Ciot__GpioStateInfo *
       ciot__gpio_state_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__gpio_state_info__free_unpacked
                     (Ciot__GpioStateInfo *message,
                      ProtobufCAllocator *allocator);
/* Ciot__GpioReq methods */
void   ciot__gpio_req__init
                     (Ciot__GpioReq         *message);
size_t ciot__gpio_req__get_packed_size
                     (const Ciot__GpioReq   *message);
size_t ciot__gpio_req__pack
                     (const Ciot__GpioReq   *message,
                      uint8_t             *out);
size_t ciot__gpio_req__pack_to_buffer
                     (const Ciot__GpioReq   *message,
                      ProtobufCBuffer     *buffer);
Ciot__GpioReq *
       ciot__gpio_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__gpio_req__free_unpacked
                     (Ciot__GpioReq *message,
                      ProtobufCAllocator *allocator);
/* Ciot__GpioData methods */
void   ciot__gpio_data__init
                     (Ciot__GpioData         *message);
size_t ciot__gpio_data__get_packed_size
                     (const Ciot__GpioData   *message);
size_t ciot__gpio_data__pack
                     (const Ciot__GpioData   *message,
                      uint8_t             *out);
size_t ciot__gpio_data__pack_to_buffer
                     (const Ciot__GpioData   *message,
                      ProtobufCBuffer     *buffer);
Ciot__GpioData *
       ciot__gpio_data__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ciot__gpio_data__free_unpacked
                     (Ciot__GpioData *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Ciot__GpioCfg_Closure)
                 (const Ciot__GpioCfg *message,
                  void *closure_data);
typedef void (*Ciot__GpioStatus_Closure)
                 (const Ciot__GpioStatus *message,
                  void *closure_data);
typedef void (*Ciot__GpioStateInfo_Closure)
                 (const Ciot__GpioStateInfo *message,
                  void *closure_data);
typedef void (*Ciot__GpioReq_Closure)
                 (const Ciot__GpioReq *message,
                  void *closure_data);
typedef void (*Ciot__GpioData_Closure)
                 (const Ciot__GpioData *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    ciot__gpio_state__descriptor;
extern const ProtobufCEnumDescriptor    ciot__gpio_req_type__descriptor;
extern const ProtobufCEnumDescriptor    ciot__gpio_mode__descriptor;
extern const ProtobufCEnumDescriptor    ciot__gpio_pull__descriptor;
extern const ProtobufCMessageDescriptor ciot__gpio_cfg__descriptor;
extern const ProtobufCMessageDescriptor ciot__gpio_status__descriptor;
extern const ProtobufCMessageDescriptor ciot__gpio_state_info__descriptor;
extern const ProtobufCMessageDescriptor ciot__gpio_req__descriptor;
extern const ProtobufCMessageDescriptor ciot__gpio_data__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_ciot_2fproto_2fv1_2fgpio_2eproto__INCLUDED */
