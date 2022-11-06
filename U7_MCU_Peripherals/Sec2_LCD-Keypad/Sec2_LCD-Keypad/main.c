/*
 * Sec2_LCD-Keypad.c
 *
 * Created: 11/6/2022 11:53:25 AM
 * Author : Ahmed Aboraya
 */ 

#include <util/delay.h>
//-----------------------------
//Includes
//-----------------------------
#include "ATMEGA32.h"
#include "DIO_Driver.h"
#include "LCD.h"
#include "keypad.h"

#define F_CPU 1000000UL

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



int main(void)
{

	vuint32_t Num1 = 0, Num2 = 0, result=0 ;
	volatile char flag = 0;
	volatile char Operator;

	LCD_INIT();
	_delay_ms(50);

	LCD_clear_screen();
	LCD_WRITE_STRING("Calc is ready");
	Keypad_init();
	_delay_ms(20);
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
			if ((key_pressed == ('+' || '-' || '*' || '/'))&& (flag == 0))
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
