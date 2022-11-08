/*
 * Bit_Math.h
 *
 * Created: 7/27/2022 6:03:17 PM
 *  Author: Ahmed Aboraya
 */ 
#include <string.h>

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define Set_Bit(Reg, Bit)		(Reg |= (1<<Bit))
#define Reset_Bit(Reg,Bit)		(Reg &=~ (1<<Bit))
#define Toggle_Bit(Reg,Bit)		(Reg ^= (1<<Bit))
#define Get_Bit(Reg,Bit)		((Reg >> Bit) & 1)

#define Set_Pin(Port, Pin)		(Port |= Pin)
#define Reset_Pin(Port,Pin)		(Port &=~ Pin)
#define Toggle_Pin(Port,Pin)	(Port ^= Pin)

#define Set_Port(Port)			(Port = 0xFF)
#define Reset_Port(Port)		(Port = 0x00)
#endif /* BIT_MATH_H_ */