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

//Includes
#include "STM32F103x6.h"
#include "STM32F103x6_EXTI_Driver.c"
#include "LCD.c"
#include "Keypad.c"

uint8_t IRQ_Flag;
//Generic Functions
void WAIT_ms(uint32_t t){
	uint32_t i,j;
	for(i=0;i<t;i++){
		for(j=0;j<255;j++);
	}
}

void clock_init(){
	//Enable ABP2 clock register
	//Enable IO port A clock
	 RCC_GPIOA_CLOCK_EN();

	//Enable IO port B clock
	 RCC_GPIOB_CLOCK_EN();
	//Enable Alternative IO port clock
	 RCC_AFIO_CLOCK_EN();
}
void IRQ9_CallBack(void){
	LCD_clear_screen();
	IRQ_Flag = 1;
	LCD_WRITE_STRING("Attention!! EXTI9 happened ");
	WAIT_ms(1000);

}


int main(void)
{
	clock_init();
	LCD_INIT();
	Keypad_init();
	WAIT_ms(50);
	//Configure an External interrupt request of line 9 on PORT B pin 9
	EXTI_pinConfig_t EXTI_Config;
	EXTI_Config.EXTI_Pin = EXTI9PB9 ;
	EXTI_Config.Trigger_state = EXTI_Trigger_RISING;
	EXTI_Config.P_IRQ_CallBack = IRQ9_CallBack;
	EXTI_Config.IRQ_EN = EXTI_IRQ_ENABLE;
	MCAL_EXTI_init(&EXTI_Config);

	IRQ_Flag = 1;
    /* Loop forever */
	while(1){
		if (IRQ_Flag){
			LCD_clear_screen();
			IRQ_Flag = 0;
		}
	}
}