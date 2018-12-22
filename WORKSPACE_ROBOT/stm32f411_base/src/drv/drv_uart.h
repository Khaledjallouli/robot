/*
 * drv_uart.h
 */

#ifndef SRC_DRV_DRV_UART_H_
#define SRC_DRV_DRV_UART_H_

#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>



void uart2_Init(void);
void uart6_Init(void);

void term_printf(const char* fmt, ...);
void term_printf_stlink(const char* fmt, ...);
void term_printf_zigbee(const char* fmt, ...);

void num2str(char *s, unsigned int number, unsigned int base, unsigned int size, int sp);
unsigned int str2num(char *s, unsigned base);

UART_HandleTypeDef Uart2Handle;
UART_HandleTypeDef Uart6Handle;


#endif /* SRC_DRV_DRV_UART_H_ */
