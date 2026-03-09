#include "stm32f411xe.h"

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIOA->MODER &= ~(0xF << (2 * 2));
    GPIOA->MODER |=  (0xA << (2 * 2));

    GPIOA->AFR[0] &= ~(0xFF << (4 * 2));
    GPIOA->AFR[0] |=  (0x77 << (4 * 2));

    USART2->BRR = 16000000 / 9600;
    USART2->CR1 |= USART_CR1_TE;
    USART2->CR1 |= USART_CR1_UE;

    while (1)
    {
        while (!(USART2->SR & USART_SR_TXE));
        USART2->DR = 'A';

        for (volatile int i = 0; i < 1000000; i++);
    }
}
