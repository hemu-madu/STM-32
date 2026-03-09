#include "stm32f411xe.h"
#include "gpio_driver.h"
#include "exti_driver.h"

void EXTI_Callback(uint8_t pin)
{
    if(pin == 13)
    {
        GPIO_TogglePin(GPIOA, 5);
    }
}


int main(void)
{
    /* Enable GPIO clocks */
    GPIO_EnableClock(GPIOA);
    GPIO_EnableClock(GPIOC);

    /* Configure PA5 as Output (LED) */
    GPIO_Init(GPIOA, 5, GPIO_MODE_OUTPUT, GPIO_NO_PULL);

    /* Configure PC13 as Input with Pull-Up (Button) */
    GPIO_Init(GPIOC, 13, GPIO_MODE_INPUT, GPIO_PULL_UP);

    /* Configure EXTI for PC13 (Falling Edge Trigger) */
    EXTI_Init(GPIOC, 13, EXTI_TRIGGER_FALLING);

    /* Enable NVIC Interrupt */
    EXTI_EnableIRQ(13);

    while(1)
    {
        // Main loop empty
    }
}
