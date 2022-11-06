/*
 * keypad.c
 *
 * Created: 4/22/2021 6:32:10 PM
 *  Author: Ahmed Aboraya
 */ 


#include "keypad.h"

int Key_padRow[] = {R0, R1, R2, R3}; //rows of the keypad
int Key_padCol[] = {C0, C1, C2, C3};//columns

void Keypad_init(){

	//DIO_PinConfig_t keypad_pinconfig;

	//MODE: init DIOB R0 pin as input(reset state)
	//CNF: make PORTB pin R0 as input

	MCAL_PIN_Direction (KEYPAD_PORT, R0, INPUT_PIN);


	//MODE: init KEYPAD_PORT R1 pin as input(reset state)
	//CNF: make PORTB pin R1 as input

	MCAL_PIN_Direction (KEYPAD_PORT, R1, INPUT_PIN);



	//MODE: init DIOB R2 pin as input(reset state)
	//CNF: make PORTB pin R2 as input
	MCAL_PIN_Direction (KEYPAD_PORT, R2, INPUT_PIN);



	//MODE: init DIOB R3 pin as input(reset state)
	//CNF: make PORTB pin R3 as input
	MCAL_PIN_Direction (KEYPAD_PORT, R3, INPUT_PIN);


	/************************************************************/

	// make PORTB pin C0 as output
	MCAL_PIN_Direction (KEYPAD_PORT, C0, OUTPUT_PIN);

	// make PORTB pin C1 as output
	MCAL_PIN_Direction (KEYPAD_PORT, C1, OUTPUT_PIN);

	// make PORTB pin C2 as output

	MCAL_PIN_Direction (KEYPAD_PORT, C2, OUTPUT_PIN);

	// make PORTB pin C3 as output
	MCAL_PIN_Direction (KEYPAD_PORT, C3, OUTPUT_PIN);


	MCAL_DIO_WritePort(KEYPAD_PORT ,0xFF);
}

char Keypad_getkey(){
	int i,j;
	for (i = 0; i < 4; i++){
		/* --- All Column PINS are SET to 1, Once a PIN is pressed it will RESET --- */
		MCAL_DIO_WritePIN(KEYPAD_PORT ,Key_padCol[0],DIO_PIN_SET);
		MCAL_DIO_WritePIN(KEYPAD_PORT ,Key_padCol[1],DIO_PIN_SET);
		MCAL_DIO_WritePIN(KEYPAD_PORT ,Key_padCol[2],DIO_PIN_SET);
		MCAL_DIO_WritePIN(KEYPAD_PORT ,Key_padCol[3],DIO_PIN_SET);

		MCAL_DIO_WritePIN(KEYPAD_PORT ,Key_padCol[i],DIO_PIN_RESET);
		for(j = 0; j < 4; j++){
			if (!(MCAL_DIO_ReadPIN(KEYPAD_PORT ,Key_padRow[j])))
			{
				while(!(MCAL_DIO_ReadPIN(KEYPAD_PORT ,Key_padRow[j])));
				switch(i){
					case (0):
						if (j == 0) return '7';
						else if (j == 1) return '4';
						else if (j == 2) return '1';
						else if (j == 3) return '?';
						break;
					case (1):
						if (j == 0) return '8';
						else if (j == 1) return '5';
						else if (j == 2) return '2';
						else if (j == 3) return '0';
						break;
					case (2):
						if (j == 0) return '9';
						else if (j == 1) return '6';
						else if (j == 2) return '3';
						else if (j == 3) return '=';
						break;
					case (3):
						if (j == 0) return '/';
						else if (j == 1) return '*';
						else if (j == 2) return '-';
						else if (j == 3) return '+';
						break;
				}
			}
		}
	}
	return 'A';
}
