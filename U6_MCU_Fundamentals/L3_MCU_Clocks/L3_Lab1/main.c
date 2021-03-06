/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */


#include <stdio.h>
#include<stdint.h>
#include<stdlib.h>
typedef volatile unsigned int vuint32_t;
//GPIOA registers
#define GPIOA_BASE 0x40010800 //base address of Port A
#define GPIOA_CRH *(volatile uint32_t*) (GPIOA_BASE+0x04)
#define GPIOA_ODR *(volatile uint32_t*) (GPIOA_BASE+0x0C)

// RCC register
#define RCC_BASE 0x40021000 //base address of RCC
#define RCC_APB2ENR *(volatile uint32_t*) (RCC_BASE+0x18)

int main(void)
{
	//Enable IO port A clock
	RCC_APB2ENR = 1<<2 ;
	int i;
	//init GPIOA
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	while(1){
		//enable pin 13 in output data register "open LED"
		GPIOA_ODR |= 1<<13;
		for(i = 0;i<=5000;i++); //delay
		//disable pin 13 in output data register "close LED"
		GPIOA_ODR &= ~(1<<13);
		for(i = 0;i<=5000;i++);
	}
}
