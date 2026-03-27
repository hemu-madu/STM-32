#include "gpio_driver.h"

void GPIO_EnableClock(GPIO_TypeDef *GPIOx)
{
    if(GPIOx == GPIOA) RCC->AHB1ENR |= (1 << 0);
    else if(GPIOx == GPIOB) RCC->AHB1ENR |= (1 << 1);
    else if(GPIOx == GPIOC) RCC->AHB1ENR |= (1 << 2);
    else if(GPIOx == GPIOD) RCC->AHB1ENR |= (1 << 3);
}

void GPIO_Init(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t mode, uint8_t pull)
{
    /* Clear mode */
    GPIOx->MODER &= ~(3 << (pin * 2));
    GPIOx->MODER |=  (mode << (pin * 2));

    /* Clear pull */
    GPIOx->PUPDR &= ~(3 << (pin * 2));
    GPIOx->PUPDR |=  (pull << (pin * 2));
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t state)
{
    if(state)
        GPIOx->ODR |= (1 << pin);
    else
        GPIOx->ODR &= ~(1 << pin);
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint8_t pin)
{
    GPIOx->ODR ^= (1 << pin);
}
