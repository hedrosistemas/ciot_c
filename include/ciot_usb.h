/**
 * @file ciot_usb.h
 * @ingroup hardware_interfaces
 * @brief Header file for CIOT USB module.
 * @version 0.1
 * @date 2023-10-17
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_USB__H__
#define __CIOT_USB__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "types/ciot_usb_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

/**
 * @brief Handle type for CIOT USB module.
 */
typedef struct ciot_usb *ciot_usb_t;

/**
 * @brief Event ID enumeration for CIOT USB module.
 */
typedef enum ciot_usb_event_id
{
    CIOT_USB_EVENT_DRV_SOF = CIOT_IFACE_EVENT_CUSTOM,     /*!< USB driver start of frame event */
    CIOT_USB_EVENT_DRV_RESET,                             /*!< USB driver reset event */
    CIOT_USB_EVENT_DRV_SUSPEND,                           /*!< USB driver suspend event */
    CIOT_USB_EVENT_DRV_RESUME,                            /*!< USB driver resume event */
    CIOT_USB_EVENT_DRV_WUREQ,                             /*!< USB driver wake-up request event */
    CIOT_USB_EVENT_DRV_SETUP,                             /*!< USB driver setup event */
    CIOT_USB_EVENT_DRV_EPTRANSFER,                        /*!< USB driver endpoint transfer event */
    CIOT_USB_EVENT_FIRST_POWER,                           /*!< First power event */
    CIOT_USB_EVENT_POWER_DETECTED,                        /*!< Power detected event */
    CIOT_USB_EVENT_POWER_REMOVED,                         /*!< Power removed event */
    CIOT_USB_EVENT_POWER_READY,                           /*!< Power ready event */
    CIOT_USB_EVENT_FIRST_APP,                             /*!< First application event */
    CIOT_USB_EVENT_INST_APPEND,                           /*!< Instance append event */
    CIOT_USB_EVENT_INST_REMOVE,                           /*!< Instance remove event */
    CIOT_USB_EVENT_STARTED,                               /*!< USB started event */
    CIOT_USB_EVENT_STOPPED,                               /*!< USB stopped event */
    CIOT_USB_EVENT_STATE_CHANGED,                         /*!< State changed event */
    CIOT_USB_EVENT_FIRST_INTERNAL,                        /*!< First internal event */
    CIOT_USB_EVENT_HFCLK_READY,                           /*!< High frequency clock ready event */
    CIOT_USB_EVENT_START_REQ,                             /*!< Start request event */
    CIOT_USB_EVENT_STOP_REQ,                              /*!< Stop request event */
    CIOT_USB_EVENT_SUSPEND_REQ,                           /*!< Suspend request event */
    CIOT_USB_EVENT_WAKEUP_REQ,                            /*!< Wake-up request event */
    CIOT_USB_EVENT_SETUP_SETADDRESS,                      /*!< Setup set address event */
    CIOT_USB_EVENT_DATA,                                  /*!< USB data event */
} ciot_usb_event_id_t;

/**
 * @brief Status message structure for CIOT USB module.
 */
typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;   /*!< Message header */
    ciot_usb_status_t status;   /*!< Status information */
} ciot_usb_status_msg_t;

/**
 * @brief Create a new instance of CIOT USB module.
 *
 * @param handle Unused parameter (can be NULL).
 * @return Pointer to the new CIOT USB instance.
 */
ciot_usb_t ciot_usb_new(void *handle);

/**
 * @brief Start the CIOT USB module with the given configuration.
 *
 * @param self Pointer to the CIOT USB instance.
 * @param cfg Configuration for the USB module.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_usb_start(ciot_usb_t self, ciot_usb_cfg_t *cfg);

/**
 * @brief Stop the CIOT USB module.
 *
 * @param self Pointer to the CIOT USB instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_usb_stop(ciot_usb_t self);

/**
 * @brief Process a request in the CIOT USB module.
 *
 * @param self Pointer to the CIOT USB instance.
 * @param req Pointer to the USB request structure.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_usb_process_req(ciot_usb_t self, ciot_usb_req_t *req);

/**
 * @brief Send data through the CIOT USB module.
 *
 * @param self Pointer to the CIOT USB instance.
 * @param data Pointer to the data buffer.
 * @param size Size of the data buffer.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_usb_send_data(ciot_usb_t self, uint8_t *data, int size);

/**
 * @brief Send bytes through the CIOT USB interface.
 *
 * @param iface Pointer to the CIOT interface instance.
 * @param bytes Pointer to the byte buffer to send.
 * @param size Size of the byte buffer.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_usb_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size);

/**
 * @brief Set bridge mode for the CIOT USB module.
 *
 * @param self Pointer to the CIOT USB instance.
 * @param mode Bridge mode flag (true for enabled, false for disabled).
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_usb_set_bridge_mode(ciot_usb_t self, bool mode);

/**
 * @brief Task function for the CIOT USB module.
 *
 * @param self Pointer to the CIOT USB instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_usb_task(ciot_usb_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_USB__H__
