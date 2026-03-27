#ifndef UART_H
#define UART_H

#include "stm32l476xx.h"
#include <stdint.h>

/* UART Configuration Structure */
typedef struct
{
    USART_TypeDef *Instance;
    uint32_t BaudRate;
} UART_Handle_t;

/* Function Prototypes */
void UART_Init(UART_Handle_t *huart);
void UART_WriteChar(UART_Handle_t *huart, char ch);
void UART_WriteString(UART_Handle_t *huart, char *str);
char UART_ReadChar(UART_Handle_t *huart);

#endif
