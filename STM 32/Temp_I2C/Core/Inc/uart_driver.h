#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "stm32f411xe.h"

void UART2_Init(void);
void UART2_SendChar(char c);
void UART2_SendString(const char *str);

#endif
