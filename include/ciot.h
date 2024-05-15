/**
 * @file ciot_n.h
 * @ingroup core
 * @brief Header file for the CIOT network module.
 * @version 0.1
 * @date 2023-10-10
 * @author Your Name
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT__H__
#define __CIOT__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"
#include "ciot_storage.h"
#include "ciot_bridge.h"

#define CIOT_IFACE_CFG_FILENAME "cfg%d.dat"

#ifdef CIOT_TARGET_MONGOOSE

extern struct mg_mgr mg; ///< Mongoose network manager.

#define CIOT_HANDLE &mg

#else

#define CIOT_HANDLE NULL

#endif

#ifdef CIOT_TARGET_NRF

#define app_main main

#endif

#ifdef  CIOT_TARGET_ARDUINO

#define app_main setup

#endif  //CIOT_TARGET_ARDUINO

typedef struct ciot *ciot_t; ///< CIOT network handle.

/**
 * @brief CIOT configuration structure
 * 
 */
typedef struct ciot_cfg
{
    ciot_iface_t **ifaces; ///< Array of CIOT interfaces.
    void **cfgs; ///< Array of configurations for the interfaces.
    uint8_t count; ///< Number of interfaces.
} ciot_cfg_t;

/**
 * @brief Create a new CIOT network instance.
 *
 * @return Pointer to the created CIOT network instance.
 */
ciot_t ciot_new(void);

/**
 * @brief Start the CIOT network module.
 *
 * @param self Pointer to the CIOT network instance.
 * @param cfg Pointer to the network configuration.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_start(ciot_t self, ciot_cfg_t *cfg);

/**
 * @brief Set the storage for CIOT network data.
 *
 * @param self Pointer to the CIOT network instance.
 * @param storage Pointer to the storage instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_set_storage(ciot_t self, ciot_storage_t storage);

/**
 * @brief Register an event handler for CIOT network events.
 *
 * @param self Pointer to the CIOT network instance.
 * @param event_handler Event handler function.
 * @param event_args Event handler arguments.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_register_event(ciot_t self, ciot_iface_event_handler_t event_handler, void *event_args);

/**
 * @brief Send a request via a proxy interface in CIOT network.
 *
 * @param self Pointer to the CIOT network instance.
 * @param iface Pointer to the network interface.
 * @param proxy_iface Pointer to the proxy interface.
 * @param req Pointer to the request message.
 * @param size Size of the request message.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_proxy_send_req(ciot_t self, ciot_iface_t *iface, ciot_msg_iface_info_t *proxy_iface, ciot_msg_t *req, int size);

/**
 * @brief Save the configuration of a specific interface in CIOT network.
 *
 * @param self Pointer to the CIOT network instance.
 * @param iface_id ID of the interface to save.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_save_iface_cfg(ciot_t self, uint8_t iface_id);

/**
 * @brief Delete the configuration of a specific interface in CIOT network.
 *
 * @param self Pointer to the CIOT network instance.
 * @param iface_id ID of the interface to delete.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_delete_iface_cfg(ciot_t self, uint8_t iface_id);

/**
 * @brief Perform the CIOT network task.
 *
 * @param self Pointer to the CIOT network instance.
 * @return Error code indicating success or failure.
 */
ciot_err_t ciot_task(ciot_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT__H__
