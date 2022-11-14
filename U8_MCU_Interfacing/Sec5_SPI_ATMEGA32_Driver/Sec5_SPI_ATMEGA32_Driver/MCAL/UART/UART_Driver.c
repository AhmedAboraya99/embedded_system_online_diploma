/*
 * UART_Driver.c
 *
 * Created: 12/27/2021 7:21:19 AM
 *  Author: Ahmed Aboraya
 */ 

//-----------------------------
//Includes
//-----------------------------

#include "UART_Driver.h"



/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

void MCAL_USART_init(USART_TypeDef* USARTx, USART_Config_t * UART_Config){
	
	//Define USART Baud Rate Register
	Set_Pin(USARTx ->UBRRL,(unsigned char) UART_Config->BaudRate>>8);
	Set_Pin(USARTx ->UBRRL,(unsigned char) UART_Config->BaudRate);
	
	//Enable Sending/Receiving
	Set_Bitfield(USART->UCSRB.bits.TXEN);
	Set_Bitfield(USART->UCSRB.bits.RXEN);
	// Set Transmission Speed mode
	Set_Pin(USARTx->UCSRA.reg, UART_Config->USART_Speed);
	
	// The URSEL must be one when writing the UCSRC 
	Set_Bitfield(USARTx->UCSRC.bits.URSEL);	
	
	//define Data Bits using UCSZ2 in UCSRB & UCSZ1 UCSZ0 in UCSRC
	if(UART_Config->Payload_Length ==  USART_Payload_Length_5B||UART_Config->Payload_Length ==  USART_Payload_Length_6B
					||UART_Config->Payload_Length ==  USART_Payload_Length_7B||UART_Config->Payload_Length ==  USART_Payload_Length_8B )
	{
		Set_Pin(USARTx->UCSRC.reg, UART_Config->Payload_Length);
		Reset_Bitfield(USARTx->UCSRB.bits.UCSZ2);
			
	}
	else
		//case USART_Payload_Length_9B
	{
		Set_Pin(USARTx->UCSRC.reg, UART_Config->Payload_Length);
		Reset_Bitfield(USARTx->UCSRB.bits.UCSZ2);
	}
	
	// Set Parity bit type
	Set_Pin(USARTx->UCSRC.reg ,UART_Config->Parity);
	
	//Set Stop bit type 
	Set_Pin(USARTx->UCSRC.reg, UART_Config->StopBits);
	
	//Define USART Mode ( Synchronous - Asynchronous)
	Set_Pin(USARTx->UCSRA.reg, UART_Config->USART_Mode) ;
	// Enable/Disable interrupt 
	if(UART_Config->IRQ_Enable == USART_IRQ_Enable_NONE )
	{
		Set_Pin(USARTx->UCSRB.reg, UART_Config->IRQ_Enable);
		GP_USART_IRQ_CallBack = (void *)(0x0);
		Global_Interrupt_Disable();
	}
	else
	//case There is Interrupt
	{
		Set_Pin(USARTx->UCSRB.reg, UART_Config->IRQ_Enable);
		GP_USART_IRQ_CallBack = UART_Config -> P_IRQ_CallBack;
		Global_Interrupt_Enable();
	}
	
}
void MCAL_USART_DeInit(USART_TypeDef* USARTx)
{
	while(!(USARTx->UCSRA.bits.UDRE));
	
	Reset_Port(USARTx->UBRRL);
	Reset_Bitfield(USARTx->UCSRA.bits.MPCM);
	Reset_Bitfield(USARTx->UCSRA.bits.U2X);
	Reset_Bitfield(USARTx->UCSRA.bits.TXC);
	Reset_Port(USARTx->UCSRB.reg);
	USARTx->UCSRC.reg = 0x86;
	Reset_Port(USARTx->UBRRL);
	Reset_Port(USARTx->UBRRH.reg);
	
}
void MCAL_USART_send_data(USART_TypeDef* USARTx, uint16_t* Data, enum UART_Polling_Mechanism UART_Polling_EN){
	
	if(UART_Polling_EN){
		/* Wait for empty transmit buffer */
		while(!( USART->UCSRA.bits.UDRE));
	}
	if(USARTx->UCSRB.bits.UCSZ2){
		if(Get_Bit(*Data, 8)){
			Set_Bitfield(USARTx->UCSRB.bits.TXB8);	//set the ninth bit of data bits
		}else{
			Reset_Bitfield(USARTx->UCSRB.bits.TXB8);	//set the ninth bit of data bits
		}
	}
	USARTx->UDR =(uint8_t *) *Data;	//send data to I/O data register

}
uint16_t MCAL_USART_receive_data(USART_TypeDef* USARTx,enum UART_Polling_Mechanism UART_Polling_EN){
	uint16_t RXBuffer = 0 ;
	char Ninth_bit;
	if(UART_Polling_EN){
	/* Wait for data to be received */
	while( !(USART->UCSRA.bits.RXC));
	}
	RXBuffer = USARTx->UDR;
	/* Get status and 9th bit, then data */
	/* from buffer */
	if(USARTx->UCSRB.bits.UCSZ2){
		Ninth_bit = (USARTx->UCSRB.bits.RXB8);
		Set_Pin(RXBuffer, Ninth_bit<<8) ;	//get the ninth bit of data bits
	}
	/* Get and return received data from buffer */
	return RXBuffer;
}
void MCAL_USART_send_string(USART_TypeDef* USARTx, char *p_Data,enum UART_Polling_Mechanism UART_Polling_EN ){
	
	while(*p_Data != '\0'){
		/* Wait for empty transmit buffer */
		MCAL_USART_send_data(USARTx, *p_Data, UART_Polling_EN);	//send data to I/O data register			
		p_Data++;	//send Next Char
		}
	
}
char* MCAL_USART_receive_string(USART_TypeDef* USARTx,enum UART_Polling_Mechanism UART_Polling_EN){
	char data[50], i = 0;
	char* p_data = data;
	char get = 0;
	while(get != '!'){
		get = MCAL_USART_receive_data(USARTx, UART_Polling_EN);
		data[i] = get;
		i++;
	}

	return p_data ;
}




void __vector_15 (void) __attribute__((signal));
void __vector_15 (void){
	GP_USART_IRQ_CallBack();
}
void __vector_14 (void) __attribute__((signal));
void __vector_1 (void){
	GP_USART_IRQ_CallBack();
}
void __vector_13 (void) __attribute__((signal));
void __vector_13 (void){
	GP_USART_IRQ_CallBack();
}