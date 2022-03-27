/*
 * key.c
 *
 *  Created on: Mar 25, 2022
 *      Author: admin
 */
#include "key.h"
#include "../../icode/led/led.h"
#include "../../core/inc/retarget.h"
#include "../../Core/Inc/usart.h"


uint8_t KEY_0(void)	//按键高电平有效，需要设置为输入下拉
{
	uint8_t a;
	a = 0;
	if(HAL_GPIO_ReadPin(GPIOE,KEY0_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(GPIOE,KEY0_Pin) == GPIO_PIN_SET)
		{
			a = 1;
		}
	}
	while(HAL_GPIO_ReadPin(GPIOE,KEY0_Pin) == GPIO_PIN_SET);	//如果用户不松手一直停在这个循环里，不会重复执行读读电平操作
	return a;
}

uint8_t KEY_UP(void)
{
	uint8_t a;
	a = 0;
	if(HAL_GPIO_ReadPin(GPIOA,KEYUP_Pin) == GPIO_PIN_SET)
	{
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(GPIOA,KEYUP_Pin) == GPIO_PIN_SET)
		{
			a = 1;
		}
	}
	while(HAL_GPIO_ReadPin(GPIOA,KEYUP_Pin) == GPIO_PIN_SET);
	return a;
}

void KEY_Control()
{
   if(KEY_0())
   {
	   LED_0(1);
	   LED_1(0);
   }
   if(KEY_UP())
   {
	   LED_0(0);
	   LED_1(1);
   }

}

void KEY_Printf()
{
	if(KEY_0())
	{
//		HAL_UART_Transmit(&huart1,(uint8_t*)&"KEY1\r\n",6,0xffff);
		printf("KEY1\r\n");
		LED_0(1);
		HAL_Delay(100);
		LED_0(0);
	}
	if(KEY_UP())
	{
		printf("KEY2\r\n");
		LED_1(1);
		HAL_Delay(100);
		LED_1(0);
	}
}
