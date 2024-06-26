/**
 * @file ciot_iface.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_IFACE__H__
#define __CIOT_IFACE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "ciot_err.h"
#include "ciot_msg_types.h"

typedef enum ciot_iface_req_status
{
    CIOT_IFACE_REQ_STATUS_IDLE,
    CIOT_IFACE_REQ_STATUS_SENDED,
    CIOT_IFACE_REQ_STATUS_RECEIVED,
} ciot_iface_req_status_t;

typedef enum ciot_iface_event_id
{
    CIOT_IFACE_EVENT_UNKNOWN,
    CIOT_IFACE_EVENT_STARTED,
    CIOT_IFACE_EVENT_STOPPED,
    CIOT_IFACE_EVENT_ERROR,
    CIOT_IFACE_EVENT_REQUEST,
    CIOT_IFACE_EVENT_DATA,
    CIOT_IFACE_EVENT_DONE,
    CIOT_IFACE_EVENT_CUSTOM,
} ciot_iface_event_id_t;

typedef union __attribute__((packed))
{
    ciot_msg_t msg;
    uint8_t payload[sizeof(ciot_msg_t)];
} ciot_iface_event_data_u;

typedef struct __attribute__((packed))
{
    ciot_iface_event_id_t id;
    ciot_iface_event_data_u *data;
    uint16_t size;
} ciot_iface_event_t;

typedef ciot_err_t (ciot_iface_start_fn)(void *iface, ciot_msg_data_u *cfg);
typedef ciot_err_t (ciot_iface_stop_fn)(void *iface);
typedef ciot_err_t (ciot_iface_process_req_fn)(void *iface, ciot_msg_data_u *req);
typedef ciot_err_t (ciot_iface_send_data_fn)(void *iface, void *data, int size);

typedef struct ciot_iface_base_data
{
    void *ptr;
    uint16_t size;
} ciot_iface_base_data_t;

typedef struct ciot_iface_req_info
{
    ciot_iface_req_status_t status;
    uint8_t id;
    ciot_msg_type_t type;
    ciot_msg_iface_info_t iface;
} ciot_iface_req_info_t;

typedef struct ciot_iface_base
{
    void *ptr;
    ciot_iface_start_fn *start;
    ciot_iface_stop_fn *stop;
    ciot_iface_process_req_fn *process_req;
    ciot_iface_send_data_fn *send_data;
    ciot_iface_base_data_t cfg;
    ciot_iface_base_data_t status;
    ciot_iface_req_info_t req;
} ciot_iface_base_t;

typedef struct ciot_iface ciot_iface_t;

typedef ciot_err_t (ciot_iface_event_handler_t)(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);

struct ciot_iface
{
    ciot_iface_base_t base;
    ciot_msg_iface_info_t info;
    ciot_iface_event_handler_t *event_handler;
    void *event_args;
};

ciot_err_t ciot_iface_start(ciot_iface_t *self, ciot_msg_data_u *cfg);
ciot_err_t ciot_iface_stop(ciot_iface_t *self);
ciot_err_t ciot_iface_get_cfg(ciot_iface_t *self, ciot_msg_data_u *cfg);
ciot_err_t ciot_iface_get_status(ciot_iface_t *self, void *status);
ciot_err_t ciot_iface_get_info(ciot_iface_t *iface, void *info, int size);
ciot_err_t ciot_iface_process_req(ciot_iface_t *self, ciot_msg_data_u *req, void *sender);
ciot_err_t ciot_iface_process_msg(ciot_iface_t *self, ciot_msg_t *msg, void *sender);
ciot_err_t ciot_iface_send_data(ciot_iface_t *self, void *data, int size);
ciot_err_t ciot_iface_send_msg(ciot_iface_t *self, ciot_msg_t *msg, int size);
ciot_err_t ciot_iface_send_req(ciot_iface_t *self, ciot_msg_t *msg, int size);
ciot_err_t ciot_iface_register_event(ciot_iface_t *self, ciot_iface_event_handler_t event_handler, void *event_args);
ciot_err_t coit_iface_reset_request(ciot_iface_t *self);

const char *ciot_iface_to_str(ciot_iface_t *iface);
const char *ciot_iface_type_to_str(ciot_msg_iface_type_t iface_type);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_IFACE__H__