#ifndef _BSP_MATH_H
#define _BSP_MATH_H

#include "main.h"
#include "stdbool.h"

    // 定义一个用于表示斜坡发生器状态的结构体
typedef struct RampGenerator
{
    float currentValue; // 当前值
    float targetValue;  // 目标值
    float step;         // 每个控制周期应当改变的数值大小
    bool isBusy;        // 指示斜坡发生器是否正在调整中
} RampGenerator;

extern RampGenerator motor_step[3];


void rampIterate(RampGenerator *ramp);
void rampInit(RampGenerator *ramp, float startValue, float targetValue, float time, float cycleTime);

#endif

