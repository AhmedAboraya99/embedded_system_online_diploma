#ifndef _ATMEGA32_DIO_H_
#define _ATMEGA32_DIO_H_

//-----------------------------
//Includes
//-----------------------------

#include "ATMEGA32.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

//-----------------------------
//Configure structure for DIO
//-----------------------------


typedef struct {
	uint8_t DIO_PINNumber;   	//pin number of DIO Port
	//this parameter can be a value of  @ref DIO_Pins_define

	uint8_t DIO_Mode;			//mode of DIO selected pins
	//this parameter can be a value of  @ref DIO_Mode_define

}DIO_PinConfig_t;
//-----------------------------
//Macros Configuration References
//-----------------------------

/*@ref DIO_Mode_define

 * 0 : floating input (reset state)
 * 1 : Input with pull-up
 * 2 : Input with Pull-down
 * 3 : General purpose Output Push-pull

*/


#define DIO_Mode_IN_HI_Z				0x00000000U
#define DIO_Mode_IN_PD					0x00000001U
#define DIO_Mode_OUT_Low				0x00000002U
#define DIO_Mode_OUT_High				0x00000003U


//@ref DIO_Pin_define

#define DIO_PIN0			 	((uint8_t)0x01)
#define DIO_PIN1				((uint8_t)0x02)
#define DIO_PIN2				((uint8_t)0x04)
#define DIO_PIN3				((uint8_t)0x08)
#define DIO_PIN4				((uint8_t)0x10)
#define DIO_PIN5				((uint8_t)0x20)
#define DIO_PIN6				((uint8_t)0x40)
#define DIO_PIN7				((uint8_t)0x80)

#define DIO_All_PINs			((uint8_t)0xFF)

#define DIO_PIN_Mask				0xFFFFU //pin mask to test

//@ref DIO_Port_define
#define DIO_PORTA			 	0
#define DIO_PORTB				1
#define DIO_PORTC				2
#define DIO_PORTD				3

//@ref DIO_PIN_State

#define  DIO_PIN_RESET						0
#define  DIO_PIN_SET						1

//@ref DIO_PIN_Direction

#define  OUTPUT_PIN							1
#define	 INPUT_PIN							0

//@ref DIO_PORT_Direction					
#define  OUTPUT_PORT						1
#define	 INPUT_PORT							0

/*
* ===============================================
* APIs Supported by "MCAL DIO DRIVER"
* ===============================================
*/

void MCAL_PIN_Direction(DIO_TypeDef* DIOx , uint8_t PIN_Number, uint8_t value );
void MCAL_PORT_Direction(DIO_TypeDef* DIOx , uint8_t value );
//initialization APIs

void  MCAL_DIO_init (DIO_TypeDef* DIOx ,DIO_PinConfig_t* PINConfig);
void  MCAL_DIO_Deinit (uint8_t PORTx );
void  MCAL_DIO_SET_Pin (DIO_TypeDef* DIOx ,uint8_t Pin_Number, uint8_t Pin_Mode );


//Read APIs
uint8_t MCAL_DIO_ReadPIN (DIO_TypeDef* DIOx, uint8_t PIN_Number);
uint8_t MCAL_DIO_ReadPort (DIO_TypeDef* DIOx );

//Write APIs
void MCAL_DIO_WritePIN (DIO_TypeDef* DIOx, uint8_t PIN_Number,uint8_t value );
void MCAL_DIO_WritePort (DIO_TypeDef* DIOx, uint8_t value );

void  MCAL_DIO_TogglePIN (DIO_TypeDef* DIOx, uint8_t PIN_Number);




//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTRF		1
#define EXT_RESET   (1 << EXTRF)

#endif
