#include <stdint.h>
#include "ultrasonic_gpio.h"
#include "stm32l476xx.h"

#ifndef ULTRASONIC_GPIO_H
#define ULTRASONIC_GPIO_H

#include <stdint.h>
#include "stm32l476xx.h"

/* Pin configuration */
#define TRIG_PORT GPIOB
#define TRIG_PIN  4

#define ECHO_PORT GPIOB
#define ECHO_PIN  5

void Ultrasonic_Init(void);
uint32_t Ultrasonic_Read(void);
void delay_us(uint32_t us);

#endif
void delay_us(uint32_t us);


uint32_t Ultrasonic_Read(void)
{
    uint32_t count = 0;
    uint32_t timeout;

    // Trigger pulse
    TRIG_PORT->ODR &= ~(1 << TRIG_PIN);
    delay_us(2);
    TRIG_PORT->ODR |=  (1 << TRIG_PIN);
    delay_us(10);
    TRIG_PORT->ODR &= ~(1 << TRIG_PIN);

    // Wait for echo HIGH with timeout
    timeout = 30000;
    while (!(ECHO_PORT->IDR & (1 << ECHO_PIN)))
    {
        if (--timeout == 0)
            return 0;
    }

    // Measure echo HIGH time
    while (ECHO_PORT->IDR & (1 << ECHO_PIN))
    {
        count++;
    }

    // Convert to distance (approx cm)
    return (count / 100);
}
