/*
 * main.c
 *
 * Created: 7/12/2022 9:24:20 AM
 *  Author: Ahmed Aboraya
 */ 

#define  F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SPIE	7
#define SPE		6
#define DORD	5
#define MSTR	4
#define CPHA	2
#define SPR0	0


#define SS		4
#define MOSI	5
#define MISO	6
#define SCK		7

#define DDR_SPI		DDRB
#define SPI_PORT	PORTB

void SPI_MasterInit(void){
	/* Set MOSI and SCK output, all others input */
	DDR_SPI |= (1<<MOSI) | (1<<SS) |(1<<SCK);
	DDR_SPI &= ~(1<<MISO) ;
	// Enable SPI, Master mode and set clock rate as fck/16
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0) ;

}
void MAX7221_PacketTransmit(char sCommand, char sData){
	// initialize the packet by writing 0 on SS "SS must be low to clock data in or out"
	SPI_PORT &= ~( 1 << SS); 
	//write command on MAX7221
	SPDR = sCommand ;
	/* Wait for transmission complete */
	while(! (SPSR&(1<<SPIF)) );
	/* Start transmission */
	SPDR = sData ;
	/* Wait for transmission complete */
	while(! (SPSR&(1<<SPIF)) );
	 //  terminate the packet by writing 1 on SS "SS must be HIGH after clock data in or out"
	SPI_PORT |= ( 1 << SS);

}
int main(void)
{
	char NumData ;
	char Counter = 0;
	SPI_MasterInit();
	
	MAX7221_PacketTransmit(0x09, 0xFF); // set decoding mode
	MAX7221_PacketTransmit(0x0A, 0x0F); // set scan limit
	MAX7221_PacketTransmit(0x0B, 0x7F); // Max intensity
	MAX7221_PacketTransmit(0x0C, 0x01); // turn on display
	
	while (1)
	{
		
		for( NumData = 1; NumData< 9;NumData++ ){
			
			MAX7221_PacketTransmit(NumData, Counter++); 
			_delay_ms(1000);
		}
		
	}
}

