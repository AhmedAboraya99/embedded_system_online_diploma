/*
 * I2C.c
 *
 * Created: 9/1/2022 8:57:18 PM
 *  Author: Ahmed Aboraya
 */ 
#include "I2C.h"
uint8_t PrescalerValue = 1; //1 4 16 64

void I2C_Init(unsigned long SCL_Clock){
	TWBR =  ((F_CPU/SCL_Clock)-16) / (2*PrescalerValue);
	switch(PrescalerValue){
		case 1:
			TWSR = 0;
			break;
		case 4:
			TWSR = 1;
			break;
		case 16:
			TWSR = 2;
			break;	
		case 64:
			TWSR = 3;
			break;			
		
	}
}
void I2C_Start(){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		/* Send START condition */
	while(!(TWCR&(1<<TWINT)));					/* Wait for TWINT Flag set.
												 This indicates that the START condition has been transmitted. */
	while(TWSR != 0x08);						/* Status code is set after Start condition has been transmitted */
}
void I2C_Write(unsigned char DATA){
	TWDR = DATA;		/* Load DATA into TWDR Register. */
	
	TWCR = (1<<TWINT)|(1<<TWEN);	/*  Clear TWINT bit in TWCR to start transmission of data */
	while(!(TWCR & (1<<TWINT)));			//Wait for TWINT Flag set.
	/* This indicates that the DATA has been transmitted, and ACK/NACK has been received */

}
void I2C_Stop(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
void I2C_SetAddress(unsigned char address){
	TWAR = address;
}
unsigned char I2C_Read(unsigned char ack){
	
	if (ack == 1){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);	//TWEA bit is written to one, means: 
// 	1. The device’s own slave address has been received.
// 	2. A general call has been received, while the TWGCE bit in the TWAR is set.
// 	3. A data byte has been received in Master Receiver or Slave Receiver mode.
	}
	while(!(TWCR & (1<<TWINT)));		/*This indicates that the SLA+W has been transmitted, and ACK/NACK has been received.*/
	while(TWSR != 0x60);				/* Own SLA+W has been received; ACK has been returned*/
	if (ack == 1)
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(!(TWCR & (1<<TWINT)));		/*This indicates that the DATA has been transmitted, and ACK/NACK has been received.*/
	while(TWSR != 0x80);				/*data has been received; ACK has been returned*/
	return TWDR;
}