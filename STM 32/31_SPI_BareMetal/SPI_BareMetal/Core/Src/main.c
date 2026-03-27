#include "stm32l476xx.h"
#include <stdio.h>

void delay(volatile uint32_t t)
{
    while(t--);
}

/* ================= UART SECTION ================= */

void UART2_Init(void)
{
    /* Enable Clocks */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;     // GPIOA clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;  // USART2 clock

    /* PA2 -> TX , PA3 -> RX */
    GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
    GPIOA->MODER |= (2 << GPIO_MODER_MODE2_Pos) |
                    (2 << GPIO_MODER_MODE3_Pos);  // Alternate mode

    GPIOA->AFR[0] &= ~(0xFF << 8);
    GPIOA->AFR[0] |= (7 << 8) | (7 << 12);  // AF7 = USART2

    /* Baud Rate */
    USART2->BRR = SystemCoreClock / 9600;

    /* Enable TX and USART */
    USART2->CR1 |= USART_CR1_TE;
    USART2->CR1 |= USART_CR1_UE;
}

void UART2_SendChar(char c)
{
    while(!(USART2->ISR & USART_ISR_TXE));
    USART2->TDR = c;
}

void UART2_Print(char *str)
{
    while(*str)
    {
        UART2_SendChar(*str++);
    }
}

void UART2_PrintHex(uint8_t data)
{
    char buffer[6];
    sprintf(buffer,"0x%02X ",data);
    UART2_Print(buffer);
}

/* ================= SPI SECTION ================= */

void SPI1_Init(void)
{
    /* Enable Clocks */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    /* PA5=SCK, PA6=MISO, PA7=MOSI */
    GPIOA->MODER &= ~(GPIO_MODER_MODE5_Msk |
                      GPIO_MODER_MODE6_Msk |
                      GPIO_MODER_MODE7_Msk);

    GPIOA->MODER |= (2 << GPIO_MODER_MODE5_Pos) |
                    (2 << GPIO_MODER_MODE6_Pos) |
                    (2 << GPIO_MODER_MODE7_Pos);

    /* AF5 for SPI1 */
    GPIOA->AFR[0] &= ~(0xFFF << 20);
    GPIOA->AFR[0] |= (5 << 20) | (5 << 24) | (5 << 28);

    /* SPI Configuration */
    SPI1->CR1 = 0;
    SPI1->CR1 |= SPI_CR1_MSTR;       // Master mode
    SPI1->CR1 |= SPI_CR1_SSM;        // Software slave
    SPI1->CR1 |= SPI_CR1_SSI;        // Internal slave select
    SPI1->CR1 |= (3 << SPI_CR1_BR_Pos);  // Baud rate = fPCLK/16

    SPI1->CR1 |= SPI_CR1_SPE;        // Enable SPI
}

uint8_t SPI1_Transfer(uint8_t data)
{
    while(!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;

    while(!(SPI1->SR & SPI_SR_RXNE));
    return SPI1->DR;
}

/* ================= MAIN ================= */

int main(void)
{
    UART2_Init();
    SPI1_Init();

    UART2_Print("SPI BareMetal Test\r\n");

    while(1)
    {
        uint8_t tx = 0x55;
        uint8_t rx = SPI1_Transfer(tx);

        UART2_Print("TX: ");
        UART2_PrintHex(tx);

        UART2_Print(" RX: ");
        UART2_PrintHex(rx);

        UART2_Print("\r\n");

        delay(1000000);
    }
}
