#include "timer_driver.h"
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

/* Initialize TIM2 for 1 second interrupt */
void Timer_Init_1s(void)
{
    /* Enable TIM2 clock */
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    /* Prescaler: 16 MHz → 1 kHz */
    TIM2->PSC = 16000 - 1;

    /* Auto-reload: 1 kHz → 1 second */
    TIM2->ARR = 1000 - 1;

    /* Clear update flag */
    TIM2->SR &= ~TIM_SR_UIF;

    /* Enable update interrupt */
    TIM2->DIER |= TIM_DIER_UIE;

    /* Enable NVIC interrupt */
    NVIC_EnableIRQ(TIM2_IRQn);
}

void Timer_Start(void)
{
    TIM2->CR1 |= TIM_CR1_CEN;
}

void Timer_Stop(void)
{
    TIM2->CR1 &= ~TIM_CR1_CEN;
}
