/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "string.h"
#include "stdio.h"
#include "bsp_uart.h"
#include "usart.h"
#include "sensor.h"
#include "bsp_motor.h"
#include "key.h"
#include "bsp_task.h"
#include "syn6288.h"
#include "eeprom.h"
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId ConTaskHandle;
osThreadId DisTaskHandle;
osThreadId KTaskHandle;
osThreadId eepTaskHandle;
osThreadId SenTaskHandle;
osThreadId UartTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Con_Task(void const * argument);
void Dis_Task(void const * argument);
void K_Task(void const * argument);
void eep_Task(void const * argument);
void Sen_Task(void const * argument);
void Uart_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of ConTask */
  osThreadDef(ConTask, Con_Task, osPriorityHigh, 0, 128);
  ConTaskHandle = osThreadCreate(osThread(ConTask), NULL);

  /* definition and creation of DisTask */
  osThreadDef(DisTask, Dis_Task, osPriorityAboveNormal, 0, 128);
  DisTaskHandle = osThreadCreate(osThread(DisTask), NULL);

  /* definition and creation of KTask */
  osThreadDef(KTask, K_Task, osPriorityNormal, 0, 128);
  KTaskHandle = osThreadCreate(osThread(KTask), NULL);

  /* definition and creation of eepTask */
  osThreadDef(eepTask, eep_Task, osPriorityAboveNormal, 0, 128);
  eepTaskHandle = osThreadCreate(osThread(eepTask), NULL);

  /* definition and creation of SenTask */
  osThreadDef(SenTask, Sen_Task, osPriorityNormal, 0, 128);
  SenTaskHandle = osThreadCreate(osThread(SenTask), NULL);

  /* definition and creation of UartTask */
  osThreadDef(UartTask, Uart_Task, osPriorityNormal, 0, 128);
  UartTaskHandle = osThreadCreate(osThread(UartTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Con_Task */
/**
  * @brief  Function implementing the ConTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Con_Task */
void Con_Task(void const * argument)
{
  /* USER CODE BEGIN Con_Task */
  /* Infinite loop */
  for(;;)
  {
	Control_Task();
    vTaskDelay(10);
  }
  /* USER CODE END Con_Task */
}

/* USER CODE BEGIN Header_Dis_Task */
/**
* @brief Function implementing the DisTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Dis_Task */
void Dis_Task(void const * argument)
{
  /* USER CODE BEGIN Dis_Task */
  /* Infinite loop */
  for(;;)
  {
	  Display_Task();
	  vTaskDelay(10);
  }
  /* USER CODE END Dis_Task */
}

/* USER CODE BEGIN Header_K_Task */
/**
* @brief Function implementing the KTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_K_Task */
void K_Task(void const * argument)
{
  /* USER CODE BEGIN K_Task */
  /* Infinite loop */
  for(;;)
  {
	 Key_Task();
     osDelay(10);
  }
  /* USER CODE END K_Task */
}

/* USER CODE BEGIN Header_eep_Task */
/**
* @brief Function implementing the eepTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_eep_Task */
void eep_Task(void const * argument)
{
  /* USER CODE BEGIN eep_Task */
  /* Infinite loop */
  for(;;)
  {
	eeprom_Task();
    vTaskDelay(10);
  }
  /* USER CODE END eep_Task */
}

/* USER CODE BEGIN Header_Sen_Task */
/**
* @brief Function implementing the SenTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Sen_Task */
void Sen_Task(void const * argument)
{
  /* USER CODE BEGIN Sen_Task */
  /* Infinite loop */
  for(;;)
  {
	Sensor_Task();	  
    osDelay(10);
  }
  /* USER CODE END Sen_Task */
}

/* USER CODE BEGIN Header_Uart_Task */
/**
* @brief Function implementing the UartTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Uart_Task */
void Uart_Task(void const * argument)
{
  /* USER CODE BEGIN Uart_Task */
  /* Infinite loop */
  for(;;)
  {
	uart_Task();
    osDelay(10);
  }
  /* USER CODE END Uart_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

