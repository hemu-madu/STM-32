#include "tmp007.h"
#include "i2c_driver.h"

uint16_t TMP007_ReadTempRaw(void)
{
    return I2C1_Read16(TMP007_ADDR, TMP007_TEMP_REG);
}

float TMP007_ReadTempC(void)
{
    uint16_t raw = TMP007_ReadTempRaw();
    return raw * 0.03125f;
}
