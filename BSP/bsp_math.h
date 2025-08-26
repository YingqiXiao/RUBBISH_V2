#ifndef _BSP_MATH_H
#define _BSP_MATH_H

#include "main.h"
#include "stdbool.h"

    // ����һ�����ڱ�ʾб�·�����״̬�Ľṹ��
typedef struct RampGenerator
{
    float currentValue; // ��ǰֵ
    float targetValue;  // Ŀ��ֵ
    float step;         // ÿ����������Ӧ���ı����ֵ��С
    bool isBusy;        // ָʾб�·������Ƿ����ڵ�����
} RampGenerator;

extern RampGenerator motor_step[3];


void rampIterate(RampGenerator *ramp);
void rampInit(RampGenerator *ramp, float startValue, float targetValue, float time, float cycleTime);

#endif

