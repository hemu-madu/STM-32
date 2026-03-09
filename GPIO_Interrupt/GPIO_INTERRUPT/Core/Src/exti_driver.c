#include "exti_driver.h"

void EXTI_Init(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t trigger)
{
    /* Enable SYSCFG clock */
    RCC->APB2ENR |= (1 << 14);

    uint8_t portcode = 0;

    if(GPIOx == GPIOA) portcode = 0;
    else if(GPIOx == GPIOB) portcode = 1;
    else if(GPIOx == GPIOC) portcode = 2;
    else if(GPIOx == GPIOD) portcode = 3;

    uint8_t index = pin / 4;
    uint8_t position = (pin % 4) * 4;

    /* Map EXTI line to port */
    SYSCFG->EXTICR[index] &= ~(0xF << position);
    SYSCFG->EXTICR[index] |=  (portcode << position);

    /* Unmask interrupt */
    EXTI->IMR |= (1 << pin);

    /* Trigger selection */
    if(trigger == EXTI_TRIGGER_RISING)
        EXTI->RTSR |= (1 << pin);

    else if(trigger == EXTI_TRIGGER_FALLING)
        EXTI->FTSR |= (1 << pin);

    else if(trigger == EXTI_TRIGGER_BOTH)
    {
        EXTI->RTSR |= (1 << pin);
        EXTI->FTSR |= (1 << pin);
    }
}

void EXTI_EnableIRQ(uint8_t pin)
{
    if(pin <= 4)
        NVIC_EnableIRQ((IRQn_Type)(EXTI0_IRQn + pin));
    else if(pin <= 9)
        NVIC_EnableIRQ(EXTI9_5_IRQn);
    else
        NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* Default weak callback */
__attribute__((weak)) void EXTI_Callback(uint8_t pin)
{
    // User override this in main.c
}

/* IRQ Handlers */

void EXTI15_10_IRQHandler(void)
{
    for(uint8_t i = 10; i <= 15; i++)
    {
        if(EXTI->PR & (1 << i))
        {
            EXTI->PR |= (1 << i);
            EXTI_Callback(i);
        }
    }
}

void EXTI9_5_IRQHandler(void)
{
    for(uint8_t i = 5; i <= 9; i++)
    {
        if(EXTI->PR & (1 << i))
        {
            EXTI->PR |= (1 << i);
            EXTI_Callback(i);
        }
    }
}

void EXTI0_IRQHandler(void)
{
    if(EXTI->PR & (1 << 0))
    {
        EXTI->PR |= (1 << 0);
        EXTI_Callback(0);
    }
}

void EXTI1_IRQHandler(void)
{
    if(EXTI->PR & (1 << 1))
    {
        EXTI->PR |= (1 << 1);
        EXTI_Callback(1);
    }
}

void EXTI2_IRQHandler(void)
{
    if(EXTI->PR & (1 << 2))
    {
        EXTI->PR |= (1 << 2);
        EXTI_Callback(2);
    }
}

void EXTI3_IRQHandler(void)
{
    if(EXTI->PR & (1 << 3))
    {
        EXTI->PR |= (1 << 3);
        EXTI_Callback(3);
    }
}

void EXTI4_IRQHandler(void)
{
    if(EXTI->PR & (1 << 4))
    {
        EXTI->PR |= (1 << 4);
        EXTI_Callback(4);
    }
}
