#include <stdint.h>
#include "stm32l476xx.h"
#include "lcd_gpio.h"
#include "ultrasonic_gpio.h"

/* Backlight pin */
#define BL_PORT GPIOB
#define BL_PIN  6

void delay_ms(uint32_t ms);

/* Software PWM brightness (0–100) */
void LCD_SetBrightness(uint8_t percent)
{
    uint32_t on_time  = percent;
    uint32_t off_time = 100 - percent;

    BL_PORT->ODR |=  (1 << BL_PIN);
    delay_ms(on_time);

    BL_PORT->ODR &= ~(1 << BL_PIN);
    delay_ms(off_time);
}

int main(void)
{
    /* Enable GPIOB clock */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    /* Backlight pin output */
    BL_PORT->MODER &= ~(3 << (2 * BL_PIN));
    BL_PORT->MODER |=  (1 << (2 * BL_PIN));

    LCD_Init();
    Ultrasonic_Init();

    while (1)
    {
        uint32_t distance = Ultrasonic_Read();

        /* Dim when object is close */
        if (distance < 20)
            LCD_SetBrightness(20);
        else
            LCD_SetBrightness(80);

        LCD_Clear();
        LCD_Print("Distance:");

        char buf[10];
        int i = 0;
        uint32_t t = distance;

        if (t == 0) buf[i++] = '0';
        while (t > 0)
        {
            buf[i++] = (t % 10) + '0';
            t /= 10;
        }
        for (int j = i - 1; j >= 0; j--)
            LCD_SendData(buf[j]);

        LCD_Print("cm");

        delay_ms(300);
    }
}

/* Simple delay */
void delay_ms(uint32_t ms)
{
    while (ms--)
        for (volatile uint32_t i = 0; i < 8000; i++);
}
