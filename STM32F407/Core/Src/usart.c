/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "retarget.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
//uint8_t  USART1_RX_BUF[USART1_REC_LEN];	//接收缓冲，最大USART1_REC_LEN个字节，在usart.h使用宏定义为200
//uint16_t USART1_RX_STA = 0;		//接收状态标记
//uint8_t  USART1_NewData;
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart == &huart1)
//	{
//		printf("%c",USART1_NewData);
//		if((USART1_RX_STA & 0x8000) == 0)	//接收未完成
//		{
//			if(USART1_RX_STA&0x4000)	//接收到0x0d
//			{
//				if(USART1_NewData != 0x0a)
//					USART1_RX_STA = 0;	//接收错误，重新开始
//				else USART1_RX_STA |=0x8000;
//			}
//			else	//还没接收到0x0d
//			{
//				if(USART1_NewData == 0x0d)
//					USART1_RX_STA |= 0x4000;
//				else
//				{
//					USART1_RX_BUF[USART1_RX_STA&0x3FFF] = USART1_NewData;
//					USART1_RX_STA++;
//					if(USART1_RX_STA > (USART1_REC_LEN-1))
//						USART1_RX_STA = 0;	//接收数据错误，重新开始接收
//				}
//			}
//		}
//		HAL_UART_Receive_IT(&huart1, (uint8_t *)&USART1_NewData, 1);
//	}
//}
//


//void USART_TR()
//{
//	if(USART1_RX_STA&0x8000)
//	{
//		len=USART1_RX_STA&0x3fff;	//计算长度
//		printf("\r\nsend:\r\n");
//		HAL_UART_Transmit(&huart1,(uint8_t *)USART1_RX_BUF,len,1000);	//发送
//		while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=SET);		//等待发送完成
//		USART1_RX_STA=0;
//	}
//}


//void UART_LEDControl()
//{
//	if(USART1_RX_STA & 0xc000)
//	{
//		if(USART1_RX_BUF[0] == '1')
//		{
//			LED_0(1);
//			LED_1(0);
//		}
//		if(USART1_RX_BUF[0] == '0')
//		{
//			LED_0(0);
//			LED_1(1);
//		}
//		USART1_RX_STA = 0;
//	}
//}
/* USER CODE END 1 */
