/**
 * @file ciot_tcp.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_tcp.h"

#if (CIOT_CONFIG_FEATURE_ETHERNET || CIOT_CONFIG_FEATURE_WIFI) && defined(CIOT_TARGET_ESP8266)

struct ciot_tcp
{
    ciot_iface_t iface;
    void *netif;
    ciot_tcp_type_t type;
};

ciot_err_t ciot_tcp_init(void)
{
    
}

ciot_tcp_t ciot_tcp_new(ciot_tcp_handle_t *handle)
{
    
}

ciot_err_t ciot_tcp_start(ciot_tcp_t self, ciot_tcp_cfg_t *cfg)
{
    
}

ciot_err_t ciot_tcp_stop(ciot_tcp_t self)
{
    
}

ciot_err_t ciot_tcp_process_req(ciot_tcp_t self, ciot_tcp_req_t *req)
{
    
}

ciot_err_t ciot_tcp_send_data(ciot_tcp_t self, uint8_t *data, int size)
{
    
}

ciot_err_t ciot_tcp_register_event(ciot_tcp_t tcp, ciot_iface_event_handler_t event_handler, void *event_args)
{
    
}

#endif