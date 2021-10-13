/*
 * main.c
 *
 * Created: 10/13/2021 11:55:48 PM
 *  Author: Ahmed Aboraya
 */ 
#include "utilities.h"
#include<stdint.h>
#define F_CPU 8000000UL
typedef volatile uint32_t vuint32_t;

//IO registers
#define IO_Base 0x20

//PORTD registers
#define PORTD 	*(vuint32_t*)(IO_Base+0x12) //PORTD data register
#define DDRD	*(vuint32_t*)(IO_Base+0x11) //PORTD data direction register
#define PIND 	*(vuint32_t*)(IO_Base+0x10) //PORTD data input register


void GPIO_init(){
	//reset PORTD Data registers
	
	
	//set PORTD pin 4 -> 7 as output
	DDRD |=(0b1111<<4);

}

void WAIT_ms(uint32_t t){
	uint32_t i,j;
	for(i=0;i<t;i++){
		for(j=0;j<255;j++);
	}
}
void main()
{
	GPIO_init();

	while(1){
		//Turn ON first LED
		SetBit(PORTD,5);
		WAIT_ms(10);	//delay

		//Turn ON second LED
		ResetBit(PORTD,5);
		SetBit(PORTD,6);
		WAIT_ms(10);	//delay

		//Turn ON third LED
		ResetBit(PORTD,6);
		SetBit(PORTD,7);
		WAIT_ms(10);	//delay

		//Turn ON BUZZer
		ResetBit(PORTD,7);
		SetBit(PORTD,4);
		WAIT_ms(10);	//delay
		ResetBit(PORTD,4);
		WAIT_ms(10);	//delay
	}
}