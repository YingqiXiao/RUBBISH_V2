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
#define WARN_TIME 600 //满载警报传感器被遮挡时间，单位：10ms

#define BELT_DELAY_TIME 100//分类结束后，一级传送带比二级传送带启动慢的时间，单位：10ms

#define SENSOR_INIT_STATE 0
#define SENSOR_TRAN_STATE 1
#define SENSOR_STOP_STATE 2.
#define SENSOR_WAIT_STATE 3
#define SENSOR_DELAY_STATE 4

/*传感器判断结构体*/
typedef struct{

bool Sensor_State;//传感器状态
uint8_t Sensor_flag;//传感器标志位
	
}sensor_t;
extern sensor_t sensor[];
extern uint32_t belt_time;//二级传送带启动时一级传送带延时一段时间启动

void Sensor_Read(void);
void Sensor_Judge(void);
void warn_task(void);
	
#endif
