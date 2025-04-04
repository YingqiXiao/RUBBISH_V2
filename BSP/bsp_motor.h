#ifndef _BSP_MOTOR_H_
#define _BSP_MOTOR_H_

#include "main.h"
#include "stdbool.h"

#define MOTOR_RUN 1
#define MOTOR_STOP 0
#define MOTOR1 0
#define MOTOR2 1
#define MOTOR3 2

typedef struct{

unsigned int motor_speed;
	
}motor_t;

extern motor_t motor[];

void Motor_Control(uint8_t Motor_Flag,uint16_t Motor_PWM,bool Motor_State);

#endif
