#include "i2c_driver.h"

static void I2C1_GPIO_Config(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // PB8, PB9 Alternate function
    GPIOB->MODER &= ~(0xF << 16);
    GPIOB->MODER |=  (0xA << 16);

    // Open drain
    GPIOB->OTYPER |= (1 << 8) | (1 << 9);

    // Pull-up
    GPIOB->PUPDR &= ~(0xF << 16);
    GPIOB->PUPDR |=  (0x5 << 16);

    // High speed
    GPIOB->OSPEEDR |= (0xF << 16);

    // AF4 for I2C
    GPIOB->AFR[1] &= ~(0xFF);
    GPIOB->AFR[1] |= (4 << 0);   // PB8
    GPIOB->AFR[1] |= (4 << 4);   // PB9
}

void I2C1_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    I2C1_GPIO_Config();

    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    I2C1->CR2 = 16;      // APB1 16MHz
    I2C1->CCR = 80;      // 100kHz
    I2C1->TRISE = 17;

    I2C1->CR1 |= I2C_CR1_PE;
}

uint16_t I2C1_Read16(uint8_t addr, uint8_t reg)
{
    uint8_t msb, lsb;
    uint16_t data;

    while(I2C1->SR2 & I2C_SR2_BUSY);

    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = addr << 1;
    while(!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    I2C1->DR = reg;
    while(!(I2C1->SR1 & I2C_SR1_TXE));

    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = (addr << 1) | 1;
    while(!(I2C1->SR1 & I2C_SR1_ADDR));

    I2C1->CR1 |= I2C_CR1_ACK;
    (void)I2C1->SR2;

    while(!(I2C1->SR1 & I2C_SR1_RXNE));
    msb = I2C1->DR;

    I2C1->CR1 &= ~I2C_CR1_ACK;
    I2C1->CR1 |= I2C_CR1_STOP;

    while(!(I2C1->SR1 & I2C_SR1_RXNE));
    lsb = I2C1->DR;

    data = (msb << 8) | lsb;

    return data;
}
