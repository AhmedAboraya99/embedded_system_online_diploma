/*
 * keypad.h
 *
 * Created: 4/22/2021 6:32:00 PM
 *  Author: Ahmed Aboraya
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

//-----------------------------
//Includes
//-----------------------------
#include "ATMEGA32.h"
#include "DIO_Driver.h"

#define R0 DIO_PIN0
#define R1 DIO_PIN1
#define R2 DIO_PIN2
#define R3 DIO_PIN3
#define C0 DIO_PIN4
#define C1 DIO_PIN5
#define C2 DIO_PIN6
#define C3 DIO_PIN7

#define KEYPAD_PORT DIOC

#define DataDir_KEYPAD_PORT DDRC
void Keypad_init();
char Keypad_getkey();

#endif /* KEYPAD_H_ */
