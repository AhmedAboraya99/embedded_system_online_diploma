/*
 * UART_Driver.c
 *
 * Created: 12/27/2021 7:21:19 AM
 *  Author: Ahmed Aboraya
 */ 
#include "UART_Driver.h"

void MCAL_USART_init(){
	//Define USART Baud Rate Register Low byte
	SET_Pin(USART ->UBRRH,(unsigned char) MYUBRR>>8);		
	SET_Pin(USART ->UBRRL,(unsigned char) MYUBRR);	
	//Enable TX, RX
	SET_Bit(USART->UCSRB, TXEN);
	SET_Bit(USART->UCSRB, RXEN);
	
	//select 8 bits of data
	//Bit 2:1 – UCSZ1:0: Character Size
	//The UCSZ1:0 bits combined with the UCSZ2 bit in UCSRB sets the number of data bits
	SET_Bit(UCSRC, UCSZ0);
	SET_Bit(UCSRC, UCSZ1);
	RESET_Bit(USART->UCSRB, UCSZ2);
	//Asynchronous Operation mode
	RESET_Bit(UCSRC, UMSEL);

	//x2 Speed is disabled
	RESET_Bit(USART->UCSRA , U2X);
	

	// Bit 5:4 – UPM1:0: Parity Mode
	RESET_Bit(UCSRC, UPM0);
	RESET_Bit(UCSRC, UPM1);
	//Bit 3 – USBS: Stop Bit Select
	RESET_Bit(UCSRC, USBS);	
	/*Set UCSRC Mode*/
	SET_Bit(UCSRC, URSEL);

}
void MCAL_USART_send_char(char Data){
	/* Wait for empty transmit buffer */
	while(!GET_Bit( USART->UCSRA , UDRE));
		USART->UDR = Data;	//send data to I/O data register
}
char MCAL_USART_receive_char(){
	/* Wait for data to be received */
	while( !GET_Bit(USART->UCSRA, RXC));
	
	/* Get and return received data from buffer */
	return USART->UDR; 
}
void MCAL_USART_send_string(char *p_Data){
	
	while(*p_Data != '\0'){
		MCAL_USART_send_char(*p_Data);
		p_Data++;	//send Next Char
	}
}

char* MCAL_USART_receive_string(){
	char data[50], i = 0;
	char* p_data = data;
	char get = 0;
	while(get != '!'){
		
		get = MCAL_USART_receive_char();
		data[i] = get;
		i++;
	}

	return p_data ;
}
void MCAL_USART_Clear(){
	/* Wait for empty transmit buffer */
	while(!GET_Bit( USART->UCSRA , UDRE));
	RESET_Port(USART->UDR);
}