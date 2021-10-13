/*
 * utilities.h
 *
 * Created: 10/14/2021 1:11:41 AM
 *  Author: Ahmed Aboraya
 */ 


#ifndef UTILITIES_H_
#define UTILITIES_H_

#define SetBit(reg,bit) reg|=(1<<bit)
#define ResetBit(reg,bit) reg&=~(1<<bit)
#define ToggleBit(reg,bit) reg^=(1<<bit)
#define ReadBit(reg,bit) (reg>>bit)&1




#endif /* UTILITIES_H_ */