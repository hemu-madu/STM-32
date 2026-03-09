#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "stm32f4xx.h"

/* GPIO Modes */
#define GPIO_MODE_INPUT     0x00
#define GPIO_MODE_OUTPUT    0x01

/* Pull Config */
#define GPIO_NO_PULL        0x00
#define GPIO_PULL_UP        0x01
#define GPIO_PULL_DOWN      0x02

void GPIO_EnableClock(GPIO_TypeDef *GPIOx);
void GPIO_Init(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t mode, uint8_t pull);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t state);
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint8_t pin);

#endif
