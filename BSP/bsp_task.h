#ifndef _BSP_TASK_
#define _BSP_TASK_

#include "main.h"

#define RECYCLE 1
#define OTHER 2
#define KITCHEN 3
#define HARM 4
#define NORECEIVE_WAIT_TIME 500 //单位：10ms
#define LOCK 0
#define UNLOCK 1

typedef struct{
	
 unsigned int Noreceive_Number;
	
}noreceive_cast_t;

extern noreceive_cast_t Noreceive_Cast[];

void Key_Task(void);
void Control_Task(void);//多加一个l是为了与FREERTOS中的任务名避免重复
void Init_Task(void);
void Display_Task(void);
void Sensor_Task(void);
void eeprom_Task(void);
void uart_Task(void);

#endif
