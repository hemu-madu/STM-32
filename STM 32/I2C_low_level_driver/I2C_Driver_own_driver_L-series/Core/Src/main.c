#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "bme280.h"

extern int32_t BME280_ReadTempRaw(void);

void delay(void)
{
    for(volatile int i=0;i<1000000;i++);
}

int main(void)
{
    RCC_Init();
    GPIO_Init();
    UART2_Init();
    I2C1_Init();
    BME280_Init();
    BME280_ReadCalibration();

    UART2_Print("BME280 Celsius Test\r\n");

    while(1)
    {
        float temp = BME280_ReadTemperature();

        UART2_Print("Temperature: ");
        UART2_Print_Float(temp);
        UART2_Print(" C\r\n");

        for(volatile int i=0;i<2000000;i++);
    }
}
