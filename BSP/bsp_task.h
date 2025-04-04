#ifndef _BSP_TASK_
#define _BSP_TASK_

#include "main.h"

#define RECYCLE 1
#define OTHER 2
#define KITCHEN 3
#define HARM 4

typedef struct{
	
 unsigned int Cast2_flag;
	
}cast_t;

extern cast_t cast[];

void Key_Task(void);
void Main_Task(void);
void Init_Task(void);
void Display_Task(void);
#endif
