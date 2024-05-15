/**
 * @file ciot_mqttc.h
 * @ingroup software_interfaces
 * @brief Header file for CIOT MQTT client functionality.
 * @version 0.1
 * @date 2023-10-09
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_MQTT__H__
#define __CIOT_MQTT__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_mqttc_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Structure representing a CIOT MQTT client instance.
 */
typedef struct ciot_mqttc *ciot_mqttc_t;

/**
 * @brief Enumeration for CIOT MQTT client event IDs.
 */
typedef enum ciot_mqttc_event_id
{
    CIOT_MQTT_EVENT_CONNECTING = CIOT_IFACE_EVENT_CUSTOM, /**< MQTT client connecting event ID. */
    CIOT_MQTT_EVENT_SUBSCRIBED, /**< MQTT client subscribed event ID. */
    CIOT_MQTT_EVENT_UNSUBSCRIBED, /**< MQTT client unsubscribed event ID. */
} ciot_mqttc_event_id_t;

/**
 * @brief Structure representing a CIOT MQTT client status message.
 */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header; /**< Header information. */
    ciot_mqttc_status_t status; /**< MQTT client status. */
} ciot_mqttc_status_msg_t;

/**
 * @brief Creates a new CIOT MQTT client instance.
 * @param handle A handle for the MQTT client.
 * @return A pointer to the new MQTT client instance.
 */
ciot_mqttc_t ciot_mqttc_new(void *handle);

/**
 * @brief Starts the CIOT MQTT client.
 * @param self Pointer to the MQTT client instance.
 * @param cfg Pointer to the MQTT client configuration.
 * @return An error code indicating the status of the operation.
 */
ciot_err_t ciot_mqttc_start(ciot_mqttc_t self, ciot_mqttc_cfg_t *cfg);

/**
 * @brief Stops the CIOT MQTT client.
 * @param self Pointer to the MQTT client instance.
 * @return An error code indicating the status of the operation.
 */
ciot_err_t ciot_mqttc_stop(ciot_mqttc_t self);

/**
 * @brief Processes MQTT client requests.
 * @param self Pointer to the MQTT client instance.
 * @param req Pointer to the MQTT client request.
 * @return An error code indicating the status of the operation.
 */
ciot_err_t ciot_mqttc_process_req(ciot_mqttc_t self, ciot_mqttc_req_t *req);

/**
 * @brief Sends data using the MQTT client.
 * @param self Pointer to the MQTT client instance.
 * @param data Pointer to the data to be sent.
 * @param size Size of the data to be sent.
 * @return An error code indicating the status of the operation.
 */
ciot_err_t ciot_mqttc_send_data(ciot_mqttc_t self, uint8_t *data, int size);

/**
 * @brief Publishes a message using the MQTT client.
 * @param self Pointer to the MQTT client instance.
 * @param topic MQTT topic to publish to.
 * @param data Pointer to the data to be published.
 * @param size Size of the data to be published.
 * @param qos Quality of Service level for the message.
 * @return An error code indicating the status of the operation.
 */
ciot_err_t ciot_mqttc_publish(ciot_mqttc_t self, char *topic, uint8_t *data, int size, uint8_t qos);

/**
 * @brief Subscribes to an MQTT topic using the MQTT client.
 * @param self Pointer to the MQTT client instance.
 * @param topic MQTT topic to subscribe to.
 * @param qos Quality of Service level for the subscription.
 * @return An error code indicating the status of the operation.
 */
ciot_err_t ciot_mqttc_subscribe(ciot_mqttc_t self, char *topic, uint8_t qos);

/**
 * @brief Resets the data rate for the MQTT client.
 * @param self Pointer to the MQTT client instance.
 * @return An error code indicating the status of the operation.
 */
ciot_err_t ciot_mqttc_reset_data_rate(ciot_mqttc_t self);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_MQTT__H__
