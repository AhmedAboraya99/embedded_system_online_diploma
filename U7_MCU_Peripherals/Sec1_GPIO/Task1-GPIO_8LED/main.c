/*
 * main.c
 *
 * Created: 10/16/2021 8:49:59 AM
 *  Author: Ahmed Aboraya
 */ 
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

void GPIO_init(){
	//reset PORTA Data registers
	PORTA =(0x00);
	//set PORTA pin 0 -> 7 as output
	DDRA =(0xFF);

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
		int i;
		for(i=0;i<=7;i++){
			//Turn ON LED Sequentially
			SetBit(PORTA,i);
			WAIT_ms(30);	//delay
		}
		for(i=7;i>=0;i--){
			//Turn OFF LED Sequentially
			ResetBit(PORTA,i);
			WAIT_ms(30);	//delay
		}

	}
}