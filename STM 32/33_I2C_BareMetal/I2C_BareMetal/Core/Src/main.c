#include "stm32l476xx.h"

/* Function Prototypes */
void UART2_Init(void);
void UART2_Write(char ch);
void UART2_Print(char *str);

void I2C1_Init(void);
void I2C1_Start(uint8_t addr);

/* Global Variables */
volatile uint8_t transferComplete = 0;
volatile uint8_t txData = 0xAA;

/* ===================== MAIN ===================== */

int main(void)
{
    UART2_Init();
    I2C1_Init();

    UART2_Print("I2C Interrupt BareMetal\r\n");

    while(1)
    {
        transferComplete = 0;

        I2C1_Start(0x50);   // Send to slave 0x50

        while(!transferComplete);   // Wait for ISR

        UART2_Print("Transfer Done\r\n");

        for(volatile int i=0; i<200000; i++);
    }
}

/* ===================== UART ===================== */

void UART2_Init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

    /* PA2 -> AF7 (USART2_TX) */
    GPIOA->MODER &= ~(3 << (2*2));
    GPIOA->MODER |=  (2 << (2*2));

    GPIOA->AFR[0] &= ~(0xF << (4*2));
    GPIOA->AFR[0] |=  (7 << (4*2));

    USART2->CR1 = 0;

    /* 4 MHz / 9600 = 416 */
    USART2->BRR = 416;

    USART2->CR1 |= USART_CR1_TE;
    USART2->CR1 |= USART_CR1_UE;
}

void UART2_Write(char ch)
{
    while(!(USART2->ISR & USART_ISR_TXE));
    USART2->TDR = ch;
}

void UART2_Print(char *str)
{
    while(*str)
    {
        UART2_Write(*str++);
    }
}

/* ===================== I2C ===================== */

void I2C1_Init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;

    /* PB6 = SCL, PB7 = SDA */
    GPIOB->MODER &= ~(0xF << (6*2));
    GPIOB->MODER |=  (0xA << (6*2));   // AF mode

    GPIOB->OTYPER |= (1<<6) | (1<<7);  // Open-drain
    GPIOB->OSPEEDR |= (3<<(6*2)) | (3<<(7*2));
    GPIOB->PUPDR |= (1<<(6*2)) | (1<<(7*2));

    GPIOB->AFR[0] &= ~((0xF<<(4*6)) | (0xF<<(4*7)));
    GPIOB->AFR[0] |=  (4<<(4*6)) | (4<<(4*7));  // AF4

    I2C1->CR1 &= ~I2C_CR1_PE;

    /* TIMING for 4 MHz → 100 kHz */
    I2C1->TIMINGR = 0x0010020A;

    /* Enable interrupts */
    I2C1->CR1 |= I2C_CR1_TXIE;
    I2C1->CR1 |= I2C_CR1_TCIE;
    I2C1->CR1 |= I2C_CR1_ERRIE;

    NVIC_EnableIRQ(I2C1_EV_IRQn);
    NVIC_EnableIRQ(I2C1_ER_IRQn);

    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1_Start(uint8_t addr)
{
    I2C1->CR2 = 0;

    I2C1->CR2 |= (addr << 1);
    I2C1->CR2 |= (1 << 16);      // NBYTES = 1
    I2C1->CR2 |= I2C_CR2_START;
}

/* ===================== I2C INTERRUPTS ===================== */

void I2C1_EV_IRQHandler(void)
{
    if(I2C1->ISR & I2C_ISR_TXIS)
    {
        I2C1->TXDR = txData;
    }

    if(I2C1->ISR & I2C_ISR_TC)
    {
        I2C1->CR2 |= I2C_CR2_STOP;
        transferComplete = 1;
    }
}

void I2C1_ER_IRQHandler(void)
{
    if(I2C1->ISR & I2C_ISR_NACKF)
    {
        I2C1->ICR |= I2C_ICR_NACKCF;
        I2C1->CR2 |= I2C_CR2_STOP;
        transferComplete = 1;
    }
}
