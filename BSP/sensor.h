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
#define WARN_TIME 1000 //满载警报传感器被遮挡时间，单位：10ms

/*传感器判断结构体*/
typedef struct{

bool Sensor_State;//传感器状态
uint8_t Sensor_flag;//传感器标志位
	
}sensor_t;
extern sensor_t sensor[];

void Sensor_Read(void);
void Sensor_Judge(void);

#endif
