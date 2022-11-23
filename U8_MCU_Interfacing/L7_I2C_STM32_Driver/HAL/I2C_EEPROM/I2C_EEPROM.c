/*
 * I2C_EEPROM.c
 *
 *  Created on: Nov 21, 2022
 *      Author: Ahmed Aboraya
 */


#include "I2C_EEPROM.h"

void I2C_EEPROM_Init(void)
{

	I2C_Config_t I2C_EEPROMCfg;

	/* I2C Controller as Master */
	I2C_EEPROMCfg.G_CallAddress_Detection = G_CallAddress_Enable;
	I2C_EEPROMCfg.Bus_Mode = I2C_Mode;
	I2C_EEPROMCfg.Clock_Stretch = Clock_Stretch_Enable;
	I2C_EEPROMCfg.I2C_Addressing_Mode = Addressing_Mode_7bit;
	I2C_EEPROMCfg.I2C_ClockSpeed.I2C_SpeedMode = Standard_Speed_Mode;
	I2C_EEPROMCfg.I2C_ClockSpeed.I2C_ClockFreq = I2C_SM_100KHz;
	I2C_EEPROMCfg.I2C_ACK_Control = I2C_ACK_Enable;
	I2C_EEPROMCfg.IRQ_Enable = I2C_IRQ_Disable;
	I2C_EEPROMCfg.P_IRQ_CallBack = NULL;

	MCAL_I2C_Init(I2C1, &I2C_EEPROMCfg);
	MCAL_I2C_GPIO_Set_Pins(I2C1);

}

void I2C_EEPROM_Write_Data(uint32_t Memory_Address , uint8_t* PTxBuffer , uint8_t DataLength){
	uint8_t i=0;
	uint8_t Ebuffer[256];

	Ebuffer[0] = (uint8_t)(Memory_Address >> 8);		// Send Higher Byte of memory address
	Ebuffer[1] = (uint8_t)(Memory_Address);			// Send Lower Byte of memory address

	for( i =2 ; i<(DataLength+2) ; i++)
	{
		Ebuffer[i]= PTxBuffer[i-2];
	}

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, Ebuffer, (DataLength+2), Start, With_Stop);


}
void I2C_EEPROM_Read_Data( uint32_t Memory_Address , uint8_t* PRxBuffer , uint8_t DataLength)
{
	uint8_t Ebuffer[2];

	Ebuffer[0] = (uint8_t)(Memory_Address >> 8);		// Send Higher Byte of memory address
	Ebuffer[1] = (uint8_t)(Memory_Address);			// Send Lower Byte of memory address

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, Ebuffer, 2, Start, Without_Stop);
	MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_Address, PRxBuffer, DataLength, Repeated_Start, With_Stop);

}

