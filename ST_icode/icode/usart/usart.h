/*
 * usart.h
 *
 *  Created on: Mar 25, 2022
 *      Author: admin
 */

#ifndef USART_USART_H_
#define USART_USART_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "../../core/inc/usart.h"
#include "../../icode/led/led.h"


#define USART1_REC_LEN 200


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void UART_LEDControl();

#endif /* USART_USART_H_ */


