/*
 * Bit_Math.h
 *
 * Created: 7/27/2022 6:03:17 PM
 *  Author: Ahmed Aboraya
 */ 
#include <string.h>


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define BIT_SET					SET
#define BIT_RESET				RESET

#define SET_Bit(Reg, Bit)		(Reg |= (1<<Bit))
#define RESET_Bit(Reg,Bit)		(Reg &=~ (1<<Bit))
#define TOGGLE_Bit(Reg,Bit)		(Reg ^= (1<<Bit))
#define GET_Bit(Reg,Bit)		((Reg >> Bit) & 1)

#define SET_Pin(Reg, Pin)		(Reg |= Pin)
#define RESET_Pin(Reg, Pin)		(Reg &=~ Pin)
#define TOGGLE_Pin(Reg, Pin)	(Reg ^= Pin)

#define SET_Config(Reg, Config)			SET_Pin(Reg, Config)
#define RESET_Config(Reg, Config)		(Reg &= Config)
#define SET_Port(Port)					(Port = 0xFF)
#define RESET_Port(Port)				(Port = 0x00)
#define ASSIGN_Port(Port,value)			(Port = value)

#define SET_Bitfield(Bitfield)			(Bitfield = 1)
#define RESET_Bitfield(Bitfield)		(Bitfield = 0)
#define	ASSIGN_Bitfield(Bitfield, Value)		(Bitfield = Value)
#endif /* BIT_MATH_H_ */