#ifndef DEVICE_REGISTERS_H
#define DEVICE_REGISTERS_H

#include <stdint.h>

/* RCC */
#define RCC_BASE      0x40023800U
#define RCC_AHB1ENR   (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB2ENR   (*(volatile uint32_t*)(RCC_BASE + 0x44))

/* GPIOA */
#define GPIOA_BASE    0x40020000U
#define GPIOA_MODER   (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL    (*(volatile uint32_t*)(GPIOA_BASE + 0x20))

/* SPI1 Registers */

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;

} SPI_RegDef_t;

#define SPI1 ((SPI_RegDef_t*)0x40013000U)

#endif
