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
#include "string.h"

uint32_t Receive_time = 0;//��λ������ʶ������
uint8_t Motor_Number = 0;//������
uint32_t Noreceive_time = 0;//��λ��δʶ����������������⵽��
noreceive_cast_t Noreceive_Cast[1] = {0};//�����λ��δʶ����������������⵽��������ͰͶ�����
bool Lock_flag = 0;

/**
*   @brief  ����ڶ����������ж�������ͨ������λ��δ���ִ������
*   @param  ��������1~4
*   @return none
*   @author Aoyer
*/
void Noreceive_Task(uint8_t Cast_Numebr)
{
	switch(Cast_Numebr)
	{	
		case RECYCLE:
		{
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 1)
			{
				Servo_Control(SERVO1,90,SERVO270);
				Servo_Control(SERVO2,180,SERVO270);
			}
			
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 100)
				Servo_Control(SERVO2,270,SERVO270);
			
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 200)
				Servo_Control(SERVO1,0,SERVO270);
			
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 300)
			{				
				Uart_Flag.flag = 0;
				
				/*������ɺ󴫸���������ʱ״̬���������ʹ��������У�һ�����ʹ�ֹͣ�ȴ���ʱʱ�����*/
				sensor[FIRST_SENSOR].Sensor_flag = 4;
				sensor[SECOND_SENSOR].Sensor_flag = 4;
				
				Noreceive_time = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}
			
		}break;
		
		case OTHER:
		{	
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 1)
			{
				Servo_Control(SERVO1,270,SERVO270);
				Servo_Control(SERVO2,0,SERVO270);
			}
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 200)
				Servo_Control(SERVO2,270,SERVO270);
			
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 300)
				Servo_Control(SERVO1,0,SERVO270);			

			if(Noreceive_time == NORECEIVE_WAIT_TIME + 400)
			{
				Uart_Flag.flag = 0;
				
				/*������ɺ󴫸���������ʱ״̬���������ʹ��������У�һ�����ʹ�ֹͣ�ȴ���ʱʱ�����*/
				sensor[FIRST_SENSOR].Sensor_flag = 4;
				sensor[SECOND_SENSOR].Sensor_flag = 4;
				
				Noreceive_time = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}
			
		}break;
		
		case HARM:
		{
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 1)
			{
				Servo_Control(SERVO1,0,SERVO270);
				Servo_Control(SERVO2,180,SERVO270);
			}
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 100)
				Servo_Control(SERVO2,270,SERVO270);

			if(Noreceive_time == NORECEIVE_WAIT_TIME + 200)
			{
				Uart_Flag.flag = 0;
				
				/*������ɺ󴫸���������ʱ״̬���������ʹ��������У�һ�����ʹ�ֹͣ�ȴ���ʱʱ�����*/
				sensor[FIRST_SENSOR].Sensor_flag = 4;
				sensor[SECOND_SENSOR].Sensor_flag = 4;
				
				Noreceive_time = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}	
			
		}break;

		case KITCHEN:
		{
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 1)
			{
				Servo_Control(SERVO1,180,SERVO270);
				Servo_Control(SERVO2,90,SERVO270);
			}
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 100)
				Servo_Control(SERVO2,270,SERVO270);

			if(Noreceive_time == NORECEIVE_WAIT_TIME + 200)
			{
				Servo_Control(SERVO1,0,SERVO270);
			}
			
			if(Noreceive_time == NORECEIVE_WAIT_TIME + 300)
			{
				Uart_Flag.flag = 0;
				
				/*������ɺ󴫸���������ʱ״̬���������ʹ��������У�һ�����ʹ�ֹͣ�ȴ���ʱʱ�����*/
				sensor[FIRST_SENSOR].Sensor_flag = 4;
				sensor[SECOND_SENSOR].Sensor_flag = 4;
				
				Noreceive_time = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);				
			}
			
		}break;			
	}
}


