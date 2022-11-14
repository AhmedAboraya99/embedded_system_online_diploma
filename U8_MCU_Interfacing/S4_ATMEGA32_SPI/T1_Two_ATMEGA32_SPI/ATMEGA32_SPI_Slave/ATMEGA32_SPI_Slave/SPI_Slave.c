/*
 * ATMEGA32_SPI_Slave.c
 *
 * Created: 6/27/2022 8:03:48 PM
 * Author : Ahmed Aboraya
 */ 

#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SPIE	7
#define SPE		6
#define DORD	5
#define MSTR	4
#define SPR0	0

#define SS		4
#define MOSI	5
#define MISO	6
#define SCK		7

#define DDR_SPI		DDRB
#define DDR_PORT	PORTB

void SPI_SlaveInit(void){
	DDR_SPI |= (1<<MISO);
	// Set MISO input
	DDR_SPI &=~(1<<MOSI) &~ (1<<SCK) &~ (1<<SS);	
	// Enable SPI
	SPCR |= (1<<SPE);
	/* Set MISO output, all others input */

}
char SPI_SlaveReceive(void){

	/* Wait for Reception complete */
	while(! (SPSR & (1<<SPIF)) );
	
	/* Return Data Register */
	return SPDR;

}
void SPI_SlaveTransmit(char sData){
	
	/* Start transmission */
	SPDR = sData ;
	/* Wait for transmission complete */
	while(! (SPSR&(1<<SPIF)) );

}
int main(void)
{
	uint8_t NumData ;
	SPI_SlaveInit();
	DDRA=0XFF;
	while (1)
	{
		for(uint8_t i = 255; i >= 0;i--){
			
			NumData = i;
			PORTA = SPI_SlaveReceive();
			_delay_ms(1000);
			DDR_PORT &= ~1<<SS;
			SPI_SlaveTransmit(NumData);
			DDR_PORT &= ~1<<SS;
			
			
		} 
		
	}
}
