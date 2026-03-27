#ifndef EXTI_DRIVER_H
#define EXTI_DRIVER_H

#include "stm32f4xx.h"

/* Trigger Types */
#define EXTI_TRIGGER_RISING     0x01
#define EXTI_TRIGGER_FALLING    0x02
#define EXTI_TRIGGER_BOTH       0x03

void EXTI_Init(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t trigger);
void EXTI_EnableIRQ(uint8_t pin);

/* Weak callback function */
void EXTI_Callback(uint8_t pin);

#endif
