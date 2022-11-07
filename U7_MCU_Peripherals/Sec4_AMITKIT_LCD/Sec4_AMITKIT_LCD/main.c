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


#define F_CPU 800000UL

typedef volatile unsigned int vuint32_t;





int main(void)
{


	LCD_INIT();
	_delay_ms(50);

	LCD_WRITE_STRING("LEARN IN DEPTH");




	/* Loop forever */
	while(1){

	}
}
