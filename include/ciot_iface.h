/**
 * @file ciot_iface.h
 * @ingroup core
 * @brief Header file for the CIOT interface.
 * @version 0.1
 * @date 2023-10-09
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_IFACE__H__
#define __CIOT_IFACE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "ciot_err.h"
#include "types/ciot_msg_types.h"
#include "ciot_serializer.h"

/**
 * @brief Enumeration for the status of interface requests.
 */
typedef enum ciot_iface_req_status {
    CIOT_IFACE_REQ_STATUS_IDLE, /**< Request status: Idle. */
    CIOT_IFACE_REQ_STATUS_SENDED, /**< Request status: Sent. */
    CIOT_IFACE_REQ_STATUS_RECEIVED, /**< Request status: Received. */
} ciot_iface_req_status_t;

/**
 * @brief Enumeration for CIOT interface event types.
 */
typedef enum ciot_iface_event_type {
    CIOT_IFACE_EVENT_INTERNAL = -1, /**< Internal event type. */
    CIOT_IFACE_EVENT_UNKNOWN, /**< Unknown event type. */
    CIOT_IFACE_EVENT_STARTED, /**< Interface started event. */
    CIOT_IFACE_EVENT_STOPPED, /**< Interface stopped event. */
    CIOT_IFACE_EVENT_ERROR, /**< Interface error event. */
    CIOT_IFACE_EVENT_REQUEST, /**< Interface request event. */
    CIOT_IFACE_EVENT_DATA, /**< Interface data event. */
    CIOT_IFACE_EVENT_DONE, /**< Interface done event. */
    CIOT_IFACE_EVENT_CUSTOM, /**< Custom interface event. */
} ciot_iface_event_type_t;

/**
 * @brief Union for CIOT interface event data.
 */
typedef union __attribute__((packed)) {
    ciot_msg_t msg; /**< CIOT message. */
    uint8_t payload[sizeof(ciot_msg_t)]; /**< Payload data. */
} ciot_iface_event_data_u;

/**
 * @brief Structure representing an interface event.
 */
typedef struct __attribute__((packed)) {
    ciot_iface_event_type_t type; /**< Event type. */
    ciot_iface_event_data_u *data; /**< Event data. */
    uint16_t size; /**< Size of the event data. */
} ciot_iface_event_t;

/**
 * @brief Function pointer for starting an interface.
 */
typedef ciot_err_t (ciot_iface_start_fn)(void *iface, ciot_msg_data_u *cfg);

/**
 * @brief Function pointer for stopping an interface.
 */
typedef ciot_err_t (ciot_iface_stop_fn)(void *iface);

/**
 * @brief Function pointer for processing a request on an interface.
 */
typedef ciot_err_t (ciot_iface_process_req_fn)(void *iface, ciot_msg_data_u *req);

/**
 * @brief Function pointer for sending data on an interface.
 */
typedef ciot_err_t (ciot_iface_send_data_fn)(void *iface, void *data, int size);

/**
 * @brief Structure representing base data for an interface.
 */
typedef struct ciot_iface_base_data {
    void *ptr; /**< Pointer to data. */
    uint16_t size; /**< Size of data. */
} ciot_iface_base_data_t;

/**
 * @brief Structure representing request information for an interface.
 */
typedef struct ciot_iface_req_info {
    ciot_iface_req_status_t status; /**< Request status. */
    uint8_t id; /**< Request ID. */
    ciot_msg_type_t type; /**< Message type. */
    ciot_msg_iface_info_t iface; /**< Interface information. */
    uint16_t response_size; /**< Size of response. */
} ciot_iface_req_info_t;

/**
 * @brief Structure representing the base of an interface.
 */
typedef struct ciot_iface_base {
    void *ptr; /**< Pointer to interface data. */
    ciot_iface_start_fn *start; /**< Function pointer for starting the interface. */
    ciot_iface_stop_fn *stop; /**< Function pointer for stopping the interface. */
    ciot_iface_process_req_fn *process_req; /**< Function pointer for processing a request. */
    ciot_iface_send_data_fn *send_data; /**< Function pointer for sending data. */
    ciot_iface_base_data_t cfg; /**< Configuration data. */
    ciot_iface_base_data_t status; /**< Status data. */
    ciot_iface_req_info_t req; /**< Request information. */
} ciot_iface_base_t;

/**
 * @brief Structure representing a CIOT interface.
 */
typedef struct ciot_iface ciot_iface_t;

/**
 * @brief Function pointer for handling interface events.
 */
typedef ciot_err_t (ciot_iface_event_handler_t)(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);

/**
 * @brief Structure representing a CIOT interface.
 */
