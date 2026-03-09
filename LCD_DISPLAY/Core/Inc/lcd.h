#ifndef LCD_H
#define LCD_H

#include "stm32l4xx_hal.h"

void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Char(uint8_t data);
void LCD_String(char *str);

#endif
