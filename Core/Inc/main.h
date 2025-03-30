/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTOR1_PWM_Pin GPIO_PIN_0
#define MOTOR1_PWM_GPIO_Port GPIOA
#define MOTOR2_PWM_Pin GPIO_PIN_1
#define MOTOR2_PWM_GPIO_Port GPIOA
#define MOTOR3_PWM_Pin GPIO_PIN_2
#define MOTOR3_PWM_GPIO_Port GPIOA
#define MOTOR1_IN1_Pin GPIO_PIN_3
#define MOTOR1_IN1_GPIO_Port GPIOA
#define MOTOR1_IN2_Pin GPIO_PIN_4
#define MOTOR1_IN2_GPIO_Port GPIOA
#define MOTOR2_IN1_Pin GPIO_PIN_5
#define MOTOR2_IN1_GPIO_Port GPIOA
#define SERVO1_PWM_Pin GPIO_PIN_6
#define SERVO1_PWM_GPIO_Port GPIOA
#define SERVO2_PWM_Pin GPIO_PIN_7
#define SERVO2_PWM_GPIO_Port GPIOA
#define MOTOR2_IN2_Pin GPIO_PIN_0
#define MOTOR2_IN2_GPIO_Port GPIOB
#define MOTOR3_IN1_Pin GPIO_PIN_1
#define MOTOR3_IN1_GPIO_Port GPIOB
#define MOTOR3_IN2_Pin GPIO_PIN_2
#define MOTOR3_IN2_GPIO_Port GPIOB
#define WARN_TX_Pin GPIO_PIN_10
#define WARN_TX_GPIO_Port GPIOB
#define WARN_RX_Pin GPIO_PIN_11
#define WARN_RX_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_12
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_13
#define OLED_SDA_GPIO_Port GPIOB
#define RECYCLE_SENSOR_Pin GPIO_PIN_14
#define RECYCLE_SENSOR_GPIO_Port GPIOB
#define OTHER_SENSOR_Pin GPIO_PIN_15
#define OTHER_SENSOR_GPIO_Port GPIOB
#define KITCHEN_SENSOR_Pin GPIO_PIN_8
#define KITCHEN_SENSOR_GPIO_Port GPIOA
#define TONGXIN_TX_Pin GPIO_PIN_9
#define TONGXIN_TX_GPIO_Port GPIOA
#define TONGXIN_RX_Pin GPIO_PIN_10
#define TONGXIN_RX_GPIO_Port GPIOA
#define HARM_SENSOR_Pin GPIO_PIN_11
#define HARM_SENSOR_GPIO_Port GPIOA
#define FIRST_SENSOR_Pin GPIO_PIN_12
#define FIRST_SENSOR_GPIO_Port GPIOA
#define SECOND_SENSOR_Pin GPIO_PIN_15
#define SECOND_SENSOR_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_4
#define KEY2_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_5
#define KEY3_GPIO_Port GPIOB
#define EEPROM_SCL_Pin GPIO_PIN_6
#define EEPROM_SCL_GPIO_Port GPIOB
#define EEPROM_SDA_Pin GPIO_PIN_7
#define EEPROM_SDA_GPIO_Port GPIOB
#define KEY4_Pin GPIO_PIN_8
#define KEY4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
