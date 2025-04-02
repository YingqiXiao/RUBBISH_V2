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

uint32_t time_flag = 0;//用于正常识别到垃圾
uint8_t motor_flag = 0;
uint32_t time2_flag = 0;//用于未识别到垃圾
uint8_t Cast2_flag = 1;//用于未识别到垃圾往哪个桶投

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
	sprintf(text,"MOTOR1_SPEED:%d",motor[0].motor_speed);
	OLED_ShowString(0,0,(uint8_t *)text,sizeof(text));
	sprintf(text,"MOTOR2_SPEED:%d",motor[1].motor_speed);
	OLED_ShowString(1,0,(uint8_t *)text,sizeof(text));	
	sprintf(text,"MOTOR3_SPEED:%d",motor[2].motor_speed);
	OLED_ShowString(2,0,(uint8_t *)text,sizeof(text));
	switch(Cast2_flag)
	{
		case RECYCLE:
			sprintf(text,"NOTARGE_CAST:RECYCLE");
		break;
		case OTHER:
			sprintf(text,"NOTARGE_CAST:OTHER");
		break;	
		case KITCHEN:
			sprintf(text,"NOTARGE_CAST:KITCHEN");
		break;
		case HARM:
			sprintf(text,"NOTARGE_CAST:KHARM");
		break;		
	}	
	OLED_ShowString(3,0,(uint8_t *)text,sizeof(text));	
}

void Key_Task(void)
{
	if(key[2].long_flag == 1)
	{
		uchar speed1_h = motor[0].motor_speed >> 8;
		uchar speed1_l = motor[0].motor_speed & 0xff;
		uchar speed2_h = motor[1].motor_speed >> 8;
		uchar speed2_l = motor[1].motor_speed & 0xff;
		uchar speed3_h = motor[2].motor_speed >> 8;
		uchar speed3_l = motor[2].motor_speed & 0xff;			
		eeprom_write(1,Cast2_flag);
		eeprom_write(2,speed1_h);
		eeprom_write(3,speed1_l);
		eeprom_write(4,speed2_h);
		eeprom_write(5,speed2_l);
		eeprom_write(6,speed3_h);
		eeprom_write(7,speed3_l);
		key[2].long_flag = 0;
	}
	
	if(key[3].single_flag == 1)
	{
		Cast2_flag++;
		if(Cast2_flag > 4)
		{
			Cast2_flag = 1;
		}
		key[3].single_flag = 0;
	}
	
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
				motor[0].motor_speed += 100;
				if(motor[0].motor_speed > 1000)
				{
					motor[0].motor_speed = 1000;
				}
				key[0].single_flag = 0;
			}
			
			if(key[1].single_flag == 1)
			{
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
				motor[1].motor_speed += 100;
				if(motor[1].motor_speed > 1000)
				{
					motor[1].motor_speed = 1000;
				}
				key[0].single_flag = 0;
			}
			
			if(key[0].single_flag == 1)
			{
				motor[1].motor_speed -= 100;
				if(motor[1].motor_speed != 0)
				{
				motor[1].motor_speed -= 100;
				}
				key[0].single_flag = 0;
			}
			
		}break;

		case MOTOR3:
		{
			if(key[0].single_flag == 1)
			{
				motor[2].motor_speed += 100;
				if(motor[2].motor_speed > 1000)
				{
					motor[2].motor_speed = 1000;
				}
				key[0].single_flag = 0;
			}
			
			if(key[0].single_flag == 1)
			{
				motor[2].motor_speed -= 100;
				if(motor[2].motor_speed != 0)
				{
				motor[2].motor_speed -= 100;
				}
				key[0].single_flag = 0;
			}
			
		}break;
		
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
		if(time2_flag == 500)
		{
			Cast_Task(Cast2_flag);
		}
	}
}

void Init_Task(void)
{
	sensor[FIRST_SENSOR].sensor_flag = 0;
	sensor[SECOND_SENSOR].sensor_flag = 0;
	Uart_Flag.flag = 0;
	Cast2_flag = eeprom_read(1);
	motor[0].motor_speed = (eeprom_read(2) << 8) + eeprom_read(3);
	motor[1].motor_speed = (eeprom_read(4) << 8) + eeprom_read(5);
	motor[2].motor_speed = (eeprom_read(6) << 8) + eeprom_read(7);
	Motor_Control(MOTOR1,motor[0].motor_speed,MOTOR_RUN);
	Motor_Control(MOTOR2,motor[1].motor_speed,MOTOR_RUN);
	Motor_Control(MOTOR3,motor[2].motor_speed,MOTOR_RUN);
	Servo_Control(SERVO1,90,SERVO180);//识别处
	Servo_Control(SERVO2,90,SERVO270);//识别处
	
}
