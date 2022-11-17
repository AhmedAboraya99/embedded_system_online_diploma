/*
 * Sec6_I2C_ATMEGA32.c
 *
 * Created: 9/1/2022 8:51:27 PM
 * Author : Ahmed Aboraya
 */ 

#include "I2C.h"

#define MCU_AS_MASTER
//#define MCU_AS_SLAVE

int main(void)
{	
	#ifdef MCU_AS_MASTER
	unsigned int buffer = 0;
	I2C_Init(0x48);
	#endif
	#ifdef MCU_AS_SLAVE
	DDRA = 0xFF;	//make PORTA as output
	I2C_SetAddress(0b11010000);
	#endif
	
    while (1) 
    {
		#ifdef MCU_AS_MASTER
		_delay_ms(2000);
		I2C_Start();
		I2C_Write(0b11010000+0);		/* Application loads SLA+W (slave address+write command) into TWDR*/
		while(TWSR != 0x18)	;			/*Check TWSR to see if SLA+W was sent and ACK received*/
		I2C_Write(buffer++);			//transmit data
		while(TWSR != 0x28)	;			/*Data byte has been transmitted ACK has been received*/
		I2C_Stop();
		#endif
		
		#ifdef MCU_AS_SLAVE
		PORTA = I2C_Read(1);
		#endif
    }
}

