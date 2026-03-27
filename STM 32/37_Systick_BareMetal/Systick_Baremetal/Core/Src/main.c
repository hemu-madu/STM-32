#include "stm32l476xx.h"

volatile uint32_t msTicks = 0;

void delay_ms(uint32_t ms)
{
    uint32_t start = msTicks;
    while ((msTicks - start) < ms);
}

int main(void)
{
    /* Enable global interrupts */
    __enable_irq();

    /* Enable GPIOA clock */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    /* Set PA5 as Output */
    GPIOA->MODER &= ~(3 << (5 * 2));
    GPIOA->MODER |=  (1 << (5 * 2));

    /* SysTick config for 1ms (4 MHz clock) */
    SysTick->LOAD = 4000 - 1;
    SysTick->VAL  = 0;
    SysTick->CTRL = (1 << 2) | (1 << 1) | (1 << 0);

    while (1)
    {
        GPIOA->ODR ^= (1 << 5);
        delay_ms(1000);
    }
}
