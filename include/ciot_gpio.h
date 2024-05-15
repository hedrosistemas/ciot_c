/**
 * @file ciot_gpio.h
 * @ingroup hardware_interfaces
 * @brief Header file for CIOT GPIO interface.
 * @version 0.1
 * @date 2023-10-17
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_GPIO__H__
#define __CIOT_GPIO__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_gpio_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Structure representing the CIOT GPIO interface.
 */
typedef struct ciot_gpio *ciot_gpio_t;

/**
 * @brief Structure representing the CIOT GPIO status message.
 */
typedef struct __attribute__((packed)) {
    ciot_msg_header_t header; /**< Message header. */
    ciot_gpio_status_t status; /**< GPIO status. */
} ciot_gpio_status_msg_t;

/**
 * @brief Creates a new CIOT GPIO interface instance.
 * @param handle The handle for the GPIO interface.
 * @return A pointer to the new CIOT GPIO instance.
 */
ciot_gpio_t ciot_gpio_new(void *handle);

/**
 * @brief Starts the CIOT GPIO interface.
 * @param self The CIOT GPIO instance.
 * @param cfg The GPIO configuration.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_gpio_start(ciot_gpio_t self, ciot_gpio_cfg_t *cfg);

/**
 * @brief Stops the CIOT GPIO interface.
 * @param self The CIOT GPIO instance.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_gpio_stop(ciot_gpio_t self);

/**
 * @brief Processes a request for the CIOT GPIO interface.
 * @param self The CIOT GPIO instance.
 * @param req The GPIO request to be processed.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_gpio_process_req(ciot_gpio_t self, ciot_gpio_req_t *req);

/**
 * @brief Sends data over the CIOT GPIO interface.
 * @param self The CIOT GPIO instance.
 * @param data The data to be sent.
 * @param size The size of the data.
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_gpio_send_data(ciot_gpio_t self, uint8_t *data, int size);

/**
 * @brief Sets the state of a GPIO pin.
 * @param self The CIOT GPIO instance.
 * @param gpio The GPIO pin number.
 * @param state The state to set (CIOT_GPIO_STATE_HIGH or CIOT_GPIO_STATE_LOW).
 * @return An error code indicating the result of the operation.
 */
ciot_err_t ciot_gpio_set_state(ciot_gpio_t self, int gpio, ciot_gpio_state_t state);

/**
 * @brief Gets the state of a GPIO pin.
 * @param self The CIOT GPIO instance.
 * @param gpio The GPIO pin number.
 * @return The state of the GPIO pin (CIOT_GPIO_STATE_HIGH or CIOT_GPIO_STATE_LOW).
 */
ciot_gpio_state_t ciot_gpio_get_state(ciot_gpio_t self, int gpio);

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_GPIO__H__
