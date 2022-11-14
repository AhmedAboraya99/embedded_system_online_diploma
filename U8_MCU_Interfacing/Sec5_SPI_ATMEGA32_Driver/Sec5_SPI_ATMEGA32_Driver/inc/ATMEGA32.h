#ifndef _ATMEGA32_H_
#define _ATMEGA32_H_

//-----------------------------
//Includes
//-----------------------------
#include <stdlib.h>
#include <stdint.h>

#include "Bit_Math.h"

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define Flash_Memory_Base 				0x00000000UL
#define	SRAM_Base						0x00000060UL
#define IO_Base 						0x00000020UL



//-----------------------------
//Base addresses for IO Peripherals
//-----------------------------
//DIO

//0x0000 0030 - 0x0000 0032 DIO Port D
//0x0000 0033 - 0x0000 0035 DIO Port C
//0x0000 0036 - 0x0000 0038 DIO Port B
//0x0000 0039 - 0x0000 003B DIO Port A


#define DIOA_Base		(IO_Base+0x19UL)
#define DIOB_Base		(IO_Base+0x16UL)
#define DIOC_Base		(IO_Base+0x13UL)
#define DIOD_Base		(IO_Base+0x10UL)

#define PORTA_Base		(IO_Base+0x1BUL)
#define PORTB_Base		(IO_Base+0x18UL)
#define PORTC_Base		(IO_Base+0x15UL)
#define PORTD_Base		(IO_Base+0x12UL)

#define DDRA_Base		(IO_Base+0x1AUL)
#define DDRB_Base		(IO_Base+0x17UL)
#define DDRC_Base		(IO_Base+0x14UL)
#define DDRD_Base		(IO_Base+0x11UL)


#define USART_Base		(IO_Base+0x09UL)
#define SPI_Base		(IO_Base+0x0DUL)

//-*-*-*-*-*-*-*-*-*-*-*-
//	Create new Data Types
//-*-*-*-*-*-*-*-*-*-*-*


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: DIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	
	volatile uint8_t	PINx;
	volatile uint8_t	DDRx;
	volatile uint8_t	PORTx;

}DIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct {
	vuint8_t UBRRL;		//USART Baud Rate Register Low
	volatile union{		
		vuint8_t reg;	
		struct {
			vuint8_t TXB8	 :1;		/* Transmit Data Bit 8 */
			vuint8_t RXB8 	 :1;		/* Receive Data Bit 8 */
			vuint8_t UCSZ2   :1;		/* Character Size */
			vuint8_t TXEN    :1;		/* Transmitter Enable */
			vuint8_t RXEN    :1;		/* Receiver Enable */
			vuint8_t UDRIE   :1;		/* USART Data Register Empty Interrupt Enable */
			vuint8_t TXCIE   :1;		/* TX Complete Interrupt Enable */
			vuint8_t RXCIE   :1;		/* RX Complete Interrupt Enable */
		}bits;
	}UCSRB;		//USART Control and Status Register B

	volatile union{
		vuint8_t reg;
	struct{
			vuint8_t MPCM	    :1;		/* Multi-processor Communication Mode */
			vuint8_t U2X		:1;		/* Double the USART Transmission Speed */
			vuint8_t PE			:1;		/* Parity Error */
			vuint8_t DOR		:1;		/* Data OverRun */
			vuint8_t FE			:1;		/* Frame Error */
			vuint8_t UDRE	    :1;		/* USART Data Register Empty */
			vuint8_t TXC		:1;		/* USART Transmit Complete */
			vuint8_t RXC		:1;		/* USART Receive Complete */
		}bits;
	}UCSRA;			//USART Control and Status Register A	
	vuint8_t	UDR;		//USART I/O Data Register
		uint8_t	Reserved[8];
	volatile union	{
		vuint8_t reg;
		struct{
			vuint8_t UCPOL		:1;
			vuint8_t UCSZ0		:1;
			vuint8_t UCSZ1		:1;
			vuint8_t USBS		:1;
			vuint8_t UPM0		:1;
			vuint8_t UPM1		:1;
			vuint8_t UMSEL		:1;
			vuint8_t URSEL		:1;
			}bits;

		}UCSRC;		//USART Baud Rate Register High
}USART_TypeDef;

