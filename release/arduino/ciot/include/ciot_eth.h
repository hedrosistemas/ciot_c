/**
 * @file ciot_eth.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_ETH__H__
#define __CIOT_ETH__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_tcp_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_eth *ciot_eth_t;

typedef enum ciot_eth_event_id
{
    CIOT_ETH_EVENT_START = CIOT_IFACE_EVENT_CUSTOM,
    CIOT_ETH_EVENT_STOP,
    CIOT_ETH_EVENT_CONNECTED,
    CIOT_ETH_EVENT_DISCONNECTED,
} ciot_eth_event_id_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_tcp_status_t status;
} ciot_eth_status_msg_t;

ciot_eth_t ciot_eth_new(void *handle);
ciot_err_t ciot_eth_start(ciot_eth_t self, ciot_tcp_cfg_t *cfg);
ciot_err_t ciot_eth_stop(ciot_eth_t self);
ciot_err_t ciot_eth_process_req(ciot_eth_t self, ciot_tcp_req_t *req);
ciot_err_t ciot_eth_send_data(ciot_eth_t self, uint8_t *data, int size);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_ETH__H__