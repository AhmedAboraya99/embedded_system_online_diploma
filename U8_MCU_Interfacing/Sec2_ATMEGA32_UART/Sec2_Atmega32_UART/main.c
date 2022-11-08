/*
 * main.c
 *
 * Created: 12/27/2021 7:16:01 AM
 *  Author: Ahmed Aboraya
 */ 
//-----------------------------
//Includes : Header Files
//-----------------------------

#include "DIO_Driver.h"
#include "UART_Driver.h"
#include "lcd.h"

#define F_CPU 800000UL

int main(void)
{
 	char *data;
 	LCD_INIT();
	_delay_ms(50);
 	MCAL_USART_init();
	 
	LCD_WRITE_STRING("welcome");
	
 	MCAL_USART_send_char('A');
 	MCAL_USART_send_char('H');
	MCAL_USART_send_char('M');
	MCAL_USART_send_char('E');
	MCAL_USART_send_char('D');	
	MCAL_USART_send_char(' ');	

 	MCAL_USART_send_string("Who?");
	
 	while(1)
 	{
	data=MCAL_USART_receive_string();
	LCD_clear_screen();
	LCD_WRITE_STRING(data);
 	}
}