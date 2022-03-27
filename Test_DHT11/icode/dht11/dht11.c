/*
 * dht11.c
 *
 *  Created on: Mar 27, 2022
 *      Author: admin
 */

#include "dht11.h"
#include "../delay/delay.h"
#include "../../Core/Inc/gpio.h"

void DHT11_IO_OUT(void)	//端口变为输出
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}

void DHT11_IO_IN(void)	//端口变为输入
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DHT11_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
}

void DHT11_RST(void)	//DHT11端口复位，发出起始信号（IO发送）
{
	DHT11_IO_OUT();
	HAL_GPIO_WritePin(GPIOA, DHT11_Pin, GPIO_PIN_RESET);
	HAL_Delay(20);	//拉低至少20ms
	HAL_GPIO_WritePin(GPIOA, DHT11_Pin, GPIO_PIN_SET);
	delay_us(30);	//主机拉高20-40ms
}

uint8_t DHT11_Check(void)	//返回值为0表示通信成功，为1失败
{
	uint8_t retry = 0;
	DHT11_IO_IN();	//IO切换带输入状态
	while(HAL_GPIO_ReadPin(GPIOA, DHT11_Pin) && retry < 100)	//dht11拉低40-80ms
	{
		retry++;
		delay_us(1);
	}
	if(retry >= 100)
		return 1;
	else
		retry = 0;
	while(!HAL_GPIO_ReadPin(GPIOA, DHT11_Pin) && retry < 100)	//dht11拉高40-80ms
	{
		retry++;
		delay_us(1);
	}
	if(retry >= 100)
		return 1;
	else
		return 0;
}

uint8_t DHT11_ReadBit(void)	//从DHT11里读取一个位，返回值位0/1
{
	uint8_t retry = 0;
	while(HAL_GPIO_ReadPin(GPIOA, DHT11_Pin) && retry < 100)	//等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry = 0;
	while(!HAL_GPIO_ReadPin(GPIOA, DHT11_Pin) && retry < 100)	//等待变为高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);	//等待40us，判断高低电平，既数据1或0
	if(HAL_GPIO_ReadPin(GPIOA, DHT11_Pin))
		return 1;
	else
		return 0;
}

uint8_t DHT11_ReadByte(void)	//从DHT11里读取一个字节，返回读到的数据
{
	uint8_t i , dat;
	dat = 0;
	for(i = 0; i < 8; i++)
	{
		dat <<= 1;
		dat |= DHT11_ReadBit();
	}
	return dat;
}

uint8_t DHT11_Init(void)	//DHT11初始化
{
	DHT11_RST();	//DHT11端口复位，发出起始信号
	return DHT11_Check();	//等待DHT11回应
}

uint8_t DHT11_ReadData(uint8_t *h)	//读取一次数据
{
	uint8_t buf[5];
	uint8_t i;
	DHT11_RST();	//DHT11端口复位，发出起始信号
	if(DHT11_Check() == 0)	//等待DHT11响应
	{
		for(i = 0;i < 5;i++)
			buf[i] = DHT11_ReadByte();
		if((buf[0] + buf[1] +buf[2] +buf[3]) == buf[4])	//数据检验
		{
			*h = buf[0];	//将湿度值放入指针1
			h++;
			*h = buf[2];	//将温度值放入指针2
		}
	}
	else return 1;
	return 0;

}





