#include "key.h"

keys_t Key[4]={0,0,0,0,0};

void Key_Read(void)
{	
	Key[0].Key_State = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3);
	Key[1].Key_State = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);
	Key[2].Key_State = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
	Key[3].Key_State = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8);
	
	for(int i = 0;i < 4;i++)
	{
		switch(Key[i].Judge_State)
		{
			case 0:
			{
				if(Key[i].Key_State == 0)
				{
					Key[i].Judge_State = 1;
				}
			}
			break;
			
			case 1:
			{
				if(Key[i].Key_State == 0)
				{
					Key[i].Judge_State = 2;
					
				}
				
				else Key[i].Judge_State = 0;
			}
			break;
			
			case 2:
			{
				if(Key[i].Key_State == 1)
				{
					Key[i].Judge_State = 0;
					
					if(Key[i].Key_time >= LONG_PRESS_TIME)
						Key[i].Long_flag = 1;
					
					if(Key[i].Key_time < LONG_PRESS_TIME)
						Key[i].Single_flag = 1;
					
					

					Key[i].Key_time = 0;
						
				}
				
				else 
				{
					Key[i].Key_time++;
						
				}
			}
			break;
		}
		
	}
}
	

