#ifndef TMP007_H
#define TMP007_H

#include <stdint.h>

#define TMP007_ADDR      0x40
#define TMP007_TEMP_REG  0x03

uint16_t TMP007_ReadTempRaw(void);
float TMP007_ReadTempC(void);

#endif
