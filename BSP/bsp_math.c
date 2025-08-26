#include "bsp_math.h"
#include <stdio.h>
#include <stdbool.h>

RampGenerator motor_step[3];

// 一个周期内对斜坡发生器状态的更新
void rampIterate(RampGenerator *ramp)
{
    if (ramp->isBusy)
    {

        if (ramp->currentValue < ramp->targetValue)
        {                                     // 如果当前值小于目标值
            ramp->currentValue += ramp->step; // 增大当前值
            if (ramp->currentValue > ramp->targetValue)
            { // 避免超调
                ramp->currentValue = ramp->targetValue;
            }
        }
        else if (ramp->currentValue > ramp->targetValue)
        {                                     // 如果当前值大于目标值
            ramp->currentValue -= ramp->step; // 减小当前值
            if (ramp->currentValue < ramp->targetValue)
            { // 避免超调
                ramp->currentValue = ramp->targetValue;
            }
        }

        // 判断是否达到目标
        if (ramp->currentValue == ramp->targetValue)
        {
            ramp->isBusy = false; // 达到目标，标记为不忙碌
            printf("Ramp complete. Current Value: %f\n", ramp->currentValue);
        }
    }
}

// 初始化斜坡发生器
void rampInit(RampGenerator *ramp, float startValue, float targetValue, float time, float cycleTime)
{
    ramp->currentValue = startValue;
    ramp->targetValue = targetValue;
    // 计算步进值，这里需要注意的是，确保斜坡时间和周期时间都不为零来避免除以零的错误
    if (time != 0 && cycleTime != 0)
    {
        ramp->step = (targetValue - startValue) * (cycleTime / time);
    }
    else
    {
        ramp->step = 0; // 出错情况下设置为0，避免非法操作
    }
    ramp->isBusy = true; // 标记为忙碌
}

