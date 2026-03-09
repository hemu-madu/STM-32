#include "uart.h"

void UART_Init(UART_Handle_t *huart)
{
    /* Enable GPIOA Clock */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    /* Enable USART2 Clock (for now fixed) */
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

    /* PA2 -> AF mode */
    GPIOA->MODER &= ~(3 << (2*2));
    GPIOA->MODER |=  (2 << (2*2));

    /* AF7 */
    GPIOA->AFR[0] &= ~(0xF << (4*2));
    GPIOA->AFR[0] |=  (7 << (4*2));

    /* Baudrate */
    huart->Instance->BRR = SystemCoreClock / huart->BaudRate;

    /* Enable TX & RX */
    huart->Instance->CR1 |= USART_CR1_TE | USART_CR1_RE;

    /* Enable UART */
    huart->Instance->CR1 |= USART_CR1_UE;
}

void UART_WriteChar(UART_Handle_t *huart, char ch)
{
    while(!(huart->Instance->ISR & USART_ISR_TXE));
    huart->Instance->TDR = ch;
}

void UART_WriteString(UART_Handle_t *huart, char *str)
{
    while(*str)
    {
        UART_WriteChar(huart, *str++);
    }
}

char UART_ReadChar(UART_Handle_t *huart)
{
    while(!(huart->Instance->ISR & USART_ISR_RXNE));
    return huart->Instance->RDR;
}
