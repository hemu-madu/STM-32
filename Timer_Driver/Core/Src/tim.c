#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_tim.h"
#include "tim.h"

TIM_HandleTypeDef htim2;

void tim_timebase_init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 16000 - 1;
    htim2.Init.Period = 1000 - 1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;

    HAL_TIM_Base_Init(&htim2);
    HAL_TIM_Base_Start_IT(&htim2);

    NVIC_SetPriority(TIM2_IRQn, 1);
    NVIC_EnableIRQ(TIM2_IRQn);
}
