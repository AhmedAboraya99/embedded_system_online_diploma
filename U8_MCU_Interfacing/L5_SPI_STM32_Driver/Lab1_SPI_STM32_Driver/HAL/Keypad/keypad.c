/*
 * keypad.c
 *
 * Created: 4/22/2021 6:32:10 PM
 *  Author: Marco
 */ 


#include "keypad.h"

int Key_padRow[] = {R0, R1, R2, R3}; //rows of the keypad
int Key_padCol[] = {C0, C1, C2, C3};//columns

void Keypad_init(){

	GPIO_PinConfig_t keypad_pinconfig;

	//MODE: init GPIOB R0 pin as input(reset state)
	//CNF: make PORTB pin R0 as floating input
	keypad_pinconfig.GPIO_PINNumber = R0;
	keypad_pinconfig.GPIO_Mode = GPIO_Mode_IN_Float;
	MCAL_GPIO_init (GPIOB,&keypad_pinconfig);

	//MODE: init GPIOB R1 pin as input(reset state)
	//CNF: make PORTB pin R1 as floating input
	keypad_pinconfig.GPIO_PINNumber = R1;
	keypad_pinconfig.GPIO_Mode = GPIO_Mode_IN_Float;
	MCAL_GPIO_init (GPIOB,&keypad_pinconfig);

	//MODE: init GPIOB R2 pin as input(reset state)
	//CNF: make PORTB pin R2 as floating input
	keypad_pinconfig.GPIO_PINNumber = R2;
	keypad_pinconfig.GPIO_Mode = GPIO_Mode_IN_Float;
	MCAL_GPIO_init (GPIOB,&keypad_pinconfig);

	//MODE: init GPIOB R3 pin as input(reset state)
	//CNF: make PORTB pin R3 as floating input
	keypad_pinconfig.GPIO_PINNumber = R3;
	keypad_pinconfig.GPIO_Mode = GPIO_Mode_IN_Float;
	MCAL_GPIO_init (GPIOB,&keypad_pinconfig);

	/************************************************************/

	//MODE: init GPIOB C0 pin as output with max speed = 50MHZ
	//CNF: make PORTB pin C0 as push-pull output
	keypad_pinconfig.GPIO_PINNumber = C0;
	keypad_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	keypad_pinconfig.GPIO_Speed = GPIO_Speed_50MHZ;
	MCAL_GPIO_init (GPIOB,&keypad_pinconfig);

	//MODE: init GPIOB C1 pin as output with max speed = 50MHZ
	//CNF: make PORTB pin C1 as push-pull output
	keypad_pinconfig.GPIO_PINNumber = C1;
	keypad_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	keypad_pinconfig.GPIO_Speed = GPIO_Speed_50MHZ;
	MCAL_GPIO_init (GPIOB,&keypad_pinconfig);

	//MODE: init GPIOB C2 pin as output with max speed = 50MHZ
	//CNF: make PORTB pin C2 as push-pull output
	keypad_pinconfig.GPIO_PINNumber = C2;
	keypad_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	keypad_pinconfig.GPIO_Speed = GPIO_Speed_50MHZ;
	MCAL_GPIO_init (GPIOB,&keypad_pinconfig);

	//MODE: init GPIOB C3 pin as output with max speed = 50MHZ
	//CNF: make PORTB pin C3 as push-pull output
	keypad_pinconfig.GPIO_PINNumber = C3;
	keypad_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	keypad_pinconfig.GPIO_Speed = GPIO_Speed_50MHZ;
	MCAL_GPIO_init (GPIOB,&keypad_pinconfig);

	MCAL_GPIO_WritePort(KEYPAD_PORT ,(0x3F<<2));
}

char Keypad_getkey(){
	int i,j;
	for (i = 0; i < 4; i++){
		MCAL_GPIO_WritePIN(KEYPAD_PORT ,Key_padCol[0],GPIO_PIN_SET);
		MCAL_GPIO_WritePIN(KEYPAD_PORT ,Key_padCol[1],GPIO_PIN_SET);
		MCAL_GPIO_WritePIN(KEYPAD_PORT ,Key_padCol[2],GPIO_PIN_SET);
		MCAL_GPIO_WritePIN(KEYPAD_PORT ,Key_padCol[3],GPIO_PIN_SET);
		MCAL_GPIO_WritePIN(KEYPAD_PORT ,Key_padCol[i],GPIO_PIN_RESET);
		for(j = 0; j < 4; j++){
			if (!(MCAL_GPIO_ReadPIN(KEYPAD_PORT ,Key_padRow[j])))
			{
				while(!(MCAL_GPIO_ReadPIN(KEYPAD_PORT ,Key_padRow[j])));
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
