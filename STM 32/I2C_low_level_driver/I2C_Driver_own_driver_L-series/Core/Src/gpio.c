#include "stm32l476xx.h"
#include "gpio.h"

void GPIO_Init(void)
{
    /* UART PA2 TX */
    GPIOA->MODER &= ~(3 << (2*2));
    GPIOA->MODER |=  (2 << (2*2));
    GPIOA->AFR[0] |= (7 << (2*4));

    /* I2C PB8 SCL, PB9 SDA */
    GPIOB->MODER &= ~(3<<(8*2) | 3<<(9*2));
    GPIOB->MODER |=  (2<<(8*2) | 2<<(9*2));
    GPIOB->AFR[1] |= (4<<0) | (4<<4);
    GPIOB->OTYPER |= (1<<8) | (1<<9);
    GPIOB->PUPDR |= (1<<(8*2)) | (1<<(9*2));
}
