#include "gpio.h"

void GPIOA_Init(void)
{
    /* 1. Enable Clock for GPIOA */
    RCC_AHB1ENR |= (1 << 0);

    /* 2. Set PA5 as Output (MODER = 01) */
    GPIOA_MODER &= ~(3 << (5 * 2));
    GPIOA_MODER |=  (1 << (5 * 2));

    /* 3. Set Push-Pull */
    GPIOA_OTYPER &= ~(1 << 5);

    /* 4. Set High Speed */
    GPIOA_OSPEEDR |= (3 << (5 * 2));

    /* 5. No Pull-up/Pull-down */
    GPIOA_PUPDR &= ~(3 << (5 * 2));
}

void GPIOA_SetPin(uint8_t pin)
{
    GPIOA_ODR |= (1 << pin);
}

void GPIOA_ResetPin(uint8_t pin)
{
    GPIOA_ODR &= ~(1 << pin);
}

void GPIOA_TogglePin(uint8_t pin)
{
    GPIOA_ODR ^= (1 << pin);
}
