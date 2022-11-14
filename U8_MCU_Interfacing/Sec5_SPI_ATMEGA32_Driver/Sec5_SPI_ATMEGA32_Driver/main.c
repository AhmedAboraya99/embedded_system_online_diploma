/*
 * Sec5_SPI_ATMEGA32_Driver.c
 *
 * Created: 8/17/2022 2:49:45 PM
 * Author : Ahmed Aboraya
 */ 
#define F_CPU	8000000UL
/* =====includes=====  */
#include <util/delay.h>
#include "SPI.h"
#include "lcd.h"
#include "UART_Driver.h"

/* =====global macros===== */
#define MCU_SPI_Master
//#define MCU_SPI_Slave

/* =====global variables===== */
char data;

/* =====ISR Sources ===== */


/* =====CallBack Functions===== */
void USART_CallBack(void)
{
	#ifdef MCU_SPI_Master
	 data =  MCAL_USART_receive_data(USART, UART_Polling_Disable);
	//MCAL_USART_send_data(USART, &data, UART_Polling_Enable);

	/* ========= Send Data To SPI =========== */

	/* Slave Selection (Low), to listen  */
	MCAL_DIO_WritePIN(SPI_DIO, DIO_PIN4,DIO_PIN_RESET);
	_delay_ms(10);
	/* Send data over SPI */
	MCAL_SPI_Send_Data(SPI, &data, SPI_Polling_Enable);
	
	/* Slave Selection (High) idle mode */
	MCAL_DIO_WritePIN(SPI_DIO, DIO_PIN4, DIO_PIN_SET);
	
	LCD_GOTO_XY(2,0);
	LCD_WRITE_CHAR(data);
	#endif
}
void SPI_Receive_CallBack(void){
		#ifdef MCU_SPI_Slave
		/* Receive data over SPI */
		
		MCAL_SPI_Recieve_Data(SPI, &data, SPI_Polling_Disable);
		
		LCD_GOTO_XY(2, 0);
		LCD_WRITE_CHAR(data);
		#endif
}
void USART_Config_init(){
	USART_Config_t* USART_Config;
	USART_Config->BaudRate = USART_BaudRate_9600;
	USART_Config->IRQ_Enable = USART_IRQ_Enable_RXCIE;
	USART_Config->P_IRQ_CallBack = USART_CallBack;
	USART_Config->Parity = USART_NONE_Parity;
	USART_Config->Payload_Length = USART_Payload_Length_8B;
	USART_Config->StopBits = USART_1_StopBit;
	USART_Config->USART_Mode = USART_MODE_ASYNC;
	USART_Config->USART_Speed = USART_NORMAL_SPEED;
	MCAL_USART_init(USART, USART_Config);
}

int main(void)
{
	
	data = 'A';
	uint8_t x = 0;
	LCD_INIT();
	/* Configuration of USART */
	USART_Config_init();


	/* Configuration of SPI */
	SPI_Config_t* SPI_Config;
	SPI_Config->BaudRate_Prescalar = BaudRate_Prescalar_Divide_BY_4;
	SPI_Config->Clock_Phase = Clock_Phase_First_Capture;
	SPI_Config->Clock_Polarity = Clock_Polarity_Idle_LOW;
	SPI_Config->Frame_Format = Frame_Format_MSB_FIRST;
	SPI_Config->Clock_Speed = Clock_Speed_Normal;
	
	
	/* Common Configuration */
	#ifdef MCU_SPI_Master
		SPI_Config->P_IRQ_CallBack = NULL;
		SPI_Config->SPI_Mode = SPI_Mode_MASTER;
		SPI_Config->IRQ_Enable = SPI_IRQ_ENABLE_NONE;
		
		MCAL_SPI_Init(SPI, SPI_Config);
		MCAL_SPI_DIO_Set_Pins(SPI);
		LCD_GOTO_XY(0,0);
		LCD_WRITE_STRING("MASTER");

	#endif

	#ifdef MCU_SPI_Slave
		SPI_Config->P_IRQ_CallBack = SPI_Receive_CallBack;
		SPI_Config->SPI_Mode = SPI_Mode_SLAVE;
		SPI_Config->IRQ_Enable = SPI_IRQ_ENABLE;
		MCAL_SPI_Init(SPI, SPI_Config);
		MCAL_SPI_DIO_Set_Pins(SPI);
		LCD_GOTO_XY(0,0);
		LCD_WRITE_STRING("SLAVE");
	#endif
	
	///* Set Idle High (Active High) */
	MCAL_DIO_WritePIN(SPI_DIO, DIO_PIN4, DIO_PIN_SET);

	/* Loop For Ever */
	while(1){

		#ifdef MCU_SPI_Master
			
			/* Slave Selection (Low), to listen  */
			MCAL_DIO_WritePIN(SPI_DIO, DIO_PIN4,DIO_PIN_RESET);
			/* Send data over SPI */
			_delay_ms(10);
			MCAL_SPI_Send_Data(SPI, &data, SPI_Polling_Enable);
			/* Slave Selection (High) idle mode */
			MCAL_DIO_WritePIN(SPI_DIO, DIO_PIN4, DIO_PIN_SET);
			
			LCD_GOTO_XY(1,12);
			LCD_WRITE_CHAR(data);
			(data)++;
			if (data == 'Z'+1){
				data = 'A';
			}
		#endif
		LCD_GOTO_XY(1, 9);
		LCD_WRITE_NUM(x);
		_delay_ms(1000);
		x++;
		if(x == 10){
			x = 0;
		}
	}
}

