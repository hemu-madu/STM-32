#include "stm32l476xx.h"

void UART2_Init(void);
void UART2_Transmit(char c);
void UART2_SendString(char *str);

int main(void)
{
    UART2_Init();

    while (1)
    {
        UART2_SendString("Hello, from UART Bare-Metal!\r\n");

        for(int i=0; i<1000000; i++);   // delay
    }
}

void UART2_Init(void)
{
    // 1. Enable GPIOA clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    // 2. Set PA2, PA3 to Alternate Function Mode
    GPIOA->MODER &= ~(3<<(2*2));
    GPIOA->MODER |= (2<<(2*2));   // AF mode for PA2

    GPIOA->MODER &= ~(3<<(3*2));
    GPIOA->MODER |= (2<<(3*2));   // AF mode for PA3

    // 3. Select AF7 (USART2)
    GPIOA->AFR[0] |= (7<<(4*2));  // PA2 AF7
    GPIOA->AFR[0] |= (7<<(4*3));  // PA3 AF7

    // 4. Enable USART2 clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

    // 5. Set Baud Rate (9600)
    USART2->BRR = 0x1A1;  // For 16 MHz clock

    // 6. Enable Transmitter & USART
    USART2->CR1 |= USART_CR1_TE;
    USART2->CR1 |= USART_CR1_UE;
}

void UART2_Transmit(char c)
{
    while(!(USART2->ISR & USART_ISR_TXE));
    USART2->TDR = c;
}

void UART2_SendString(char *str)
{
    while(*str)
    {
        UART2_Transmit(*str++);
    }
}
