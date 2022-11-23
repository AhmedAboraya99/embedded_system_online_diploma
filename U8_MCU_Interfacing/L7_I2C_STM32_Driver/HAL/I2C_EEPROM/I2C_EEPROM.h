/*
 * I2C_EEPROM.h
 *
 *  Created on: Nov 21, 2022
 *      Author: Ahmed Aboraya
 */

#ifndef I2C_EEPROM_H_
#define I2C_EEPROM_H_

#include "STM32F103_I2C_Driver.h"
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define EEPROM_Slave_Address	0x2A  // default Address

/*
* ===============================================
* APIs Supported by "HAL I2C EEPROM"
* ===============================================
*/
void I2C_EEPROM_Init(void);
void I2C_EEPROM_Write_Data(uint32_t Memory_Address , uint8_t* PTxBuffer , uint8_t DataLength);
void I2C_EEPROM_Read_Data( uint32_t Memory_Address , uint8_t* PRxBuffer , uint8_t DataLength);

#endif /* I2C_EEPROM_H_ */
