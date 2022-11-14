/*
 * SPI.h
 *
 * Created: 8/17/2022 5:26:28 PM
 *  Author: Ahmed Aboraya
 */ 


#ifndef SPI_H_
#define SPI_H_

//-----------------------------
//Includes
//-----------------------------

#include "ATMEGA32.h"
#include "DIO_Driver.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------


typedef struct{
	uint8_t SPI_Mode; 				//select SPI Master/Slave mode.
	//@ref SPI_Mode_define

	uint8_t Frame_Format;			//specifies Data be shifted out either MSB-first or LSB-first
	//@ref Frame_Format_define

	uint8_t Clock_Polarity;		// specifies SPI clock Polarity idle on low or idle on high
	//@ref Clock_Polarity_define

	uint8_t Clock_Phase;			// specifies SPI clock Phase "first clock capture or second clock capture"
	//@ref Clock_Phase_define

	uint8_t Clock_Speed;			//define SPI Clock Speed Low or High
	//@ref Clock_Speed_define
	
	uint8_t BaudRate_Prescalar;		//  define the serial clock baud rate prescalar
	// @ref BaudRate_Prescalar_define
	

	uint8_t IRQ_Enable;				// enable or disable SPI interrupt request
	// @ref IRQ_Enable_define

	void (*P_IRQ_CallBack)(void);		//pointer to IRQ call back function which will be called once IRQ happened
	


}SPI_Config_t;


enum SPI_Polling_Mechanism{
	SPI_Polling_Enable,
	SPI_Polling_Disable
};

//-----------------------------
//Bit definitions of SPI Registers 
//-----------------------------
/* SPCR */
//#define SPIE	7
//#define SPE		6
//#define DORD	5
//#define MSTR	4
//#define SPR0	0

#define SS		4
#define MOSI	5
#define MISO	6
#define SCK		7
/* SPSR */
//#define SPIF    7

#define SPI_DIO		DIOB

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref SPI_Mode_define
#define SPI_Mode_MASTER						(uint8_t) (1<<4)
#define SPI_Mode_SLAVE						(uint8_t) (0)

//@ref Frame_Format_define
#define  Frame_Format_LSB_FIRST				(uint8_t) (1<<5)
#define  Frame_Format_MSB_FIRST				(uint8_t) (0)


//@ref Clock_Polarity_define
#define Clock_Polarity_Idle_LOW				(uint8_t) (0)
#define Clock_Polarity_Idle_HIGH			(uint8_t) (1<<3)

//@ref Clock_Phase_define
#define Clock_Phase_First_Capture			(uint8_t) (0)
#define Clock_Phase_Second_Capture			(uint8_t) (1<<2)

//@ref Clock_Speed_define
#define Clock_Speed_Normal							(uint8_t) (0)
#define Clock_Speed_Double							(uint8_t) (1<<0)

// @ref BaudRate_Prescalar_define
/* SPCR.Bits 1:0 – SPRn:?SPI Clock Rate Select */
#define BaudRate_Prescalar_Divide_BY_4					(uint8_t) (0)
#define BaudRate_Prescalar_Divide_BY_16					(uint8_t) (1<<0)
#define BaudRate_Prescalar_Divide_BY_64					(uint8_t) (2<<0)
#define BaudRate_Prescalar_Divide_BY_128				(uint8_t) (3<<0)
/* SPSR.Bit 0 – SPI2X:?Double SPI Speed Bit */
#define BaudRate_Prescalar_DOUBLE_Divide_2				(uint8_t) (0)
#define BaudRate_Prescalar_DOUBLE_Divide_8				(uint8_t) (1<<0)
#define BaudRate_Prescalar_DOUBLE_Divide_32				(uint8_t) (2<<0)
#define BaudRate_Prescalar_DOUBLE_Divide_64				(uint8_t) (3<<0)


// @ref IRQ_Enable_define
/* Bit 7 – SPIE:?SPI Interrupt Enable */
#define SPI_IRQ_ENABLE_NONE					(uint8_t) (0)			// IRQ Disable
#define SPI_IRQ_ENABLE						(uint8_t) (1<<7)


/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/

SPI_Config_t *Global_SPI_Config;


/*
* ==============================================================================
* 				  APIs Supported by "MCAL SPI DRIVER"
* ==============================================================================
*/

void MCAL_SPI_Init(SPI_TypeDef* SPIx, SPI_Config_t* SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx);
void MCAL_SPI_DIO_Set_Pins(SPI_TypeDef* SPIx);

void MCAL_SPI_Send_Data(SPI_TypeDef* SPIx, char* pTxBuffer, enum SPI_Polling_Mechanism Polling_En);
void MCAL_SPI_Recieve_Data(SPI_TypeDef* SPIx, char* pTxBuffer, enum SPI_Polling_Mechanism Polling_En);

void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx, char* pTxBuffer, enum SPI_Polling_Mechanism Polling_En);





#endif /* SPI_H_ */