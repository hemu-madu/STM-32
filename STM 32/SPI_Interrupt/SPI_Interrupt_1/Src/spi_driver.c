#include "device_registers.h"
#include "spi_driver.h"
extern volatile uint32_t debug_step;

void SPI_Init(void)
{
    debug_step = 10;

    // 1️⃣ Enable GPIOA clock
    *((volatile uint32_t*)0x40023830) |= (1 << 0);
    debug_step = 11;

    // 2️⃣ Enable SPI1 clock
    *((volatile uint32_t*)0x40023844) |= (1 << 12);
    debug_step = 12;

    // 3️⃣ Configure Master mode
    SPI1->CR1 |= (1 << 2);   // MSTR
    debug_step = 13;

    // 4️⃣ Enable Software Slave Management
    SPI1->CR1 |= (1 << 9);   // SSM
    SPI1->CR1 |= (1 << 8);   // SSI
    debug_step = 14;

    // 5️⃣ Enable SPI
    SPI1->CR1 |= (1 << 6);   // SPE
    debug_step = 15;

    // 6️⃣ Enable TXE and RXNE Interrupt
    SPI1->CR2 |= (1 << 7);   // TXEIE
    SPI1->CR2 |= (1 << 6);   // RXNEIE
    debug_step = 16;

    // 7️⃣ Enable NVIC for SPI1 (IRQ 35)
    *((volatile uint32_t*)0xE000E104) |= (1 << (35 - 32));
    debug_step = 17;
}

void SPI1_IRQHandler(void)
{
    debug_step = 99;

    if (SPI1->SR & (1 << 1))  // TXE
    {
        SPI1->CR2 &= ~(1 << 7);   // 🔥 Disable TXEIE
    }

    if (SPI1->SR & (1 << 0))  // RXNE
    {
        volatile uint32_t temp = SPI1->DR;
    }
}
void SPI_Transmit(uint8_t *data, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        while(!(SPI1->SR & (1 << 1)));   // Wait TXE

        SPI1->DR = data[i];

        while(!(SPI1->SR & (1 << 0)));   // Wait RXNE

        volatile uint8_t dummy = SPI1->DR;  // Clear RX
    }
}

uint8_t SPI_Receive(void)
{
    while(!(SPI1->SR & (1 << 0)));  // Wait RXNE
    return SPI1->DR;
}