struct ciot_iface {
    ciot_iface_base_t base; /**< Base of the interface. */
    ciot_msg_iface_info_t info; /**< Interface information. */
    ciot_iface_event_handler_t *event_handler; /**< Event handler function pointer. */
    ciot_serializer_t serializer; /**< Serializer for the interface. */
    void *event_args; /**< Event arguments. */
};

/**
 * @brief Starts the CIOT interface.
 * @param self The CIOT interface instance.
 * @param cfg The configuration data.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_start(ciot_iface_t *self, ciot_msg_data_u *cfg);

/**
 * @brief Stops the CIOT interface.
 * @param self The CIOT interface instance.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_stop(ciot_iface_t *self);

/**
 * @brief Gets the configuration of the CIOT interface.
 * @param self The CIOT interface instance.
 * @param cfg The configuration data.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_get_cfg(ciot_iface_t *self, ciot_msg_data_u *cfg);

/**
 * @brief Gets the status of the CIOT interface.
 * @param self The CIOT interface instance.
 * @param status The status data.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_get_status(ciot_iface_t *self, void *status);

/**
 * @brief Gets the information of the CIOT interface.
 * @param iface The CIOT interface.
 * @param info The information data.
 * @param size The size of the information data.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_get_info(ciot_iface_t *iface, void *info, int size);

/**
 * @brief Processes a request on the CIOT interface.
 * @param self The CIOT interface instance.
 * @param req The request data.
 * @param sender The sender of the request.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_process_req(ciot_iface_t *self, ciot_msg_data_u *req, void *sender);

/**
 * @brief Processes a message on the CIOT interface.
 * @param self The CIOT interface instance.
 * @param msg The message data.
 * @param sender The sender of the message.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_process_msg(ciot_iface_t *self, ciot_msg_t *msg, void *sender);

/**
 * @brief Sends data on the CIOT interface.
 * @param self The CIOT interface instance.
 * @param data The data to be sent.
 * @param size The size of the data.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_send_data(ciot_iface_t *self, void *data, int size);

/**
 * @brief Sends a message on the CIOT interface.
 * @param self The CIOT interface instance.
 * @param msg The message to be sent.
 * @param size The size of the message.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_send_msg(ciot_iface_t *self, ciot_msg_t *msg, int size);

/**
 * @brief Sends a request on the CIOT interface.
 * @param self The CIOT interface instance.
 * @param req The request to be sent.
 * @param size The size of the request.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_send_req(ciot_iface_t *self, ciot_msg_t *req, int size);

/**
 * @brief Sends a response on the CIOT interface.
 * @param self The CIOT interface instance.
 * @param rsp The response to be sent.
 * @param size The size of the response.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_send_rsp(ciot_iface_t *self, ciot_msg_t *rsp, int size);

/**
 * @brief Registers an event handler for the CIOT interface.
 * @param self The CIOT interface instance.
 * @param event_handler The event handler function pointer.
 * @param event_args The event arguments.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_register_event(ciot_iface_t *self, ciot_iface_event_handler_t event_handler, void *event_args);

/**
 * @brief Resets a request on the CIOT interface.
 * @param self The CIOT interface instance.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_reset_request(ciot_iface_t *self);

/**
 * @brief Registers a request on the CIOT interface.
 * @param self The CIOT interface instance.
 * @param iface The interface information.
 * @param msg The request message.
 * @param status The request status.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_register_request(ciot_iface_t *self, ciot_msg_iface_info_t *iface, ciot_msg_t *msg, ciot_iface_req_status_t status);

/**
 * @brief Sets the serializer for the CIOT interface.
 * @param self The CIOT interface instance.
 * @param serializer The serializer to set.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_iface_set_serializer(ciot_iface_t *self, ciot_serializer_t serializer);

/**
 * @brief Gets the message ID for the CIOT interface.
 * @return The message ID.
 */
uint8_t ciot_iface_get_msg_id(void);

/**
 * @brief Converts a CIOT interface instance to a string representation.
 * @param iface The CIOT interface instance.
 * @return A string representation of the CIOT interface.
 */
const char *ciot_iface_to_str(ciot_iface_t *iface);

/**
 * @brief Converts a CIOT interface type to a string representation.
 * @param iface_type The CIOT interface type.
 * @return A string representation of the CIOT interface type.
 */
const char *ciot_iface_type_to_str(ciot_msg_iface_type_t iface_type);

/**
 * @brief Converts a CIOT interface event to a string representation.
 * @param event The CIOT interface event.
 * @return A string representation of the CIOT interface event.
 */
const char *ciot_iface_event_to_str(ciot_iface_event_t *event);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_IFACE__H__
