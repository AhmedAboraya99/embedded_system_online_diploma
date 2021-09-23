#include "PControl.h"

//define system variables
extern unsigned int Val;
unsigned int threshold = 20;
unsigned int (*PPressure)[20] ;

//define states of pressure control
STATE_define(receiving){
	//state actions
	state_id = receiving ;
	//check reading from sensor
	state=STATE(PressureDetection);
	}

STATE_define(PressureDetection){
	//state actions
	state_id = PressureDetection;

	//check reading from sensor
	if (Val <= threshold)
	{
		Alarm_state = STATE(Alarm_OFF);
		StorePressureVal(Val);
	}
	else
	{
	 Alarm_state = STATE(Alarm_ON);
	 StorePressureVal(Val);
	}
}

void StorePressureVal(int p){
	*(*PPressure) = p;
	PPressure++;
}
