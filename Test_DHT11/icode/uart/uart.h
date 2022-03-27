/*
 * uart.h
 *
 *  Created on: 2022年3月27日
 *      Author: admin
 */

#ifndef UART_UART_H_
#define UART_UART_H_



#include "stm32f4xx_hal.h"
#include "retarget.h"
#include "../../Core/Inc/usart.h"
#include "main.h"

#define USART1_REC_LEN  1
#define MAX_REC_LENGTH  1024


//extern unsigned char UART1_Rx_Buf[MAX_REC_LENGTH];
//extern unsigned char UART1_Rx_flg ;
//extern unsigned int  UART1_Rx_cnt ;
//extern unsigned char UART1_temp[REC_LENGTH];

extern uint8_t  USART1_RX_BUF[USART1_REC_LEN];	//接收缓冲，最大USART1_REC_LEN个字节，在usart.h使用宏定义为200
extern uint16_t USART1_RX_STA ;		//接收状态标记
extern uint8_t  USART1_NewData;

void MX_USART1_UART_Init(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
//void UART_LEDControl();
//void USART_RX();
//void UART_LEDControl();

#endif /* UART_UART_H_ */