/**
*   @brief  Ͷ������
*   @param  ��������1~4
*   @return none
*   @author Aoyer
*/
void Cast_Task(uint8_t Cast_Numebr)
{
	switch(Cast_Numebr)
	{	
		case RECYCLE:
		{
			
			if(Receive_time == 1)
			{
				Servo_Control(SERVO1,90,SERVO270);
				Servo_Control(SERVO2,180,SERVO270);
			}
			
			if(Receive_time == 100)
				Servo_Control(SERVO2,270,SERVO270);

			if(Receive_time == 200)
				Servo_Control(SERVO1,0,SERVO270);
			
			if(Receive_time == 300)
			{				
				Uart_Flag.flag = 0;
				
				/*������ɺ󴫸���������ʱ״̬���������ʹ��������У�һ�����ʹ�ֹͣ�ȴ���ʱʱ�����*/
				sensor[FIRST_SENSOR].Sensor_flag = 4;
				sensor[SECOND_SENSOR].Sensor_flag = 4;
				
				Receive_time = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}
			
		}break;

		case OTHER:
		{	
			if(Receive_time == 1)
			{
				Servo_Control(SERVO1,270,SERVO270);
				Servo_Control(SERVO2,0,SERVO270);
			}
			
			if(Receive_time == 200)
				Servo_Control(SERVO2,270,SERVO270);
			
			if(Receive_time == 300)
				Servo_Control(SERVO1,0,SERVO270);

			if(Receive_time == 400)
			{
				Uart_Flag.flag = 0;
				
				/*������ɺ󴫸���������ʱ״̬���������ʹ��������У�һ�����ʹ�ֹͣ�ȴ���ʱʱ�����*/
				sensor[FIRST_SENSOR].Sensor_flag = 4;
				sensor[SECOND_SENSOR].Sensor_flag = 4;
				
				Receive_time = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);		
			}
		}break;
		
		case HARM:
		{
			if(Receive_time == 1)
			{
				Servo_Control(SERVO1,0,SERVO270);
				Servo_Control(SERVO2,180,SERVO270);
				
			}
			
			if(Receive_time == 100)
			{
				Servo_Control(SERVO2,270,SERVO270);
			}
			
			if(Receive_time == 200)
			{				
				Uart_Flag.flag = 0;
				
				/*������ɺ󴫸���������ʱ״̬���������ʹ��������У�һ�����ʹ�ֹͣ�ȴ���ʱʱ�����*/
				sensor[FIRST_SENSOR].Sensor_flag = 4;
				sensor[SECOND_SENSOR].Sensor_flag = 4;
				
				Receive_time = 0;
				tx_buffer[0] = 0x08;
				tx_buffer[1] = 0x02;
				tx_buffer[2] = 0x09;
				DMA_Usart_Send(tx_buffer, tx_len);
				
			}
					
		}break;

		case KITCHEN:
		{
			if(Receive_time == 1)
			{
				Servo_Control(SERVO1,180,SERVO270);
				Servo_Control(SERVO2,90,SERVO270);
			}
			
			if(Receive_time == 100)
				Servo_Control(SERVO2,270,SERVO270);
			
			if(Receive_time == 200)
			{
				Servo_Control(SERVO1,0,SERVO270);
			}
			
			if(Receive_time == 300)
			{
				Uart_Flag.flag = 0;
				
				/*������ɺ󴫸���������ʱ״̬���������ʹ��������У�һ�����ʹ�ֹͣ�ȴ���ʱʱ�����*/
				sensor[FIRST_SENSOR].Sensor_flag = 4;
				sensor[SECOND_SENSOR].Sensor_flag = 4;
				
				Receive_time = 0;
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
	if(Key[2].Long_flag == 0)
	{
		char text[30];
		sprintf(text,"M1_SPEED:%d",motor[0].motor_speed);
		OLED_ShowString(0,0,(uint8_t *)text,sizeof(text));
		sprintf(text,"M2_SPEED:%d",motor[1].motor_speed);
		OLED_ShowString(0,1,(uint8_t *)text,sizeof(text));	
		sprintf(text,"M3_SPEED:%d",motor[2].motor_speed);
		OLED_ShowString(0,2,(uint8_t *)text,sizeof(text));
		switch(Noreceive_Cast[0].Noreceive_Number)
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
		
		if(Key[0].Judge_State == 2 || Key[1].Judge_State == 2 || Key[3].Judge_State == 2)
		{
			Lock_flag = UNLOCK;
			
		}
		
		if(Lock_flag == 1)
		{
			sprintf(text,"UNLOCK");
			OLED_ShowString(0,4,(uint8_t *)text,sizeof(text));				
		}
		else
		{
			sprintf(text,"LOCK");
			OLED_ShowString(0,4,(uint8_t *)text,sizeof(text));					
		}
	}
	
}

/**
*   @brief  ��������
*   @param  none
*   @return none
*   @author Aoyer
*/
void Key_Task(void)
{
	
	Key_Read();
	
	if(Key[2].Single_flag == 1)
	{	
		Motor_Number++;
		if(Motor_Number > 2)
		{
			Motor_Number = 0;
		}

		Key[2].Single_flag = 0;
	}
	
	switch(Motor_Number)
	{
		case MOTOR1:
		{
			if(Key[0].Single_flag == 1)
			{	
				OLED_Clear();
				motor[0].motor_speed += 1000;
				if(motor[0].motor_speed > 20000)
				{
					motor[0].motor_speed = 20000;
				}
			
				Key[0].Single_flag = 0;
			}
			
			if(Key[1].Single_flag == 1)
			{	
				OLED_Clear();
				if(motor[0].motor_speed != 0)
				{					
					motor[0].motor_speed -= 1000;
				}
	
				Key[1].Single_flag = 0;
			}
			
		}break;
		
		case MOTOR2:
		{	
			
			if(Key[0].Single_flag == 1)
			{   
				OLED_Clear();
				motor[1].motor_speed += 1000;
				if(motor[1].motor_speed > 20000)
				{
					motor[1].motor_speed = 20000;
				}

				Key[0].Single_flag = 0;
			}
			
			if(Key[1].Single_flag == 1)
			{	
				OLED_Clear();
				if(motor[1].motor_speed != 0)
				{
				motor[1].motor_speed -= 1000;
				}

				Key[1].Single_flag = 0;
			}
			
		}break;

		case MOTOR3:
		{	

			if(Key[0].Single_flag == 1)
			{
				OLED_Clear();
				motor[2].motor_speed += 1000;
				if(motor[2].motor_speed > 20000)
				{
					motor[2].motor_speed = 20000;
				}

				Key[0].Single_flag = 0;
			}
			
			if(Key[1].Single_flag == 1)
			{	
				OLED_Clear();
				if(motor[2].motor_speed != 0)
				{
				motor[2].motor_speed -= 1000;
				}

				Key[1].Single_flag = 0;
			}
			
		}break;
		
	}
	
	if(Key[3].Single_flag == 1)
	{	
		OLED_Clear();
		Noreceive_Cast[0].Noreceive_Number++;
		if(Noreceive_Cast[0].Noreceive_Number > 4)
		{
			Noreceive_Cast[0].Noreceive_Number = 1;
		}
		Key[3].Single_flag = 0;
	}
	
}


/**
*   @brief  ��������
*   @param  none
*   @return none
*   @author Aoyer
*/
void Control_Task(void)
{
	/*�յ���λ�����͵�ʶ����������*/
	if(Uart_Flag.flag != 0)
	{
		Receive_time++;
		/*�յ���λ����Ϣֱ��ֹͣ���ʹ�*/
		sensor[FIRST_SENSOR].Sensor_flag = 2;
		sensor[SECOND_SENSOR].Sensor_flag = 2;
		Cast_Task(Uart_Flag.flag);

	}

	/*δ�յ���λ�����͵�ʶ���������൫�����˴�����*/
	if(sensor[SECOND_SENSOR].Sensor_flag == 3 && Uart_Flag.flag == 0)
	{
		Noreceive_time++;
		belt_time = 0;
		if(Noreceive_time >= NORECEIVE_WAIT_TIME)//������������ȴ�һ��ʱ�䣬����ʱ��δ�յ���λ����Ϣ��ִ������
		{	
			Noreceive_Task(Noreceive_Cast[0].Noreceive_Number);
			
		}
	}
}

/**
*   @brief  ��ʼ������
*   @param  none
*   @return none
*   @author Aoyer
*/
void Init_Task(void)
{
	//��������־λ����
	sensor[FIRST_SENSOR].Sensor_flag = 0;
	sensor[SECOND_SENSOR].Sensor_flag = 0;
	//ͨ�Ŵ��ڱ�־λ����
	Uart_Flag.flag = 0;
	//eeprom��ȡ
	Noreceive_Cast[0].Noreceive_Number = ((eeprom_read(0) << 8) + eeprom_read(1));	
	motor[0].motor_speed = (eeprom_read(2) << 8) + eeprom_read(3);
	motor[1].motor_speed = (eeprom_read(4) << 8) + eeprom_read(5);
	motor[2].motor_speed = (eeprom_read(6) << 8) + eeprom_read(7);
	//�����ʼ��
	Motor_Control(MOTOR1,motor[0].motor_speed,MOTOR_RUN);
	Motor_Control(MOTOR2,motor[1].motor_speed,MOTOR_RUN);
	Motor_Control(MOTOR3,motor[2].motor_speed,MOTOR_RUN);
	//�����ʼ��
	Servo_Control(SERVO1,0,SERVO270);//ʶ��
	Servo_Control(SERVO2,270,SERVO270);//ʶ��
	//��ͨ�Ŵ���DMA����
	HAL_UART_Receive_DMA(&huart1,rx_buffer,BUFFER_SIZE);
}

/**
*   @brief  ����������
*   @param  none
*   @return none
*   @author Aoyer
*/
void Sensor_Task(void)
{
	Sensor_Read();
	Sensor_Judge();
}

/**
*   @brief  EEPROMд������
*   @param  none
*   @return none
*   @author Aoyer
*/
void eeprom_Task(void)
{
	if(Key[2].Long_flag == 1)
	{
		eeprom_write(0,Noreceive_Cast[0].Noreceive_Number >> 8);
		eeprom_write(1,Noreceive_Cast[0].Noreceive_Number & 0xff);
		eeprom_write(2,motor[0].motor_speed >> 8);
		eeprom_write(3,motor[0].motor_speed & 0xff);
		eeprom_write(4,motor[1].motor_speed >> 8);
		eeprom_write(5,motor[1].motor_speed & 0xff);
		eeprom_write(6,motor[2].motor_speed >> 8);
		eeprom_write(7,motor[2].motor_speed & 0xff);
		Key[2].Long_flag = 0;
		Lock_flag = LOCK;
	}		
}

void uart_Task(void)
{

		if(recv_end_flag == 1 && rx_len == DATA_REAL_LENGTH)  //������ɱ�־
		{
			Data_Resolve(&Uart_Flag);
			rx_len = 0;//�������
			recv_end_flag = 0;//������ս�����־λ
	//			for(uint8_t i=0;i<rx_len;i++)
	//				{
	//					rx_buffer[i]=0;//����ջ���
	//				}
				memset(rx_buffer,0,rx_len);
		}
		
		HAL_UART_Receive_DMA(&huart1,rx_buffer,BUFFER_SIZE);//���´�DMA����		
}
