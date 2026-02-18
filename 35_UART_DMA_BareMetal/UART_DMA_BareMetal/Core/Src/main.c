#include "stm32l4xx.h"

char message[] = "UART DMA BareMetal Working!\r\n";

void UART2_Init(void)
{
    // Enable clocks
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

    // PA2, PA3 alternate function
    GPIOA->MODER &= ~(0xF << 4);
    GPIOA->MODER |=  (0xA << 4);

    GPIOA->AFR[0] |= (7 << 8) | (7 << 12);

    // Baud rate (9600 @16MHz)
    USART2->BRR = 16000000 / 9600;

    // Enable DMA mode for TX
    USART2->CR3 |= USART_CR3_DMAT;

    // Enable USART + TX
    USART2->CR1 |= USART_CR1_TE | USART_CR1_UE;
}

void DMA_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

    DMA1_Channel7->CCR &= ~DMA_CCR_EN;

    DMA1_Channel7->CPAR = (uint32_t)&USART2->TDR;
    DMA1_Channel7->CMAR = (uint32_t)message;
    DMA1_Channel7->CNDTR = sizeof(message) - 1;

    DMA1_Channel7->CCR =
            DMA_CCR_MINC |       // memory increment
            DMA_CCR_DIR;         // memory to peripheral

    DMA1_Channel7->CCR |= DMA_CCR_EN;
}

int main(void)
{
    UART2_Init();
    DMA_Init();

    while (1)
    {
        // nothing needed
    }
}
