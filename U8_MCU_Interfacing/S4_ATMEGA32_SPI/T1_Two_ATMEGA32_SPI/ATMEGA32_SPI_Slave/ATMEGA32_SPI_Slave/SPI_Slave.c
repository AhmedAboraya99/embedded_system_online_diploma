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


void SPI_SlaveInit(void){
	DDR_SPI |= (1<<MISO);
	// Set MISO input
	DDR_SPI &=~(1<<MOSI) &~ (1<<SCK) &~ (1<<SS);	
	// Enable SPI
	SPCR |= (1<<SPE);
	/* Set MISO output, all others input */

}
char SPI_SlaveReceive(char rData){

	SPDR = rData;
	/* Wait for Reception complete */
	while(! (SPSR & (1<<SPIF)) );
	
	/* Return Data Register */
	return SPDR;

}
int main(void)
{
	char NumData ;
	SPI_SlaveInit();
	DDRA=0XFF;
	while (1)
	{
		for(int i = 10; i >= 0;i-- ){
			
			NumData = i;
			PORTA = SPI_SlaveReceive(NumData);
			_delay_ms(500);
			
		} 
		
	}
}
