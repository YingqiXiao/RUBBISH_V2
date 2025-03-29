#include "bsp_uart.h"
#include "usart.h"

uint8_t err = 0;
Uart_Flag_t Uart_Flag;

/*
*********************************************************************************************************
* �� �� ��: DMA_Usart_Send
* ����˵��: ���ڷ��͹��ܺ���
* ��  ��: buf��len
* �� �� ֵ: ��
*********************************************************************************************************
*/
void DMA_Usart_Send(uint8_t *buf,uint8_t len)//���ڷ��ͷ�װ
{
 if(HAL_UART_Transmit_DMA(&huart1, buf,len)!= HAL_OK) //�ж��Ƿ�����������������쳣������쳣�жϺ���
  {
   Error_Handler();
  }

}

/*
*********************************************************************************************************
* �� �� ��: DMA_Usart1_Read
* ����˵��: ���ڽ��չ��ܺ���
* ��  ��: Data,len
* �� �� ֵ: ��
*********************************************************************************************************
*/
void DMA_Usart1_Read(uint8_t *Data,uint8_t len)//���ڽ��շ�װ
{
	HAL_UART_Receive_DMA(&huart1,Data,len);//���´�DMA����
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
