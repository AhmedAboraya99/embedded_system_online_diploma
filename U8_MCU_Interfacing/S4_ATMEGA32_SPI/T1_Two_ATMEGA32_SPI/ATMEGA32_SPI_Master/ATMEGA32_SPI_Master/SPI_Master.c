/*
 * ATMEGA32_SPI.c
 *
 * Created: 6/27/2022 10:50:35 AM
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

void SPI_MasterInit(void){
	/* Set MOSI and SCK output, all others input */
	DDR_SPI |= (1<<MOSI) | (1<<SS) |(1<<SCK);
	// Enable SPI, Master mode and set clock rate as fck/16 
	SPCR |= (1<<SPE) | (1<<MSTR) |(1<<SPR0);

}
void SPI_MasterTransmit(char sData){
	
	/* Start transmission */
	SPDR = sData ;
	/* Wait for transmission complete */
	while(! (SPSR&(1<<SPIF)) );

}
char SPI_MasterReceive(void){

	/* Wait for Reception complete */
	while(! (SPSR & (1<<SPIF)) );
	
	/* Return Data Register */
	return SPDR;

}
int main(void)
{
	uint8_t NumData ;
	SPI_MasterInit();
	DDRA=0XFF;

    while (1) 
    {
		
		for(uint8_t i = 0 ; i<= 255;i++ ){
			
			NumData =  i;
			DDR_PORT &= ~1<<SS;
			SPI_MasterTransmit(NumData);
			DDR_PORT |= 1<<SS;
			PORTA = SPI_MasterReceive();	
			_delay_ms(1000);
		}
		
    }
}

