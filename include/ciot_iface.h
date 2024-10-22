/**
 * @file ciot_iface.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_IFACE__H__
#define __CIOT_IFACE__H__

#include <stdbool.h>
#include "ciot/proto/v1/msg.pb-c.h"
#include "ciot_serializer.h"
#include "ciot_msg_types.h"
#include "ciot_err.h"

#define CIOT_CONFIG_IFACE_EVENT_DATA_SIZE 512

typedef Ciot__IfaceInfo ciot_iface_info_t;
typedef Ciot__IfaceType ciot_iface_type_t;

typedef enum ciot_iface_req_state {
    CIOT_IFACE_REQ_STATE_IDLE,
    CIOT_IFACE_REQ_STATE_SENDED,
    CIOT_IFACE_REQ_STATE_RECEIVED,
} ciot_iface_req_state_t;

typedef enum ciot_iface_event_type {
    CIOT_IFACE_EVENT_UNKNOWN,
    CIOT_IFACE_EVENT_DATA,
    CIOT_IFACE_EVENT_STARTED,
    CIOT_IFACE_EVENT_STOPPED,
    CIOT_IFACE_EVENT_ERROR,
    CIOT_IFACE_EVENT_REQUEST,
    CIOT_IFACE_EVENT_DONE,
    CIOT_IFACE_EVENT_INTERNAL,
    CIOT_IFACE_EVENT_CUSTOM,
} ciot_iface_event_type_t;

typedef enum ciot_iface_decoder_state
{
    CIOT_IFACE_DECODER_STATE_ERROR=-1,
    CIOT_IFACE_DECODER_STATE_IDLE,
    CIOT_IFACE_DECODER_STATE_DECODING,
    CIOT_IFACE_DECODER_STATE_DONE,
} ciot_iface_decoder_state_t;

typedef struct ciot_iface_event {
    ciot_iface_event_type_t type;
    ciot_msg_t *msg;
    uint8_t *data;
    uint16_t size;
} ciot_iface_event_t;

typedef struct ciot_iface_req_status {
    uint8_t id;
    ciot_iface_req_state_t state;
    ciot_msg_type_t type;
    ciot_iface_info_t iface;
} ciot_iface_req_status_t;

typedef struct ciot_iface ciot_iface_t;
typedef ciot_err_t (ciot_iface_process_req_fn)(ciot_iface_t *self, ciot_msg_t *req);
typedef ciot_err_t (ciot_iface_send_data_fn)(ciot_iface_t *self, uint8_t *data, int size);
typedef ciot_err_t (ciot_iface_get_data_fn)(ciot_iface_t *self, ciot_msg_t *req);
typedef ciot_err_t (ciot_iface_event_handler_fn)(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);
typedef ciot_err_t (ciot_iface_decoder_decode_fn)(ciot_iface_t *iface, uint8_t byte);
typedef struct ciot_iface_decoder *ciot_iface_decoder_t;

struct ciot_iface_decoder {
    ciot_iface_decoder_decode_fn *decode;
    ciot_iface_send_data_fn *send;
    ciot_iface_decoder_state_t state;
    ciot_iface_event_type_t event_type;
};

struct ciot_iface {
    void *ptr;
    ciot_iface_process_req_fn *process_req;
    ciot_iface_send_data_fn *send_data;
    ciot_iface_get_data_fn *get_data;
    ciot_iface_event_handler_fn *event_handler;
    void *event_args;
    // TODO: check if it's possible to have a singleton data instance for all ifaces.
    ciot_msg_data_t data;
    ciot_iface_info_t info;
    ciot_iface_req_status_t req_status;
    ciot_serializer_t serializer;
    ciot_iface_decoder_t decoder;
};

ciot_err_t ciot_iface_init(ciot_iface_t *self);
ciot_err_t ciot_iface_send_msg(ciot_iface_t *self, ciot_msg_t *msg);
ciot_err_t ciot_iface_send_rsp(ciot_iface_t *self, ciot_msg_t *rsp);
ciot_err_t ciot_iface_send_req(ciot_iface_t *self, ciot_msg_t *req);
ciot_err_t ciot_iface_send_error(ciot_iface_t *self, ciot_iface_type_t iface_type, uint16_t iface_id, ciot_msg_t *msg, ciot_err_t err);
ciot_err_t ciot_iface_send_event(ciot_iface_t *self, ciot_iface_event_t *event);
ciot_err_t ciot_iface_send_event_type(ciot_iface_t *self, ciot_iface_event_type_t event_type);
ciot_err_t ciot_iface_process_msg(ciot_iface_t *self, ciot_msg_t *msg, ciot_iface_t *sender);
ciot_err_t ciot_iface_process_data(ciot_iface_t *self, uint8_t *data, int size);
ciot_err_t ciot_iface_register_req(ciot_iface_t *self, ciot_iface_info_t *iface, ciot_msg_t *msg, ciot_iface_req_state_t state);
ciot_err_t ciot_iface_set_event_handler(ciot_iface_t *self, ciot_iface_event_handler_fn event_handler, void *event_args);
ciot_err_t ciot_iface_set_serializer(ciot_iface_t *self, ciot_serializer_t serializer);
ciot_err_t ciot_iface_set_decoder(ciot_iface_t *self, ciot_iface_decoder_t decoder);
ciot_err_t ciot_iface_get_msg_id(void);

const char* ciot_iface_to_str(ciot_iface_t *iface);
const char* ciot_iface_type_to_str(ciot_iface_type_t iface_type);
const char *ciot_iface_event_to_str(ciot_iface_event_t *event);

bool ciot_iface_is_equal(ciot_iface_info_t *iface, ciot_iface_info_t *other);
bool ciot_iface_event_is_ack(ciot_iface_event_type_t event_type);

#endif  //!__CIOT_IFACE__H__
