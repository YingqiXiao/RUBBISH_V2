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

bool Sensor_Read(uint8_t Sensor_Flag);

#endif
