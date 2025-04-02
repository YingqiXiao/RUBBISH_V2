#include "bsp_servo.h"
#include "tim.h"

void Servo_Control(uint8_t Servo_Flag,uint16_t Servo_Angle,uint8_t Servo_Class)
{
	float Servo_PWM = 0;
	switch(Servo_Class)
	{
		case SERVO180:
		{
			Servo_PWM = 50.0f + (float)Servo_Angle / 0.9f;
			
		}
		break;
		
		case SERVO270:
		{
			Servo_PWM = 50.0f + (float)Servo_Angle / 1.35f;
			
		}
		break;
	}
	
	switch(Servo_Flag)
	{
		case SERVO1:
		{
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,(uint16_t)Servo_PWM);
		}
		break;
		
		case SERVO2:
		{
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,(uint16_t)Servo_PWM);
		}		
		break;
	}
}
