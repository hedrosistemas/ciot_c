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

#include "ciot_tcp_data.h"
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

ciot_eth_t ciot_eth_new(void *handle);
ciot_err_t ciot_eth_start(ciot_eth_t this, ciot_tcp_cfg_t *cfg);
ciot_err_t ciot_eth_stop(ciot_eth_t this);
ciot_err_t ciot_eth_process_req(ciot_eth_t this, ciot_tcp_req_t *req);
ciot_err_t ciot_eth_send_data(ciot_eth_t this, uint8_t *data, int size);

#endif  //!__CIOT_ETH__H__