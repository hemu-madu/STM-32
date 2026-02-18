#include "stm32l476xx.h"

void delay_1sec(void);

int main(void)
{
    // 1. Enable GPIOA clock
    RCC->AHB2ENR |= (1 << 0);

    // 2. Set PA5 as output (LED)
    GPIOA->MODER &= ~(3 << (5*2));
    GPIOA->MODER |=  (1 << (5*2));

    // 3. Enable TIM2 clock
    RCC->APB1ENR1 |= (1 << 0);

    // 4. Configure TIM2
    TIM2->PSC = 1599;      // Prescaler
    TIM2->ARR = 9999;      // Auto reload

    TIM2->CNT = 0;         // Reset counter

    TIM2->CR1 |= (1 << 0); // Enable timer

    while(1)
    {
        delay_1sec();

        GPIOA->ODR ^= (1 << 5);  // Toggle LED
    }
}

void delay_1sec(void)
{
    while(!(TIM2->SR & (1 << 0))); // Wait until UIF flag set

    TIM2->SR &= ~(1 << 0);        // Clear UIF flag
}
