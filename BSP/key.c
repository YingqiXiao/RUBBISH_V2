#include "key.h"

keys_t key[4]={0,0,0,0,0};

void Key_Read(void)
{	
	key[0].key_sta = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
	key[1].key_sta = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);
	key[2].key_sta = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
	key[3].key_sta = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8);
	
	for(int i = 0;i < 4;i++)
	{
		switch(key[i].judge_sta)
		{
			case 0:
			{
				if(key[i].key_sta == 0)
				{
					key[i].judge_sta = 1;
					key[i].key_time = 0;
				}
			}
			break;
			
			case 1:
			{
				if(key[i].key_sta == 0)
				{
					key[i].judge_sta = 2;
					
				}
				
				else key[i].judge_sta = 0;
			}
			break;
			
			case 2:
			{
				if(key[i].key_sta == 1)
				{
					key[i].judge_sta = 0;
					key[i].single_flag = 1;
					
					if(key[i].key_time < 70)
						key[i].single_flag = 1;							
				}
				
				else 
				{
					key[i].key_time++;
					if(key[i].key_time > 70)
						key[i].long_flag = 1;
										
				}
			}
			break;
		}
		
	}
}
	

