/**
 * @file ciot_cli.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_CLI__H__
#define __CIOT_CLI__H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ciot.h"

#define ARGP(n, value, func) if(argc > n && (strcmp(argv[n], value) == 0)) func(argc, argv)

void ciot_cli_run_cmd();

#endif  //!__ciot_CLI__H__