#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>

void SPI_Init(void);
void SPI_Transmit(uint8_t *data, uint32_t len);
uint8_t SPI_Receive(void);

#endif
