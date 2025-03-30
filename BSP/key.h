#ifndef _KEY_H_
#define _KEY_H_

#include "main.h"
#include "stdbool.h"

#define uchar unsigned char
#define uint unsigned int

typedef struct{
	uchar judge_sta;
	bool key_sta;
	bool single_flag;
	bool long_flag;
	uint key_time;
	
}keys_t;

extern keys_t key[];

void Key_Read(void);

#endif
