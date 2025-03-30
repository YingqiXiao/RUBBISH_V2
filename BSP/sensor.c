#include "sensor.h"
#include "stdbool.h"

bool Sensor_Read(uint8_t Sensor_Flag)
{
	bool Sensor_State = 0;
	switch(Sensor_Flag)
	{
		case RECYCLE_SENSOR:
			Sensor_State = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14);
		break;
		case OTHER_SENSOR:
			Sensor_State = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15);
		break;
		case KITCHEN_SENSOR:
			Sensor_State = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
		break;
		case HARM_SENSOR:
			Sensor_State = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11);
		break;
		case FIRST_SENSOR:
			Sensor_State = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
		break;
		case SECOND_SENSOR:
			Sensor_State = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);
		break;	
	}
	return Sensor_State;
}
