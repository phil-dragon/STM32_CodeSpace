/*
 * uart.c
 *
 *  Created on: 2022年3月27日
 *      Author: admin
 */

#include "../../Core/Inc/retarget.h"
#include "uart.h"
#include "../../icode/led/led.h"
#include "stdio.h"

//unsigned char UART1_Rx_Buf[MAX_REC_LENGTH] = {0}; //USART1存储接收数据
//unsigned char UART1_Rx_flg = 0;                   //USART1接收完成标志
//unsigned int  UART1_Rx_cnt = 0;                   //USART1接受数据计数器
//unsigned char UART1_temp[REC_LENGTH] = {0};       //USART1接收数据缓存
//
////UART.c
///**
//  * @brief 串口中断回调函数
//  * @param 调用回调函数的串口
//  * @note  串口每次收到数据以后都会关闭中断，如需重复使用，必须再次开启
//  * @retval None
//  */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//  if(huart->Instance==USART1)
//  {
//    UART1_Rx_Buf[UART1_Rx_cnt] = UART1_temp[0];
//    UART1_Rx_cnt++;
//    if(0x0a == UART1_temp[0])
//    {
//      UART1_Rx_flg = 1;
//    }
//    HAL_UART_Receive_IT(&huart1,(uint8_t *)UART1_temp,REC_LENGTH);
//  }
//}
//
//void USART_RX()
//{
//	 if(UART1_Rx_flg)
//	    {
//	      HAL_UART_Transmit(&huart1,UART1_Rx_Buf,UART1_Rx_cnt,0x10);    //发送接收到的数据
//	      for(int i = 0;i<UART1_Rx_cnt;i++)
//	        UART1_Rx_Buf[i] = 0;
//	      UART1_Rx_cnt = 0;
//	      UART1_Rx_flg = 0;
//	    }
//}


uint8_t  USART1_RX_BUF[USART1_REC_LEN];	//接收缓冲，最大USART1_REC_LEN个字节，在usart.h使用宏定义为200
uint16_t USART1_RX_STA = 0;		//接收状态标记，bit15接收完成标志，bit14接收到0x0d（回车），bit13~0为接收到的有效字节数目
uint8_t  USART1_NewData;	//当前串口中断接收的1个字节数据的缓存

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)	//串口中断回调函数
{
	if(huart == &huart1)	//判断串口来源（串口1，USB转串口）
	{
		RetargetInit(&huart1);	//重定向初始化串口1，否者下一步printf找不到输出地址
		printf("%c",USART1_NewData);	//把接收到的数据以符号变量的形式发送回电脑（输出）
		if((USART1_RX_STA & 0x8000) == 0)	//接收未完成
		{
			if(USART1_RX_STA&0x4000)	//接收到0x0d
			{
				if(USART1_NewData != 0x0a)	//0x0a表示换行
					USART1_RX_STA = 0;	//接收错误，重新开始
				else USART1_RX_STA |=0x8000;
			}
			else	//还没接收到0x0d
			{
				if(USART1_NewData == 0x0d)
					USART1_RX_STA |= 0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0x3FFF] = USART1_NewData;	//将收到的数据放入数组
					USART1_RX_STA++;	//数据长度计数加一
					if(USART1_RX_STA > (USART1_REC_LEN-1))
						USART1_RX_STA = 0;	//接收数据错误，重新开始接收
				}
			}
		}
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&USART1_NewData, 1);	//再开启接收中断
	}
}


//void UART_LEDControl()
//{
//	if(USART1_RX_STA & 0xc000)
//	{
//		if(USART1_RX_BUF[0] == '1')
//		{
//			while(1)
//			{
//				LED_0(1);
//				LED_1(0);
//				HAL_Delay(100);
//				LED_0(0);
//				LED_1(1);
//				HAL_Delay(100);
//			}
//
//		}
//		if(USART1_RX_BUF[0] == '0')
//		{
//			while(1)
//			{
//				LED_0(1);
//				LED_1(0);
//				HAL_Delay(1000);
//				LED_0(0);
//				LED_1(1);
//				HAL_Delay(1000);
//			}
//		}
//		USART1_RX_STA = 0;
//	}
//}




