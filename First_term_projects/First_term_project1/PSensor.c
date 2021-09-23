#include "PSensor.h"
//define system variables
unsigned int Val ;

//define states of pressure sensor reading
STATE_define(PS_reading){
	//state actions
	PS_state_id = PS_reading ;
	//read pressure Val from PSensor
	ReadSensorValue(Val);
	PS_state = STATE(PS_reading);
}

void ReadSensorValue(int v){
	v = getPressureVal();
	Val =v;
	//check reading from sensor
	state=STATE(receiving);
}