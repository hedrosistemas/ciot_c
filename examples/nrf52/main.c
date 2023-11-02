/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot.h"
#include "ciot_uart.h"
#include "ciot_usb.h"

ciot_uart_t uart;
ciot_usb_t usb;

int main()
{
    uart = ciot_uart_new(NULL);
    usb = ciot_usb_new(NULL);
    return 0;
}