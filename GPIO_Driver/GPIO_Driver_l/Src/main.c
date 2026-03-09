#include "gpio.h"

void delay(void)
{
    for(volatile int i=0; i<500000; i++);
}

int main(void)
{
    GPIOA_Init();

    while(1)
    {
        GPIOA_TogglePin(5);
        delay();
    }
}
