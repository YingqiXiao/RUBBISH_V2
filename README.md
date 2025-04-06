# RUBBISH_V2

第一天，尝试FREERTOS系统，目前已完成FREERTOS系统的配置并应用，满载警报广播使用SY6288芯片，使用串口3完成了，移植了省赛的dma串口代码，但没有测试，目前不知道能不能跑通，同时将之前while循环里的代码迁移到了freertos任务Uart_Task中，完成了舵机与电机的驱动代码，有点太晚了，明天再整理下关于GPIO的使用。

加入了硬件iic驱动eeprom和oled，同时移植了蓝桥杯的按键代码，省赛的传感器读取代码，目前仅测试了按键读取正常。

oled显示代码例程：

	char text[30];
	sprintf(text,"%d",a);
	OLED_ShowString(0,0,(uint8_t *)text,sizeof(text));

警报语音代码例程：

		//选择背景音乐2。(0：无背景音乐  1-15：背景音乐可选)
		//m[0~16]:0背景音乐为静音，16背景音乐音量最大
		//v[0~16]:0朗读音量为静音，16朗读音量最大
		//t[0~5]:0朗读语速最慢，5朗读语速最快
		//其他不常用功能请参考数据手册
		SYN_FrameInfo(0, "[v7][m1][t5]满载警报");

引脚功能查询

PB9 - MOTOR3_IN2

PB8 - KEY4

PB7 - EEPROM_SDA

PB6 - EEPROM_SCL

PB5 - KEY3

PB4 - KEY2

PB3 - KEY1

PA15 - SECOND_SENSOR

PA12 - FIRST_SENSOR

PA11 - HARM_SENSOR

PA10 - TONGXIN_RX

PA9 - TONGXIN_TX

PA8 - KITCHEN_SENSOR

PB15 - OTHER_SENSOR

PB14 - RECYCLE_SENSOR

PB13 - OLED_SDA

PB12 - OLED_SCL

PB11 - WARN_RX

PB10 - WARN_TX

PB1 - MOTOR3_IN1

PB0 - MOTOR2_IN2

PA7 - SERVO2_PWM

PA6 - SERVO1_PWM

PA5 - MOTOR2_IN1

PA4 - MOTOR1_IN2

PA3 - MOTOR1_IN1

PA2 - MOTOR3_PWM

PA1 - MOTOR2_PWM

PA0 - MOTOR1_PWM



***一定要注意写在uart.c中的这部分代码，不使能IDLE是无法进入USART1_IRQHandler的***

```
//下方为自己添加的代码
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE); //使能IDLE中断

//DMA接收函数，此句一定要加，不加接收不到第一次传进来的实数据，是空的，且此时接收到的数据长度为缓存器的数据长度
	HAL_UART_Receive_DMA(&huart1,rx_buffer,BUFFER_SIZE);
```

