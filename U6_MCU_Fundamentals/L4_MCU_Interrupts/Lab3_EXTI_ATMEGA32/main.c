/*
 * main.c
 *
 *  Created on: Oct 6, 2021
 *      Author: Ahmed Aboraya
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include<stdint.h>

#define  F_CPU  1000000UL
typedef volatile uint32_t vuint32_t;

//IO registers
#define IO_Base 0x20
/*external interrupt registers*/

#define MCUCR 	*(vuint32_t*)(IO_Base+0x35)	//MCU control register
#define MCUCSR 	*(vuint32_t*)(IO_Base+0x34)	//MCU control and status register
#define GICR 	*(vuint32_t*)(IO_Base+0x3B)	//general interrupt control register
#define GIFR 	*(vuint32_t*)(IO_Base+0x3A)	//general interrupt flag register
#define SREG 	*(vuint32_t*)(IO_Base+0x3F) //AVR status register

//PORTD registers
#define PORTD *(vuint32_t*)(IO_Base+0x12) //PORTD data register
#define DDRD *(vuint32_t*)(IO_Base+0x11) //PORTD data direction register


void GPIO_init(){
	//enable PORTD pin 5&6&7
	DDRD |=(0b111<<5);
	//set PORTD pin 2&3 as input pins "serve as INT0 & INT1"
	DDRD &=~(0b11<<2);
	//set PORTB pin 2 as input pin "serve as INT2"
	DDRB &=~(1<<2);
}
void EXTI_init(){
	//Enable Global interrupt
	SREG  |= (1<<7);
	//enable external interrupt 0&1&2 requests
	GICR |=(0b111<<5);
	//falling edge of INT2 generate interrupt request
	MCUCSR|=(0<<6);
	//rising edge of INT1 generate interrupt request
	MCUCR |=(0b11<<2);
	//any change of INT0 generate interrupt request
	MCUCR |=(0b01<<0);

}
int main()
{
	GPIO_init();
	EXTI_init();
	while(1);
}

ISR (INT0_vect)
{
	PORTD |= 1<<5;
	_delay_ms(1000);
	PORTD &= ~(1<<5);
}
ISR (INT1_vect)
{
	PORTD |= 1<<6;
	_delay_ms(1000);
	PORTD &= ~(1<<6);
}
ISR (INT2_vect)
{
	PORTD |= 1<<7;
	_delay_ms(1000);
	PORTD &= ~(1<<7);
}
