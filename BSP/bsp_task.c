#include "bsp_task.h"
#include "key.h"
#include "bsp_motor.h"
#include "bsp_servo.h"
#include "bsp_uart.h"
#include "sensor.h"
#include "tim.h"
#include "eeprom.h"
#include "oled.h"
#include "stdio.h"
#include "usart.h"
#include "bsp_uart.h"
#include "sensor.h"

uint32_t time_flag = 0;//用于正常识别到垃圾
uint8_t motor_flag = 0;
uint32_t time2_flag = 0;//用于未识别到垃圾
uint8_t key_time = 0;
uint8_t main_time = 0;
uint8_t display_time = 0;
uint8_t sensor_time2 = 0;
uint8_t lock_flag = 0;
cast_t cast[1] = {0};

void Cast_Task2(uint8_t Cast_flag)
{
	switch(Cast_flag)
	{	
		case RECYCLE:
		{
			if(time2_flag == 501)
			{
			Servo_Control(SERVO1,0,SERVO270);
			Servo_Control(SERVO2,0,SERVO270);
			}
			if(time2_flag == 600)
			{
				Servo_Control(SERVO2,90,SERVO270);
			}
			if(time2_flag == 700)
			{
				Servo_Control(SERVO1,90,SERVO270);
			}
			if(time2_flag == 800)
			{				
				Uart_Flag.flag = 0;
				sensor[FIRST_SENSOR].sensor_flag = 0;
				sensor[SECOND_SENSOR].sensor_flag = 0;
				time2_flag = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}
		}break;
		
		case OTHER:
		{	
			if(time2_flag == 501)
			{
			Servo_Control(SERVO1,90,SERVO270);
			Servo_Control(SERVO2,0,SERVO270);
			}
			if(time2_flag == 600)
			{
				Servo_Control(SERVO2,90,SERVO270);
			}
			if(time2_flag == 700)
			{
				Uart_Flag.flag = 0;
				sensor[FIRST_SENSOR].sensor_flag = 0;
				sensor[SECOND_SENSOR].sensor_flag = 0;
				time2_flag = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}
		}break;
		
		case HARM:
		{
			if(time2_flag == 501)
			{
			Servo_Control(SERVO1,180,SERVO270);
			Servo_Control(SERVO2,180,SERVO270);
			}
			if(time2_flag == 600)
			{
				Servo_Control(SERVO2,90,SERVO270);
			}
			if(time2_flag == 700)
			{
				Servo_Control(SERVO1,90,SERVO270);
			}
			if(time2_flag == 800)
			{
				Uart_Flag.flag = 0;
				sensor[FIRST_SENSOR].sensor_flag = 0;
				sensor[SECOND_SENSOR].sensor_flag = 0;
				time2_flag = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}				
		}break;

		case KITCHEN:
		{
			if(time2_flag == 501)
			{
			Servo_Control(SERVO1,270,SERVO270);
			Servo_Control(SERVO2,270,SERVO270);
			}
			if(time2_flag == 600)
			{
				Servo_Control(SERVO2,180,SERVO270);
			}
			if(time2_flag == 700)
			{
				Servo_Control(SERVO2,90,SERVO270);
				Servo_Control(SERVO2,90,SERVO270);
			}
			if(time2_flag == 800)
			{
				Uart_Flag.flag = 0;
				sensor[FIRST_SENSOR].sensor_flag = 0;
				sensor[SECOND_SENSOR].sensor_flag = 0;
				time2_flag = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);				
			}				
		}break;			
	}
}

void Cast_Task(uint8_t Cast_flag)
{
	switch(Cast_flag)
	{	
		case RECYCLE:
		{
			if(time_flag == 1)
			{
			Servo_Control(SERVO1,0,SERVO270);
			Servo_Control(SERVO2,0,SERVO270);
			}
			if(time_flag == 100)
			{
				Servo_Control(SERVO2,90,SERVO270);
			}
			if(time_flag == 200)
			{
				Servo_Control(SERVO1,90,SERVO270);
			}
			if(time_flag == 300)
			{				
				Uart_Flag.flag = 0;
				sensor[FIRST_SENSOR].sensor_flag = 0;
				sensor[SECOND_SENSOR].sensor_flag = 0;
				time_flag = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}
		}break;
		
		case OTHER:
		{	
			if(time_flag == 1)
			{
			Servo_Control(SERVO1,90,SERVO270);
			Servo_Control(SERVO2,0,SERVO270);
			}
			if(time_flag == 100)
			{
				Servo_Control(SERVO2,90,SERVO270);
			}
			if(time_flag == 200)
			{
				Uart_Flag.flag = 0;
				sensor[FIRST_SENSOR].sensor_flag = 0;
				sensor[SECOND_SENSOR].sensor_flag = 0;
				time_flag = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}
		}break;
		
		case HARM:
		{
			if(time_flag == 1)
			{
			Servo_Control(SERVO1,180,SERVO270);
			Servo_Control(SERVO2,180,SERVO270);
			}
			if(time_flag == 100)
			{
				Servo_Control(SERVO2,90,SERVO270);
			}
			if(time_flag == 200)
			{
				Servo_Control(SERVO1,90,SERVO270);
			}
			if(time_flag == 300)
			{
				Uart_Flag.flag = 0;
				sensor[FIRST_SENSOR].sensor_flag = 0;
				sensor[SECOND_SENSOR].sensor_flag = 0;
				time_flag = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}				
		}break;

		case KITCHEN:
		{
			if(time_flag == 1)
			{
			Servo_Control(SERVO1,270,SERVO270);
			Servo_Control(SERVO2,270,SERVO270);
			}
			if(time_flag == 100)
			{
				Servo_Control(SERVO2,180,SERVO270);
			}
			if(time_flag == 200)
			{
				Servo_Control(SERVO2,90,SERVO270);
				Servo_Control(SERVO2,90,SERVO270);
			}
			if(time_flag == 300)
			{
				Uart_Flag.flag = 0;
				sensor[FIRST_SENSOR].sensor_flag = 0;
				sensor[SECOND_SENSOR].sensor_flag = 0;
				time_flag = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);				
			}				
		}break;			
	}
}


