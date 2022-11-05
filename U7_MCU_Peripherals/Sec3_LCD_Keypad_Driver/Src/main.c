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

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103X6.h"
#include "STM32f103X6_GPIO_Driver.c"
#include "lcd.c"
#include "keypad.c"
#include "7_segment.c"


typedef volatile unsigned int vuint32_t;


char get_num(char key_pressed){
	switch(key_pressed)
	{
		case '0': return 0; break;
		case '1': return 1; break;
		case '2': return 2; break;
		case '3': return 3; break;
		case '4': return 4; break;
		case '5': return 5; break;
		case '6': return 6; break;
		case '7': return 7; break;
		case '8': return 8; break;
		case '9': return 9; break;
	}

}

uint32_t perform_operation(uint32_t N1, uint32_t N2, char op){
	switch (op){
		case '+':
		return N1+N2;
		break;
		case '-':
		return N1-N2;
		break;
		case '*':
		return N1*N2;
		break;
		case '/':
		return N1/N2;
		break;
	}
}

void clock_init(void)
{
	//enable clock for GPIOA
	RCC_GPIOA_CLOCK_EN();
	//enable clock for GPIOB
	RCC_GPIOB_CLOCK_EN();
}

int main(void)
{

	vuint32_t Num1 = 0, Num2 = 0, result=0 ;
	volatile char flag = 0;
	volatile char Operator;

	clock_init();
	LCD_INIT();
	INIT_7_Segment();
	WAIT_ms(50);
	for ( int i = 0; i < 10; i++)
	{
		// Display current number on the 7 segment

		MCAL_GPIO_WritePort(Segments_PORT,Seg_Numbers[i]<<9);

		// We shifted by 8 as we used Pins from 8 to 15

		// Display current number on LCD
		LCD_WRITE_CHAR(LCD_Numbers[i]);


		// Delay so changes in numbers took effect in real time
		WAIT_ms(1000);  // 1 second delay
	}

	LCD_clear_screen();
	LCD_WRITE_STRING("Calcu is ready");
	Keypad_init();
	WAIT_ms(20);
	LCD_clear_screen();
	unsigned char key_pressed, num_pressed;


	/* Loop forever */
	while(1){

		key_pressed = Keypad_getkey();
		switch(key_pressed){
			case'A':
				break;
			case '?':
				LCD_clear_screen();
				Num1 = 0;
				Num2 = 0;
				break;
			default:

				//store Two Number to be calculated
				if (((key_pressed == '+') ||(key_pressed == '-') ||(key_pressed == '*' )||(key_pressed == '/'))&& (flag = 0))
				{
					LCD_WRITE_CHAR(key_pressed);
					flag = 1;
					Operator = key_pressed;
				}
				else{
					LCD_WRITE_CHAR(key_pressed);

					num_pressed = get_num(key_pressed);
					//produce two numbers from input keys
					if (flag == 0){
						Num1 = 10*Num1+(uint32_t)(num_pressed);

					}
					//if operator is pressed
					else if (flag == 1)
					{
						Num2 = 10*Num2+(uint32_t)(num_pressed);

					}
				}

				if (key_pressed == '=')
				{

					flag = 0;
					//decide which operation will be done
					result = perform_operation(Num1, Num2, Operator);
					LCD_WRITE_COMMAND(LCD_RETURN_HOME);
					LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW);
					LCD_WRITE_NUM(result); //display the result

				}
					break;

		}
	}
}