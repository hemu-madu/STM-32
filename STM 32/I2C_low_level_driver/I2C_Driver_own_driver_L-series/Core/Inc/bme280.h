#ifndef BME280_H
#define BME280_H

#include <stdint.h>

void BME280_Init(void);
float BME280_ReadTemperature(void);
void BME280_ReadCalibration(void);

#endif
