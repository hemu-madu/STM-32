#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* Function Prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

void array_fill(int *arr, int size);
void display_numbers(int *arr, int size);
void swap_numbers(int *a, int *b);
void bubble_sort(int *arr, int size);
void insertion_sort(int *arr, int size);

/* Retarget printf to UART */
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    printf("\r\n==== STM32L476 Sorting Demo ====\r\n");

    int numbers[10];

    array_fill(numbers, 10);

    printf("Original Array:\r\n");
    display_numbers(numbers, 10);

    bubble_sort(numbers, 10);
    printf("\r\nAfter Bubble Sort:\r\n");
    display_numbers(numbers, 10);

    array_fill(numbers, 10);  // refill

    insertion_sort(numbers, 10);
    printf("\r\nAfter Insertion Sort:\r\n");
    display_numbers(numbers, 10);

    while (1)
    {
    }
}

/* Fill array with random numbers */
void array_fill(int *arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }
}

/* Display numbers */
void display_numbers(int *arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\r\n");
}

/* Swap numbers */
void swap_numbers(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Bubble Sort */
void bubble_sort(int *arr, int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                swap_numbers(&arr[j], &arr[j+1]);
            }
        }
    }
}

/* Insertion Sort */
void insertion_sort(int *arr, int size)
{
    for(int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/* USART2 Init */
static void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
}

/* GPIO Init */
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
}

/* System Clock (Basic HSI 4 MHz) */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}


void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
        // You can toggle LED here if needed
    }
}
