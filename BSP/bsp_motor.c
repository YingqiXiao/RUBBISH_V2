#include "bsp_motor.h"
#include "tim.h"
#include "stdbool.h"

motor_t motor[3] = {0};

void Motor_Control(uint8_t Motor_Flag,uint16_t Motor_PWM,bool Motor_State)
{
	switch(Motor_Flag)
	{
		case MOTOR1:
		{
			if(Motor_State == MOTOR_RUN)
			{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,Motor_PWM);
			}
			
			else if(Motor_State == MOTOR_STOP)
			{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
			}
		}
		break;
		
		case MOTOR2:
		{
			if(Motor_State == MOTOR_RUN)
			{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,Motor_PWM);
			}
			
			else if(Motor_State == MOTOR_STOP)
			{
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
			}
		}
		break;
		
		case MOTOR3:
		{
			if(Motor_State == MOTOR_RUN)
			{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
				__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,Motor_PWM);
			}
			
			else if(Motor_State == MOTOR_STOP)
			{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
			}
		}
		break;		
	}		
}
