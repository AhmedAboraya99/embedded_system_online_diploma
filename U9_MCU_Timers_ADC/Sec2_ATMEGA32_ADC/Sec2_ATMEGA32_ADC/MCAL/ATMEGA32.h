#ifndef _ATMEGA32_H_
#define _ATMEGA32_H_

//-----------------------------
//Includes
//-----------------------------
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "Bit_Math.h"
#include "Platform_Types.h"
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
#define TIMER0_Base		(IO_Base+0x32UL)
#define ADC_Base		(IO_Base+0x04UL)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: DIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	
	volatile uint8_t PINx;
	volatile uint8_t DDRx;
	volatile uint8_t PORTx;

}DIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct {
	volatile uint8_t	UBRRL;		//USART Baud Rate Register Low
	volatile uint8_t	UCSRB;		//USART Control and Status Register B
	volatile uint8_t	UCSRA;		//USART Control and Status Register A
	volatile uint8_t	UDR;		//USART I/O Data Register
	uint8_t	Reserved[19];
	volatile uint8_t	UBRRH;		//USART Baud Rate Register High
	
}USART_TypeDef;

#define UCSRC			USART->UBRRH

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: Timer
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	
	vuint8_t TCNT0;
	volatile union
	{
		vuint8_t reg;
		struct
		{
			vuint8_t CS0n       :3;		/* Clock Select [n = 2:0] */
			vuint8_t WGM01      :1;		/* Waveform Generation Mode [n=0:1] */
			vuint8_t COM0n      :2;		/* Compare Match Output Mode [n = 1:0] */
			vuint8_t WGM00      :1;		/* Waveform Generation Mode */
			vuint8_t FOC0       :1;		/* Force Output Compare */
		}bits;
	}TCCR0;
	uint32_t Reserved0;
	vuint8_t TIFR;
	vuint8_t TIMSK;
	uint16_t Reserved1;
	vuint8_t OCR0;

}TIMER0_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: ADC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	vuint8_t ADCL;			/* Data Register Low Byte*/
	vuint8_t ADCH;			/*Data Register High Byte*/
	volatile union
	{
		vuint8_t reg;
		struct
		{
			vuint8_t ADPSn      :3;		/* ADC Prescaler Select Bits */
			vuint8_t ADIE       :1;		/* ADC Interrupt Enable */
			vuint8_t ADIF       :1;		/* ADC Interrupt Flag */
			vuint8_t ADATE      :1;		/* ADC Auto Trigger Enable */
			vuint8_t ADSC       :1;		/* ADC Start Conversion */
			vuint8_t ADEN       :1;		/* ADC Enable */
		}bits;
	}ADCSRA;
	
	volatile union
	{
		vuint8_t reg;
		struct
		{
			vuint8_t MUXn       :5;		/* Analog Channel and Gain Selection Bits */
			vuint8_t ADLAR      :1;		/*ADC Left Adjust Result */
			vuint8_t REFSn      :2;		/* Reference Selection Bits */
		}bits;
	}ADMUX;
}ADC_TypeDef;


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


#define USART					 	((USART_TypeDef *) USART_Base)

#define TIMER0					 	((TIMER0_TypeDef *) TIMER0_Base)
#define ADC							((ADC_TypeDef *) ADC_Base)
//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros
//-*-*-*-*-*-*-*-*-*-*-*

/* SREG – The AVR Status Register -> Bit 7:?Global Interrupt Enable */
#define Global_Interrupt_Enable()		SREG |= (1<<7)
#define Global_Interrupt_Disable()		SREG &= ~(1<<7)






#endif
