#include "device_registers.h"
#include "spi_driver.h"

volatile uint32_t debug_step = 0;
volatile uint32_t debug_CR1 = 0;
volatile uint32_t debug_CR2 = 0;
volatile uint32_t debug_NVIC = 0;
volatile uint32_t debug_SR = 0;


int main(void)
{
    debug_step = 1;

    SPI_Init();

    debug_step = 2;

    while(1)
    {
        debug_CR1 = SPI1->CR1;
        debug_CR2  = SPI1->CR2;
        debug_NVIC = *((volatile unsigned int*)0xE000E104);
        debug_SR = *((volatile unsigned int*)0x40013008);
    }
}
