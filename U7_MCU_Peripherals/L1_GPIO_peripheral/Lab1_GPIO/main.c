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

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdio.h>
#include<stdint.h>
#include<stdlib.h>

typedef volatile unsigned int vuint32_t;

//GPIOA registers
#define GPIOA_BASE 		0x40010800 //base address of Port A
#define GPIOA_CRL		*(vuint32_t*)(GPIOA_BASE + 0x00)
#define GPIOA_CRH 		*(vuint32_t*) (GPIOA_BASE+0x04)
#define GPIOA_ODR 		*(vuint32_t*) (GPIOA_BASE+0x0C)
#define GPIOA_IDR 		*(vuint32_t*) (GPIOA_BASE+0x08)

//GPIOB registers
#define GPIOB_BASE 		0x40010C00 //base address of Port B
#define GPIOB_CRL		*(vuint32_t*)(GPIOB_BASE + 0x00)
#define GPIOB_CRH 		*(vuint32_t*) (GPIOB_BASE+0x04)
#define GPIOB_ODR 		*(vuint32_t*) (GPIOB_BASE+0x0C)
#define GPIOB_IDR 		*(vuint32_t*) (GPIOB_BASE+0x08)

// RCC registers
#define RCC_BASE 		0x40021000 //base address of RCC
#define RCC_APB2ENR 	*(vuint32_t*) (RCC_BASE+0x18)
#define IOPAEN 			(1<<2)
#define IOPBEN 			(1<<3)


void GPIO_init(){

	//reset register values of Port A
	GPIOA_CRL = 0;
	GPIOA_CRH = 0;
	GPIOA_ODR = 0;

	//MODE: init GPIOA pin 1 as input(reset state)
	GPIOA_CRL &= ~(0b11<<4);
	//CNF: make PORTA pin 1 as floating input
	GPIOA_CRL |= (0b01<<6);

	//MODE: init GPIOB pin 1 as output with max speed = 10MHZ
	GPIOB_CRL |= (0b01<<4);
	//CNF: make PORTB pin 1 as push-pull output
	GPIOB_CRL &= ~(0b11<<6);

	/************************************************************/

	//MODE: init GPIOA pin 13 as input(reset state)
	GPIOA_CRH &= ~(0b11<<20);
	//CNF: make PORTA pin 13 as floating input
	GPIOA_CRH |= (0b01<<22);

	//MODE: init GPIOB pin 13 as output with max speed = 10MHZ
	GPIOB_CRH |= (0b01<<20);
	//CNF: make PORTB pin 13 as push-pull output
	GPIOB_CRH &= ~(0b11<<22);

}

void clock_init(){
	//enable ABP2 clock register
	//enable IO port A clock "IOPAEN"
	RCC_APB2ENR |= IOPAEN ;
	//enable IO port B clock "IOPBEN"
	RCC_APB2ENR |= IOPBEN ;
}

void WAIT_ms(uint32_t t){
	uint32_t i,j;
	for(i=0;i<t;i++){
		for(j=0;j<255;j++);
	}
}

int main(void)
{
	clock_init();
	GPIO_init();

    /* Loop forever */
	while(1){

		if(((GPIOA_IDR&(1<<1)) >>1)==0) 	//mask Port A pin 1 input register
		{
			GPIOB_ODR ^= 1 << 1; 	//toggle led on pin 1 PortB
			while(((GPIOA_IDR&(1<<1)) >>1)==0); //single pressing
		}

		if(((GPIOA_IDR&(1<<13)) >> 13)==1){ //mask Port A pin 13 input register
			GPIOB_ODR ^= 1 << 13; //"multi pressing" toggle led on pin 13 PortB
			WAIT_ms(3);	//delay
		}
	}
}


