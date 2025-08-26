#include "bsp_math.h"
#include <stdio.h>
#include <stdbool.h>

RampGenerator motor_step[3];

// һ�������ڶ�б�·�����״̬�ĸ���
void rampIterate(RampGenerator *ramp)
{
    if (ramp->isBusy)
    {

        if (ramp->currentValue < ramp->targetValue)
        {                                     // �����ǰֵС��Ŀ��ֵ
            ramp->currentValue += ramp->step; // ����ǰֵ
            if (ramp->currentValue > ramp->targetValue)
            { // ���ⳬ��
                ramp->currentValue = ramp->targetValue;
            }
        }
        else if (ramp->currentValue > ramp->targetValue)
        {                                     // �����ǰֵ����Ŀ��ֵ
            ramp->currentValue -= ramp->step; // ��С��ǰֵ
            if (ramp->currentValue < ramp->targetValue)
            { // ���ⳬ��
                ramp->currentValue = ramp->targetValue;
            }
        }

        // �ж��Ƿ�ﵽĿ��
        if (ramp->currentValue == ramp->targetValue)
        {
            ramp->isBusy = false; // �ﵽĿ�꣬���Ϊ��æµ
            printf("Ramp complete. Current Value: %f\n", ramp->currentValue);
        }
    }
}

// ��ʼ��б�·�����
void rampInit(RampGenerator *ramp, float startValue, float targetValue, float time, float cycleTime)
{
    ramp->currentValue = startValue;
    ramp->targetValue = targetValue;
    // ���㲽��ֵ��������Ҫע����ǣ�ȷ��б��ʱ�������ʱ�䶼��Ϊ�������������Ĵ���
    if (time != 0 && cycleTime != 0)
    {
        ramp->step = (targetValue - startValue) * (cycleTime / time);
    }
    else
    {
        ramp->step = 0; // �������������Ϊ0������Ƿ�����
    }
    ramp->isBusy = true; // ���Ϊæµ
}

