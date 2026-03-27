#ifndef SD_SPI_H
#define SD_SPI_H

#include "main.h"

uint8_t SD_Init(void);
uint8_t SD_ReadBlock(uint8_t *buffer, uint32_t sector);
uint8_t SD_WriteBlock(uint8_t *buffer, uint32_t sector);

#endif
