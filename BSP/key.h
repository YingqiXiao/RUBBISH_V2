#ifndef _KEY_H_
#define _KEY_H_

#include "main.h"
#include "stdbool.h"

#define uchar unsigned char
#define uint unsigned int
#define LONG_PRESS_TIME 70 //判断按键是否长按时间，单位：10ms

/*按键判断结构体*/
typedef struct{
	uchar Judge_State;//是否可以进行按键判断
	bool Key_State;//按键状态
	bool Single_flag;//短按标志位
	bool Long_flag;//长按标志位
	uint Key_time;//按键按下时间记录
	
}keys_t;

extern keys_t Key[];

void Key_Read(void);

#endif
