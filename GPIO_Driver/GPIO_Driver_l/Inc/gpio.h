#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* Base Addresses */
#define PERIPH_BASE       0x40000000UL
#define AHB1_OFFSET       0x00020000UL
#define AHB1_BASE         (PERIPH_BASE + AHB1_OFFSET)

#define GPIOA_OFFSET      0x0000UL
#define RCC_OFFSET        0x3800UL

#define GPIOA_BASE        (AHB1_BASE + GPIOA_OFFSET)
#define RCC_BASE          (AHB1_BASE + RCC_OFFSET)

/* RCC Register */
#define RCC_AHB1ENR       (*(volatile uint32_t*)(RCC_BASE + 0x30))

/* GPIO Registers */
#define GPIOA_MODER       (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_OTYPER      (*(volatile uint32_t*)(GPIOA_BASE + 0x04))
#define GPIOA_OSPEEDR     (*(volatile uint32_t*)(GPIOA_BASE + 0x08))
#define GPIOA_PUPDR       (*(volatile uint32_t*)(GPIOA_BASE + 0x0C))
#define GPIOA_IDR         (*(volatile uint32_t*)(GPIOA_BASE + 0x10))
#define GPIOA_ODR         (*(volatile uint32_t*)(GPIOA_BASE + 0x14))

/* Function Prototypes */
void GPIOA_Init(void);
void GPIOA_SetPin(uint8_t pin);
void GPIOA_ResetPin(uint8_t pin);
void GPIOA_TogglePin(uint8_t pin);

#endif
