#include "sensor.h"
#include "stdbool.h"
#include "bsp_motor.h"
#include "usart.h"
#include "bsp_uart.h"
#include "syn6288.h"
#include "stdbool.h"

sensor_t sensor[6] = {0,0};
uint32_t sensor_time = 0;

void Sensor_Read(void)
{
	sensor[RECYCLE_SENSOR].sensor_state = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14);
	sensor[OTHER_SENSOR].sensor_state = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15);
	sensor[KITCHEN_SENSOR].sensor_state = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
	sensor[HARM_SENSOR].sensor_state = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11);
	sensor[FIRST_SENSOR].sensor_state = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
	sensor[SECOND_SENSOR].sensor_state = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);

}

void Sensor_Judge(void)
{
	for(uint8_t i = 4;i <= 5;i++)
	  {
		  if(sensor[i].sensor_state == 0 && sensor[i].sensor_flag == 0)
		  {
			  sensor[i].sensor_flag = 1;
		  }
		  
		  if(sensor[i].sensor_state == 1 && sensor[i].sensor_flag == 1)
		  {
			  sensor[i].sensor_flag = 2;
		  }
		  
	  }

	if(sensor[FIRST_SENSOR].sensor_flag == 0 && sensor[SECOND_SENSOR].sensor_flag == 0)
	{
		Motor_Control(MOTOR1,motor[0].motor_speed,MOTOR_RUN);
		Motor_Control(MOTOR2,motor[1].motor_speed,MOTOR_RUN);
		Motor_Control(MOTOR3,motor[2].motor_speed,MOTOR_RUN);
	}
	  
	if(sensor[FIRST_SENSOR].sensor_flag == 2)
	{
		Motor_Control(MOTOR1,0,MOTOR_STOP);
		Motor_Control(MOTOR2,0,MOTOR_STOP);		
		sensor[FIRST_SENSOR].sensor_flag = 3;
	}
	
	if(sensor[FIRST_SENSOR].sensor_flag == 3)
	{
		if(sensor[SECOND_SENSOR].sensor_flag == 2)
		{
			Motor_Control(MOTOR1,600,MOTOR_RUN);
			Motor_Control(MOTOR2,400,MOTOR_RUN);
			sensor[FIRST_SENSOR].sensor_flag = 0;			
		}
	}
	
	if(sensor[SECOND_SENSOR].sensor_flag == 2)
	{
		Motor_Control(MOTOR3,0,MOTOR_STOP);
		sensor[SECOND_SENSOR].sensor_flag = 3;
	}

	for(uint8_t i = 0;i <= 3;i++)
	{
		if(sensor[i].sensor_state == 0)
		{
			sensor_time++;
			if(sensor_time == 1000)
			{
				//ѡ�񱳾�����2��(0���ޱ�������  1-15���������ֿ�ѡ)
				//m[0~16]:0��������Ϊ������16���������������
				//v[0~16]:0�ʶ�����Ϊ������16�ʶ��������
				//t[0~5]:0�ʶ�����������5�ʶ��������
				//���������ù�����ο������ֲ�	
				SYN_FrameInfo(0, "[v1][m1][t5]���ؾ���");						
			}
			
			if(sensor_time == 1100)
			{
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x0A;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);
				sensor_time = 0;
			}
			
		}
	}
}
