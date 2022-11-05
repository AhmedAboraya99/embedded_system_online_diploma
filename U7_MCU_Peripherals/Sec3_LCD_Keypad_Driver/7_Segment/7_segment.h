/*
 * 7_segment.h
 *
 * Created: 4/17/2022 5:52:21 PM
 *  Author: Ahmed Aboraya
 */


#ifndef _7_SEGMENT_
#define _7_SEGMENT_
//-----------------------------
//Includes
//-----------------------------
#include "STM32F103X6.h"
#include "STM32f103X6_GPIO_Driver.h"

//-----------------------------
//Macros
//-----------------------------
#define ZERO		0x01
#define ONE			0x79
#define TWO			0x24
#define THREE		0x30
#define FOUR		0x4C
#define FIVE 		0x12
#define SIX			0x02
#define SEVEN		0x19
#define EIGHT		0x00
#define NINE		0x10


#define Segments_PORT GPIOB

//-----------------------------
//Global Variables
//-----------------------------

GPIO_PinConfig_t lcd_pinconfig;

// Array of 7 segment shapes of Numbers
unsigned char Seg_Numbers[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};


// Array to display Numbers of LCD screen
unsigned char LCD_Numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};


//-----------------------------
//Function Prototypes
//-----------------------------
void INIT_7_Segment();



#endif /* _7_SEGMENT_ */
