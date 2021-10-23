/*
 * main.c
 *
 * Created: 10/17/2021 6:14:10 PM
 *  Author: Ahmed Aboraya
 */ 
#include <util/delay.h>
#include "utilities.h"
#include<stdint.h>
#define F_CPU 8000000UL
typedef volatile uint32_t vuint32_t;

//IO registers
#define IO_Base 0x20

//PORTA registers
#define PORTA 	*(vuint32_t*)(IO_Base+0x1B) //PORTA data register
#define DDRA	*(vuint32_t*)(IO_Base+0x1A) //PORTA data direction register
#define PINA 	*(vuint32_t*)(IO_Base+0x19) //PORTA data input register

//PORTC registers
#define PORTC 	*(vuint32_t*)(IO_Base+0x15) //PORTC data register
#define DDRC	*(vuint32_t*)(IO_Base+0x14) //PORTC data direction register
#define PINC 	*(vuint32_t*)(IO_Base+0x13) //PORTC data input register

void GPIO_init(){
	//reset PORTA Data registers
	PORTA =(0x00);
	//set PORTA pin 0 -> 7 as output
	DDRA =(0xFF);
	
	//set PORTD pin 0 as input
	 ResetBit(DDRC,0);

}


void main()
{
	GPIO_init();

	while(1){
		int i;
		for(i=0;i<=7;i++){
			//Turn ON LED 
			if(ReadBit(PINC,0)==1){
					SetBit(PORTA,i);
					while(ReadBit(PINC,0)==1);
					
			}
			
		}
		PORTA=0x00;
	}
		
}