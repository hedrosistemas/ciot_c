/**
 * @file ciot_cli_conn.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_CLI_CONN__H__
#define __CIOT_CLI_CONN__H__

#include "ciot_iface.h"

#define CIOT_CLI_CONN_DAT_FILE "conn.dat"

ciot_err_t ciot_cli_conn_start();
ciot_err_t ciot_cli_conn_task();
int ciot_cli_conn(int argc, char const *argv[]);
ciot_err_t ciot_cli_conn_send_msg(ciot_msg_t *msg);
ciot_err_t ciot_cli_conn_send_req(ciot_msg_t *msg, ciot_iface_event_handler_fn *req_handler_fn);

#endif  //!__CIOT_CLI_CONN__H__