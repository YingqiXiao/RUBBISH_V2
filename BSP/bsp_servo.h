#ifndef _BSP_SERVO_H_
#define _BSP_SERVO_H_

#include "main.h"
#include "stdbool.h"

#define SERVO1 1
#define SERVO2 2
#define SERVO180 0
#define SERVO270 1

void Servo_Control(uint8_t Servo_Flag,uint16_t Servo_Angle,uint8_t Servo_Class);

#endif
