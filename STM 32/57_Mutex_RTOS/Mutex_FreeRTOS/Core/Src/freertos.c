#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart2;
extern SemaphoreHandle_t  uartMutexHandle;

/* ================= TASK 1 ================= */
void Task1_func(void const * argument)
{
  osDelay(200);
  printf("[Task1] Started\r\n");

  for(;;)
  {
    /* Take mutex — wait forever until available */
    if(xSemaphoreTake(uartMutexHandle, portMAX_DELAY) == pdTRUE)
    {
      /* --- Critical section start --- */
      printf("[Task1] Mutex taken\r\n");
      printf("[Task1] Accessing shared resource...\r\n");
      osDelay(500);   /* simulate work */
      printf("[Task1] Done. Releasing mutex\r\n");
      /* --- Critical section end --- */

      xSemaphoreGive(uartMutexHandle);
    }

    osDelay(1000);
  }
}

/* ================= TASK 2 ================= */
void Task2_func(void const * argument)
{
  osDelay(400);
  printf("[Task2] Started\r\n");

  for(;;)
  {
    /* Take mutex — wait forever until available */
    if(xSemaphoreTake(uartMutexHandle, portMAX_DELAY) == pdTRUE)
    {
      /* --- Critical section start --- */
      printf("[Task2] Mutex taken\r\n");
      printf("[Task2] Accessing shared resource...\r\n");
      osDelay(500);   /* simulate work */
      printf("[Task2] Done. Releasing mutex\r\n");
      /* --- Critical section end --- */

      xSemaphoreGive(uartMutexHandle);
    }

    osDelay(1000);
  }
}

/* ================= IDLE TASK MEMORY ================= */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t  xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t  **ppxIdleTaskStackBuffer,
                                   uint32_t      *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer   = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = xIdleStack;
  *pulIdleTaskStackSize   = configMINIMAL_STACK_SIZE;
}
