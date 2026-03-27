/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Task Deletion FreeRTOS Demo
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

osThreadId defaultTaskHandle;

/* USER CODE BEGIN PV */
osThreadId tempTaskHandle;
osThreadId monitorTaskHandle;
osThreadId heartbeatTaskHandle;

uint8_t uart_buf[120];
uint8_t tempTaskDone    = 0;   // 0 = alive, 1 = deleted
uint8_t monitorTaskDone = 0;   // 0 = alive, 1 = deleted
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */
void TempTask(void const * argument);
void MonitorTask(void const * argument);
void HeartbeatTask(void const * argument);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  MX_GPIO_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  osThreadDef(tempTask,      TempTask,      osPriorityNormal,      0, 128);
  osThreadDef(monitorTask,   MonitorTask,   osPriorityNormal,      0, 128);
  osThreadDef(heartbeatTask, HeartbeatTask, osPriorityBelowNormal, 0, 128);

  tempTaskHandle      = osThreadCreate(osThread(tempTask),      NULL);
  monitorTaskHandle   = osThreadCreate(osThread(monitorTask),   NULL);
  heartbeatTaskHandle = osThreadCreate(osThread(heartbeatTask), NULL);
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here */
  while (1)
  {
  }
}

/* USER CODE BEGIN 4 */

/* ------- TEMP TASK: runs 5 times then deletes itself ------- */
void TempTask(void const * argument)
{
  uint8_t i;
  for(i = 1; i <= 5; i++)
  {
    int len = snprintf((char*)uart_buf, sizeof(uart_buf),
              "[Temp Task]    Running... pass %d/5\r\n", i);
    HAL_UART_Transmit(&huart2, uart_buf, len, HAL_MAX_DELAY);
    osDelay(1000);
  }

  uint8_t msg[] = "[Temp Task]    Work done! Deleting self...\r\n";
  HAL_UART_Transmit(&huart2, msg, strlen((char*)msg), HAL_MAX_DELAY);
  osDelay(100);

  tempTaskDone = 1;        // set flag BEFORE deleting
  vTaskDelete(NULL);       // delete self
}

/* ------- MONITOR TASK: runs 3 times then deletes itself ------- */
void MonitorTask(void const * argument)
{
  uint8_t i;
  for(i = 1; i <= 3; i++)
  {
    int len = snprintf((char*)uart_buf, sizeof(uart_buf),
              "[Monitor Task] Checking system... pass %d/3\r\n", i);
    HAL_UART_Transmit(&huart2, uart_buf, len, HAL_MAX_DELAY);
    osDelay(1500);
  }

  uint8_t msg[] = "[Monitor Task] Monitoring complete! Deleting self...\r\n";
  HAL_UART_Transmit(&huart2, msg, strlen((char*)msg), HAL_MAX_DELAY);
  osDelay(100);

  monitorTaskDone = 1;     // set flag BEFORE deleting
  vTaskDelete(NULL);       // delete self
}

/* ------- HEARTBEAT TASK: runs forever, shows status of other tasks ------- */
void HeartbeatTask(void const * argument)
{
  uint32_t count = 0;
  for(;;)
  {
    count++;

    const char *tempStatus = (tempTaskDone    == 0) ? "ALIVE" : "DELETED";
    const char *monStatus  = (monitorTaskDone == 0) ? "ALIVE" : "DELETED";

    int len = snprintf((char*)uart_buf, sizeof(uart_buf),
              "[HB Task]      Tick #%lu | TempTask:%s | MonitorTask:%s\r\n",
              count, tempStatus, monStatus);

    HAL_UART_Transmit(&huart2, uart_buf, len, HAL_MAX_DELAY);
    osDelay(2000);
  }
}

/* USER CODE END 4 */

/* ------- DEFAULT TASK: idle ------- */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/**
  * @brief System Clock Configuration
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    Error_Handler();

  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM            = 1;
  RCC_OscInitStruct.PLL.PLLN            = 10;
  RCC_OscInitStruct.PLL.PLLP            = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ            = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR            = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    Error_Handler();

  RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                   | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    Error_Handler();
}

/**
  * @brief USART2 Initialization
  */
static void MX_USART2_UART_Init(void)
{
  huart2.Instance                    = USART2;
  huart2.Init.BaudRate               = 115200;
  huart2.Init.WordLength             = UART_WORDLENGTH_8B;
  huart2.Init.StopBits               = UART_STOPBITS_1;
  huart2.Init.Parity                 = UART_PARITY_NONE;
  huart2.Init.Mode                   = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling           = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
    Error_Handler();
}

/**
  * @brief GPIO Initialization
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin  = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = LD2_Pin;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
}

/**
  * @brief Error Handler
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  __disable_irq();
  while (1) {}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* USER CODE END 6 */
}
#endif
