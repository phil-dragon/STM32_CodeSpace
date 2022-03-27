/*
 * delay.c
 *
 *  Created on: Mar 27, 2022
 *      Author: admin
 */

#include "delay.h"
#include "../../Core/Inc/tim.h"

void delay_us(uint16_t us)
{
    uint16_t differ=0xffff-us-5;


    HAL_TIM_Base_Start(&htim6);
    __HAL_TIM_SetCounter(&htim6,differ);
    while(differ < 0xffff-5)
    {
        differ = __HAL_TIM_GetCounter(&htim6);
    }
    HAL_TIM_Base_Stop(&htim6);

}



