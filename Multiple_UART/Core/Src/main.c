#include "stm32l4xx_hal.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

uint8_t tx1[] = "Hello from USART1\r\n";
uint8_t tx2[] = "Hello from USART2\r\n";

uint8_t rx1[20];
uint8_t rx2[20];

uint32_t tx_counter1 = 0;
uint32_t rx_counter1 = 0;

uint32_t tx_counter2 = 0;
uint32_t rx_counter2 = 0;

void SystemClock_Config(void);
void UART1_Init(void);
void UART2_Init(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    UART1_Init();
    UART2_Init();

    HAL_UART_Transmit_IT(&huart1, tx1, sizeof(tx1));
    HAL_UART_Transmit_IT(&huart2, tx2, sizeof(tx2));

    HAL_UART_Receive_IT(&huart1, rx1, sizeof(rx1));
    HAL_UART_Receive_IT(&huart2, rx2, sizeof(rx2));

    while (1)
    {
    }

    void SystemClock_Config(void)
    {
        RCC_OscInitTypeDef RCC_OscInitStruct = {0};
        RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

        HAL_RCC_DeInit();

        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
        RCC_OscInitStruct.MSIState = RCC_MSI_ON;
        RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
        RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

        HAL_RCC_OscConfig(&RCC_OscInitStruct);

        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                    | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;

        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

        HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
    }

}
