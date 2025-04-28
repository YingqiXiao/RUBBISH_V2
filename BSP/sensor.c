#include "sensor.h"
#include "stdbool.h"
#include "bsp_motor.h"
#include "usart.h"
#include "bsp_uart.h"
#include "syn6288.h"
#include "stdbool.h"

sensor_t sensor[6] = {0,0};
uint32_t Warn_time = 0;//满载警报，传感器被遮挡时间
uint32_t belt_time = 0;//二级传送带启动时一级传送带延时一段时间启动

/**
*   @brief  传感器状态读取任务
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
*   @brief  传感器判断任务
*   @param  none
*   @return none
*   @author Aoyer
*/
void Sensor_Judge(void)
{
	/*传感器判断*/
	for(uint8_t i = 4;i <= 5;i++)
	  {
		  /*传送带被阻挡反馈高电平*/
		  if(sensor[i].Sensor_State == 1)
		  {
			  if(sensor[i].Sensor_flag == 0 || sensor[i].Sensor_flag == 4)//0为初始状态，4表示传送带处于延时时间
			  {
				  sensor[i].Sensor_flag = 1;//进入过渡状态
				  belt_time = 0;//如果延时时间有垃圾落下此时把延时时间置零
			  }
		  }

		  /*垃圾落下后传送带恢复低电平*/
		  if(sensor[i].Sensor_State == 0 && sensor[i].Sensor_flag == 1)
		  {
			  sensor[i].Sensor_flag = 2;//此时要停下对应传送带
		  }
		  
	  }	
	
	 /*如果两个传感器都属于初始状态则传送带正常运行*/
	if(sensor[FIRST_SENSOR].Sensor_flag == 0 && sensor[SECOND_SENSOR].Sensor_flag == 0)
	{
		Motor_Control(MOTOR1,motor[0].motor_speed,MOTOR_RUN);
		Motor_Control(MOTOR2,motor[1].motor_speed,MOTOR_RUN);
		Motor_Control(MOTOR3,motor[2].motor_speed,MOTOR_RUN);
	}

	/*如果一级传感器处于要求制动状态则停下一级传送带*/
	if(sensor[FIRST_SENSOR].Sensor_flag == 2)
	{
		Motor_Control(MOTOR1,0,MOTOR_STOP);
		Motor_Control(MOTOR2,0,MOTOR_STOP);		
		sensor[FIRST_SENSOR].Sensor_flag = 3;//传感器进入等待状态，等待垃圾分类完成
	}

	/*如果一级传感器处于要求制动状态则停下一级传送*/
	if(sensor[SECOND_SENSOR].Sensor_flag == 2)
	{
		Motor_Control(MOTOR3,0,MOTOR_STOP);
		Motor_Control(MOTOR1,0,MOTOR_STOP);
		Motor_Control(MOTOR2,0,MOTOR_STOP);	
		sensor[SECOND_SENSOR].Sensor_flag = 3;//传感器进入等待状态，等待垃圾分类完成
	}

	/*如果传感器进入延时状态，则二级传送带运行，一级传送带停止*/
	if(sensor[FIRST_SENSOR].Sensor_flag == 4 && sensor[SECOND_SENSOR].Sensor_flag == 4)
	{
		Motor_Control(MOTOR3,motor[2].motor_speed,MOTOR_RUN);
		Motor_Control(MOTOR2,0,MOTOR_STOP);
		Motor_Control(MOTOR1,0,MOTOR_STOP);
		belt_time++;//传送带延时时间计时
	}

	/*如果延时时间到了则将两个传感器都恢复为初始状态，延时时间归零*/
	if(belt_time == BELT_DELAY_TIME)
	{
		sensor[FIRST_SENSOR].Sensor_flag = 0;
		sensor[SECOND_SENSOR].Sensor_flag = 0;
		belt_time = 0;
	}

	/*如果满载传感器检测到满载，则向上位机发送满载信号，同时语音播报*/
	for(uint8_t i = 0;i <= 3;i++)
	{
		if(sensor[i].Sensor_State == 0)
		{
			Warn_time++;
			
			/*语音播报*/
			if(Warn_time == WARN_TIME)
			{
				//选择背景音乐2。(0：无背景音乐  1-15：背景音乐可选)
				//m[0~16]:0背景音乐为静音，16背景音乐音量最大
				//v[0~16]:0朗读音量为静音，16朗读音量最大
				//t[0~5]:0朗读语速最慢，5朗读语速最快
				//其他不常用功能请参考数据手册	
				SYN_FrameInfo(0, "[v1][m1][t5]满载警报");						
			}

			/*向上位机发送满载信息*/
			if(Warn_time == WARN_TIME + 100)//语音播报时使用串口3，通信使用串口1，可能会冲突，延时一会
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
