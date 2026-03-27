#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "stm32f411xe.h"

void I2C1_Init(void);
uint16_t I2C1_Read16(uint8_t addr, uint8_t reg);

#endif