void Display_Task()
{
	char text[30];
	sprintf(text,"M1_SPEED:%d",motor[0].motor_speed);
	OLED_ShowString(0,0,(uint8_t *)text,sizeof(text));
	sprintf(text,"M2_SPEED:%d",motor[1].motor_speed);
	OLED_ShowString(0,1,(uint8_t *)text,sizeof(text));	
	sprintf(text,"M3_SPEED:%d",motor[2].motor_speed);
	OLED_ShowString(0,2,(uint8_t *)text,sizeof(text));
	switch(cast[0].Cast2_flag)
	{
		case RECYCLE:
		{
			sprintf(text,"CAST:RECYCLE");
			OLED_ShowString(0,3,(uint8_t *)text,sizeof(text));	
		}
		break;
		case OTHER:
		{
			sprintf(text,"CAST:OTHER");
			OLED_ShowString(0,3,(uint8_t *)text,sizeof(text));	
		}
		break;	
		case KITCHEN:
		{
			sprintf(text,"CAST:KITCHEN");
			OLED_ShowString(0,3,(uint8_t *)text,sizeof(text));	
		}
		break;
		case HARM:
		{
			sprintf(text,"CAST:HARM");
			OLED_ShowString(0,3,(uint8_t *)text,sizeof(text));	
		}
		break;		
	}
	
}

void Key_Task(void)
{
	
	if(key[2].single_flag == 1)
	{	
		motor_flag++;
		if(motor_flag > 2)
		{
			motor_flag = 0;
		}

		key[2].single_flag = 0;
	}
	
	switch(motor_flag)
	{
		case MOTOR1:
		{
			if(key[0].single_flag == 1)
			{	
				OLED_Clear();
				lock_flag = 0;
				motor[0].motor_speed += 100;
				if(motor[0].motor_speed > 1000)
				{
					motor[0].motor_speed = 1000;
				}
			
				key[0].single_flag = 0;
			}
			
			if(key[1].single_flag == 1)
			{	
				OLED_Clear();
				lock_flag = 0;
				if(motor[0].motor_speed != 0)
				{					
					motor[0].motor_speed -= 100;
				}
	
				key[1].single_flag = 0;
			}
			
		}break;
		
		case MOTOR2:
		{	
			
			if(key[0].single_flag == 1)
			{   
				OLED_Clear();
				lock_flag = 0;
				motor[1].motor_speed += 100;
				if(motor[1].motor_speed > 1000)
				{
					motor[1].motor_speed = 1000;
				}

				key[0].single_flag = 0;
			}
			
			if(key[1].single_flag == 1)
			{	
				OLED_Clear();
				lock_flag = 0;
				if(motor[1].motor_speed != 0)
				{
				motor[1].motor_speed -= 100;
				}

				key[1].single_flag = 0;
			}
			
		}break;

		case MOTOR3:
		{	

			if(key[0].single_flag == 1)
			{
				OLED_Clear();
				lock_flag = 0;
				motor[2].motor_speed += 100;
				if(motor[2].motor_speed > 1000)
				{
					motor[2].motor_speed = 1000;
				}

				key[0].single_flag = 0;
			}
			
			if(key[1].single_flag == 1)
			{	
				OLED_Clear();
				lock_flag = 0;
				if(motor[2].motor_speed != 0)
				{
				motor[2].motor_speed -= 100;
				}

				key[1].single_flag = 0;
			}
			
		}break;
		
	}
	
	if(key[3].single_flag == 1)
	{	
		OLED_Clear();
		cast[0].Cast2_flag++;
		if(cast[0].Cast2_flag > 4)
		{
			cast[0].Cast2_flag = 1;
		}
		key[3].single_flag = 0;
	}
	
}

void Main_Task(void)
{		
	if(Uart_Flag.flag != 0)
	{
		time_flag++;
		Cast_Task(Uart_Flag.flag);

	}

	if(sensor[SECOND_SENSOR].sensor_flag == 3 && Uart_Flag.flag == 0)
	{
		time2_flag++;
		if(time2_flag >= 500)
		{	
			Cast_Task2(cast[0].Cast2_flag);
			
		}
	}
}

void Init_Task(void)
{
	sensor[FIRST_SENSOR].sensor_flag = 0;
	sensor[SECOND_SENSOR].sensor_flag = 0;
	Uart_Flag.flag = 0;
	cast[0].Cast2_flag = ((eeprom_read(0) << 8) + eeprom_read(1));	
	motor[0].motor_speed = (eeprom_read(2) << 8) + eeprom_read(3);
	motor[1].motor_speed = (eeprom_read(4) << 8) + eeprom_read(5);
	motor[2].motor_speed = (eeprom_read(6) << 8) + eeprom_read(7);
	
	Motor_Control(MOTOR1,motor[0].motor_speed,MOTOR_RUN);
	Motor_Control(MOTOR2,motor[1].motor_speed,MOTOR_RUN);
	Motor_Control(MOTOR3,motor[2].motor_speed,MOTOR_RUN);
	Servo_Control(SERVO1,90,SERVO180);//识别处
	Servo_Control(SERVO2,90,SERVO270);//识别处
	HAL_UART_Receive_DMA(&huart1,rx_buffer,BUFFER_SIZE);
}

