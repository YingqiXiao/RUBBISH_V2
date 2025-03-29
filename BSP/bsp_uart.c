#include "bsp_uart.h"
#include "usart.h"

uint8_t err = 0;
Uart_Flag_t Uart_Flag;

/*
*********************************************************************************************************
* 函 数 名: DMA_Usart_Send
* 功能说明: 串口发送功能函数
* 形  参: buf，len
* 返 回 值: 无
*********************************************************************************************************
*/
void DMA_Usart_Send(uint8_t *buf,uint8_t len)//串口发送封装
{
 if(HAL_UART_Transmit_DMA(&huart1, buf,len)!= HAL_OK) //判断是否发送正常，如果出现异常则进入异常中断函数
  {
   Error_Handler();
  }

}

/*
*********************************************************************************************************
* 函 数 名: DMA_Usart1_Read
* 功能说明: 串口接收功能函数
* 形  参: Data,len
* 返 回 值: 无
*********************************************************************************************************
*/
void DMA_Usart1_Read(uint8_t *Data,uint8_t len)//串口接收封装
{
	HAL_UART_Receive_DMA(&huart1,Data,len);//重新打开DMA接收
}

void Data_Resolve(Uart_Flag_t *ptr)
{

		// Count
	uint8_t temp0 = 0;

	// Takes the cached array address
	uint8_t *rx_p = rx_buffer;
	
	// Find header 0xA5 with loop optimization
	while (*rx_p != 8 && temp0 <= 4)
	{
		temp0++;
		rx_p++;
	}
	
//	// Error flag
//	err = 0;

	// Determine the frame header and end of the frame
	if (rx_p[0] == 8 && rx_p[2] == 9)	
	{
		ptr->flag = rx_p[1];
	}
	
}