#define	 UBRRH				UCSRC

typedef struct {
	
	volatile union{
		vuint8_t reg;
		struct{
			vuint8_t SPR0	    :1;		/* SPI Clock Rate Select 0 */
			vuint8_t SPR1		:1;		/* SPI Clock Rate Select 1 */
			vuint8_t CPHA		:1;		/* Clock Phase */
			vuint8_t CPOL		:1;		/* Clock Polarity */
			vuint8_t MSTR		:1;		/* Master/Slave Select */
			vuint8_t DORD	    :1;		/* Data Order */
			vuint8_t SPE		:1;		/* SPI Enable */
			vuint8_t SPIE		:1;		/* SPI Interrupt Enable */
		}bits;
	 }SPCR;		//SPI Control Register
	volatile union{
		vuint8_t reg;
		struct
		{
			vuint8_t SPI2X	    :1;		/* Double SPI Speed Bit */
			vuint8_t Reversed	:5;		/* Reversed */
			vuint8_t WCOL		:1;		/* Write Collision Flag */
			vuint8_t SPIF		:1;		/* SPI Interrupt Flag */
		}bits;	
	}SPSR;		//SPI Status Register
	vuint8_t	SPDR;		//SPI Data Register is a read/write register
	
}SPI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI 
//-*-*-*-*-*-*-*-*-*-*-*

#define MCUCR 	*(volatile uint8_t*)(IO_Base+0x35)	//MCU control register
#define MCUCSR 	*(volatile uint8_t*)(IO_Base+0x34)	//MCU control and status register
#define GICR 	*(volatile uint8_t*)(IO_Base+0x3B)	//general interrupt control register
#define GIFR 	*(volatile uint8_t*)(IO_Base+0x3A)	//general interrupt flag register
#define SREG 	*(volatile uint8_t*)(IO_Base+0x3F) //AVR status register
#define SFIOR	*(volatile uint8_t*)(IO_Base+0x30) //Special FunctionIO Register

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants
//-*-*-*-*-*-*-*-*-*-*-*
#define DIOA						((DIO_TypeDef*)DIOA_Base)
#define DIOB						((DIO_TypeDef*)DIOB_Base)
#define DIOC						((DIO_TypeDef*)DIOC_Base)
#define DIOD						((DIO_TypeDef*)DIOD_Base)

#define PORTA						*(volatile uint8_t*)(PORTA_Base)
#define PORTB						*(volatile uint8_t*)(PORTB_Base)
#define PORTC						*(volatile uint8_t*)(PORTC_Base)
#define PORTD						*(volatile uint8_t*)(PORTD_Base)

#define DDRA						*(volatile uint8_t*)(DDRA_Base)
#define DDRB						*(volatile uint8_t*)(DDRB_Base)
#define DDRC						*(volatile uint8_t*)(DDRC_Base)
#define DDRD						*(volatile uint8_t*)(DDRD_Base)

//DIO_TypeDef *DIOA = 	(DIO_TypeDef *) DIOA_Base;
//DIO_TypeDef *DIOB = 	(DIO_TypeDef *) DIOB_Base;
//DIO_TypeDef *DIOC = 	(DIO_TypeDef *) DIOC_Base;
//DIO_TypeDef *DIOD = 	(DIO_TypeDef *) DIOD_Base;

//USART_TypeDef  *USART   = (USART_TypeDef *)   USART_Base;
#define USART					 	((USART_TypeDef *) USART_Base)
#define SPI							((SPI_TypeDef *) SPI_Base)

//-*-*-*-*-*-*-*-*-*-*-*-
//Global Interrupt Macros
//-*-*-*-*-*-*-*-*-*-*-*


/* SREG – The AVR Status Register -> Bit 7:?Global Interrupt Enable */
#define Global_Interrupt_Enable()		SREG |= (1<<7)	
#define Global_Interrupt_Disable()		SREG &= ~(1<<7)




#endif
