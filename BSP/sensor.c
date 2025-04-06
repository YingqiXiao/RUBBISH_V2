#include "sensor.h"
#include "stdbool.h"
#include "bsp_motor.h"
#include "usart.h"
#include "bsp_uart.h"
#include "syn6288.h"
#include "stdbool.h"

sensor_t sensor[6] = {0,0};
uint32_t Warn_time = 0;//���ؾ��������������ڵ�ʱ��

/**
*   @brief  ������״̬��ȡ����
*   @param  none
*   @return none
*   @author Aoyer
*/
void Sensor_Read(void)
{
	sensor[RECYCLE_SENSOR].Sensor_State = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14);
	sensor[OTHER_SENSOR].Sensor_State = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15);
	sensor[KITCHEN_SENSOR].Sensor_State = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
	sensor[HARM_SENSOR].Sensor_State = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11);
	sensor[FIRST_SENSOR].Sensor_State = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
	sensor[SECOND_SENSOR].Sensor_State = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);

}

/**
*   @brief  �������ж�����
*   @param  none
*   @return none
*   @author Aoyer
*/
void Sensor_Judge(void)
{
	for(uint8_t i = 4;i <= 5;i++)
	  {
		  if(sensor[i].Sensor_State == 0 && sensor[i].Sensor_flag == 0)
		  {
			  sensor[i].Sensor_flag = 1;
		  }
		  
		  if(sensor[i].Sensor_State == 1 && sensor[i].Sensor_flag == 1)
		  {
			  sensor[i].Sensor_flag = 2;
		  }
		  
	  }

	if(sensor[FIRST_SENSOR].Sensor_flag == 0 && sensor[SECOND_SENSOR].Sensor_flag == 0)
	{
		Motor_Control(MOTOR1,motor[0].motor_speed,MOTOR_RUN);
		Motor_Control(MOTOR2,motor[1].motor_speed,MOTOR_RUN);
		Motor_Control(MOTOR3,motor[2].motor_speed,MOTOR_RUN);
	}
	  
	if(sensor[FIRST_SENSOR].Sensor_flag == 2)
	{
		Motor_Control(MOTOR1,0,MOTOR_STOP);
		Motor_Control(MOTOR2,0,MOTOR_STOP);		
		sensor[FIRST_SENSOR].Sensor_flag = 3;
	}
	
	if(sensor[FIRST_SENSOR].Sensor_flag == 3)
	{
		if(sensor[SECOND_SENSOR].Sensor_flag == 2)
		{
			Motor_Control(MOTOR1,600,MOTOR_RUN);
			Motor_Control(MOTOR2,400,MOTOR_RUN);
			sensor[FIRST_SENSOR].Sensor_flag = 0;			
		}
	}
	
	if(sensor[SECOND_SENSOR].Sensor_flag == 2)
	{
		Motor_Control(MOTOR3,0,MOTOR_STOP);
		sensor[SECOND_SENSOR].Sensor_flag = 3;
	}

	for(uint8_t i = 0;i <= 3;i++)
	{
		if(sensor[i].Sensor_State == 0)
		{
			Warn_time++;
			
			/*��������*/
			if(Warn_time == WARN_TIME)
			{
				//ѡ�񱳾�����2��(0���ޱ�������  1-15���������ֿ�ѡ)
				//m[0~16]:0��������Ϊ������16���������������
				//v[0~16]:0�ʶ�����Ϊ������16�ʶ��������
				//t[0~5]:0�ʶ�����������5�ʶ��������
				//���������ù�����ο������ֲ�	
				SYN_FrameInfo(0, "[v1][m1][t5]���ؾ���");						
			}

			/*����λ������������Ϣ*/
			if(Warn_time == WARN_TIME + 100)//��������ʱʹ�ô���3��ͨ��ʹ�ô���1�����ܻ��ͻ����ʱһ��
			{
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x0A;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);
				Warn_time = 0;
			}
			
		}
	}
}
