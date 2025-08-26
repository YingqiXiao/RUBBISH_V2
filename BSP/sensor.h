#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "main.h"
#include "stdbool.h"

#define RECYCLE_SENSOR 0
#define OTHER_SENSOR 1
#define KITCHEN_SENSOR 2
#define HARM_SENSOR 3
#define FIRST_SENSOR 4
#define SECOND_SENSOR 5
#define WARN_TIME 600 //���ؾ������������ڵ�ʱ�䣬��λ��10ms

#define BELT_DELAY_TIME 100//���������һ�����ʹ��ȶ������ʹ���������ʱ�䣬��λ��10ms

#define SENSOR_INIT_STATE 0
#define SENSOR_TRAN_STATE 1
#define SENSOR_STOP_STATE 2.
#define SENSOR_WAIT_STATE 3
#define SENSOR_DELAY_STATE 4

/*�������жϽṹ��*/
typedef struct{

bool Sensor_State;//������״̬
uint8_t Sensor_flag;//��������־λ
	
}sensor_t;
extern sensor_t sensor[];
extern uint32_t belt_time;//�������ʹ�����ʱһ�����ʹ���ʱһ��ʱ������

void Sensor_Read(void);
void Sensor_Judge(void);
void warn_task(void);
	
#endif
