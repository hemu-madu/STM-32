#include "lcd.h"

#define RS_PIN GPIO_PIN_0
#define EN_PIN GPIO_PIN_1
#define D4_PIN GPIO_PIN_2
#define D5_PIN GPIO_PIN_3
#define D6_PIN GPIO_PIN_4
#define D7_PIN GPIO_PIN_5

#define LCD_PORT GPIOA

void LCD_Enable()
{
 HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_SET);
 HAL_Delay(1);
 HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_RESET);
 HAL_Delay(1);
}

void LCD_Send4Bit(uint8_t data)
{
 HAL_GPIO_WritePin(LCD_PORT, D4_PIN, (data>>0)&1);
 HAL_GPIO_WritePin(LCD_PORT, D5_PIN, (data>>1)&1);
 HAL_GPIO_WritePin(LCD_PORT, D6_PIN, (data>>2)&1);
 HAL_GPIO_WritePin(LCD_PORT, D7_PIN, (data>>3)&1);
}

void LCD_Command(uint8_t cmd)
{
 HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_RESET);

 LCD_Send4Bit(cmd>>4);
 LCD_Enable();

 LCD_Send4Bit(cmd&0x0F);
 LCD_Enable();
}

void LCD_Char(uint8_t data)
{
 HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_SET);

 LCD_Send4Bit(data>>4);
 LCD_Enable();

 LCD_Send4Bit(data&0x0F);
 LCD_Enable();
}

void LCD_String(char *str)
{
 while(*str) LCD_Char(*str++);
}

void LCD_Init()
{
 HAL_Delay(50);

 LCD_Command(0x02);
 LCD_Command(0x28);
 LCD_Command(0x0C);
 LCD_Command(0x06);
 LCD_Command(0x01);
}
