#include "uart.h"

UART_Handle_t huart2;

int main(void)
{
    huart2.Instance = USART2;
    huart2.BaudRate = 9600;

    UART_Init(&huart2);

    while(1)
    {
        UART_WriteString(&huart2, "Custom Driver Working\r\n");

        for(int i=0;i<1000000;i++);
    }
}
