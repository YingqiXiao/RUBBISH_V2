#ifndef _KEY_H_
#define _KEY_H_

#include "main.h"
#include "stdbool.h"

#define uchar unsigned char
#define uint unsigned int
#define LONG_PRESS_TIME 70 //�жϰ����Ƿ񳤰�ʱ�䣬��λ��10ms

/*�����жϽṹ��*/
typedef struct{
	uchar Judge_State;//�Ƿ���Խ��а����ж�
	bool Key_State;//����״̬
	bool Single_flag;//�̰���־λ
	bool Long_flag;//������־λ
	uint Key_time;//��������ʱ���¼
	
}keys_t;

extern keys_t Key[];

void Key_Read(void);

#endif
