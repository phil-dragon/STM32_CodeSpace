/*
 * usart.c
 *
 *  Created on: Mar 25, 2022
 *      Author: admin
 */

#include "usart.h"
#include "../../core/inc/retarget.h"
#include "stdio.h"

uint8_t  USART1_RX_BUF[USART1_REC_LEN];
uint16_t USART1_RX_STA = 0;
uint8_t  USART1_NewData;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		printf("%c",USART1_NewData);
		if(USART1_RX_STA & 0x8000 == 0)
		{
			if(USART1_RX_STA&0x4000)
			{
				if(USART1_NewData != 0x0a)
					USART1_RX_STA = 0;
				else USART1_RX_STA |=0x8000;
			}
			else
			{
				if(USART1_NewData == 0x0d)
					USART1_RX_STA |= 0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0x3FFF] = USART1_NewData;
					USART1_RX_STA++;
					if(USART1_RX_STA > (USART1_REC_LEN-1))
						USART1_RX_STA = 0;
				}
			}
		}
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&USART1_NewData, 1);
	}
}

void UART_LEDControl()
{
	if(USART1_RX_STA & 0xc000)
	{
		if(USART1_RX_BUF[0] == '1')
		{
			LED_0(1);
			LED_1(0);
		}
		if(USART1_RX_BUF[0] == '0')
		{
			LED_0(0);
			LED_1(1);
		}
		USART1_RX_STA = 0;
	}
}

