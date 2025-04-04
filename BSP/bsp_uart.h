#ifndef _BSP_UART_H
#define _BSP_UART_H

#include "main.h"


typedef __packed struct
{	
	uint8_t flag;
	
} Uart_Flag_t;

extern Uart_Flag_t Uart_Flag;

void DMA_Usart_Send(uint8_t *buf,uint8_t len);//串口发送封装
void DMA_Usart1_Read(uint8_t *Data,uint8_t len);//串口接收封装
void Data_Resolve(Uart_Flag_t *ptr);

#endif
