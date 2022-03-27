/*
 * led.c
 *
 *  Created on: Mar 25, 2022
 *      Author: admin
 */

#include "led.h"


void LED_0(uint8_t a)
{
	if(a)
		HAL_GPIO_WritePin(GPIOF,LED0_Pin,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOF,LED0_Pin,GPIO_PIN_SET);
}

void LED_1(uint8_t a)
{
	if(a)
		HAL_GPIO_WritePin(GPIOF,LED1_Pin,GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOF,LED1_Pin,GPIO_PIN_SET);
}

void LED_Control()	//实现流水灯效果
{
	LED_0(1);
	LED_1(0);
	HAL_Delay(1000);
	LED_0(0);
	LED_1(1);
	HAL_Delay(1000);	//第二个延迟函数必须要有，否则LED0亮、LED1灭不起效果
}


