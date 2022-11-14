/*
 * UART_Driver.h
 *
 * Created: 12/27/2021 7:21:37 AM
 *  Author: Ahmed Aboraya
 */ 

#include "ATMEGA32.h"
#include "DIO_Driver.h"

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_


//-----------------------------
//Configure structure for USART
//-----------------------------

typedef struct {
	uint8_t USART_Mode;   		//select USART Synchronous / ASynchronous mode.
	//@ref USART_Mode_define
	
	uint8_t USART_Speed;		//select USART Transmission Speed mode
	//@ref USART_Speed_define

	uint8_t BaudRate;			//configure USART communication baud rate
	//@ref BaudRate_define

	uint8_t Payload_Length;			//select transmitted or received data word length (8 or 9 bits)
	// @ref Payload_Length_define

	uint8_t Parity;					//select parity mode
	//@ref Parity_define

	uint8_t StopBits;					//select number of Stop Bits
	//@ref StopBits_define

	uint8_t IRQ_Enable;				//enable or disable USART IRQ TX/RX
	//@ref IRQ_Enable_define

	void (*P_IRQ_CallBack)(void);		//pointer to IRQ call back function which will be called once IRQ happened

}USART_Config_t;

enum UART_Polling_Mechanism{
	UART_Polling_Enable,
	UART_Polling_Disable
};

//-----------------------------
//Macros Configuration References
//-----------------------------

//UCSRC  – USART Control and Status Register C Modes

//@ref USART_Mode_define
// Bit 6 – UMSEL:?Mode Select
// This bit selects between Asynchronous and Synchronous mode of operation.
#define USART_MODE_ASYNC	(uint8_t) (0<<6)
#define USART_MODE_SYNC		(uint8_t) (1<<6)	

//@ref USART_Speed_define
//Bit 1 – U2X:?Double the USART Transmission Speed

#define USART_NORMAL_SPEED		(uint8_t) (0<<1)
#define USART_DOUBLE_SPEED		(uint8_t) (1<<1)

//@ref BaudRate_define
//UBRRL – USART Baud Rate Register Low
#define USART_BaudRate_2400				207
#define USART_BaudRate_4800				103
#define USART_BaudRate_9600				51
#define USART_BaudRate_14400			34
#define USART_BaudRate_19200			25
#define USART_BaudRate_28800			16
#define USART_BaudRate_38400			12
#define USART_BaudRate_57600			8
#define USART_BaudRate_76800			6
#define USART_BaudRate_115200			3
#define USART_BaudRate_230400			1
#define USART_BaudRate_250000			1


// @ref Payload_Length_define
//Bits 2:1 – UCSZn:?Character Size [n = 1:0]

#define USART_Payload_Length_5B			(uint8_t) (0)
#define USART_Payload_Length_6B			(uint8_t) (1<<1)
#define USART_Payload_Length_7B			(uint8_t) (2<<1)
#define USART_Payload_Length_8B			(uint8_t) (3<<1)
#define USART_Payload_Length_9B			(uint8_t) (3<<1)

//@ref Parity_define

// Bits 5:4 – UPMn:?Parity Mode [n = 1:0]
// UPM1 UPM0 ParityMode
// 0 0 Disabled
// 0 1 Reserved
// 1 0 Enabled, Even Parity
// 1 1 Enabled, Odd Parity

#define  USART_NONE_Parity				(uint8_t) (0x00<<4)
#define  USART_EVEN_Parity				(uint8_t) (1<<5)|(0<<4)
#define  USART_ODD_Parity				(uint8_t) (1<<10)|(1<<9)

//@ref StopBits_define
//Bit 3 – USBS:?Stop Bit Select
#define  USART_1_StopBit					(uint8_t) (0)
#define  USART_2_StopBit					(uint8_t) (1<<3)

//@ref IRQ_Enable_define
//Bit 7 RXCIE: RX Complete Interrupt Enable
//Bit 6 TXCIE:?TX Complete Interrupt Enable

#define  USART_IRQ_Enable_NONE			(uint8_t) (0)
#define  USART_IRQ_Enable_TXCIE			(uint8_t) (1<<6)
#define  USART_IRQ_Enable_RXCIE			(uint8_t) (1<<7)
#define  USART_IRQ_Enable_TXCIE_RXCIE	(uint8_t) (1<<6)|(1<<7)




//@ref USART_IRQ_EN_define
#define  USART_IRQ_ENABLE							0
#define  USART_IRQ_DISABLE							1

/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/

void (*GP_USART_IRQ_CallBack)(void);
//USART_Config_t *Global_USART_Config[2];

/*
* ==============================================================================
* 				  APIs Supported by "MCAL UART DRIVER"
* ==============================================================================
*/

void MCAL_USART_init(USART_TypeDef* USARTx,USART_Config_t* UART_Config);
void MCAL_USART_send_data(USART_TypeDef* USARTx, uint16_t* Data, enum UART_Polling_Mechanism UART_Polling_EN);
uint16_t MCAL_USART_receive_data(USART_TypeDef* USARTx, enum UART_Polling_Mechanism UART_Polling_EN);
void MCAL_USART_send_string(USART_TypeDef* USARTx, char* p_Data, enum UART_Polling_Mechanism UART_Polling_EN);
char* MCAL_USART_receive_string(USART_TypeDef* USARTx, enum UART_Polling_Mechanism UART_Polling_EN);

//USART Macros
#define MYUBRR	51
/* UCSRA */

//#define UDRE	5		//USART Data Register Empty
//#define TXC		6		//USART Transmit Complete
//#define RXC		7		//USART Receive Complete
//#define U2X     1
//#define MPCM    0
///* UCSRB */
//#define TXEN	3		//USART Transmit Enable
//#define RXEN	4		//USART Receive Disable
//#define UCSZ2   2
//#define RXB8    1
//#define TXB8    0
///* UCSRC */
//#define URSEL   7
#endif /* UART_DRIVER_H_ */