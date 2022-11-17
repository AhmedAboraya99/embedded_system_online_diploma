/*
 * I2C.h
 *
 * Created: 9/1/2022 8:56:37 PM
 *  Author: Ahmed Aboraya
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>


void I2C_Init(unsigned long SCL_Clock);
void I2C_Start();
void I2C_Stop();
void I2C_Write(unsigned char DATA);
unsigned char I2C_Read(unsigned char ack); 
void I2C_SetAddress(unsigned char address);

#endif /* I2C_H_ */