#include "Alarm.h"

//define states of alarm
STATE_define(Alarm_OFF){
	//state actions
	AL_state_id = Alarm_OFF ;
	Set_Alarm_actuator(0);
}

STATE_define(Alarm_ON){
	//state actions
	AL_state_id = Alarm_ON ;
	Set_Alarm_actuator(1);
	Delay(60*1000);
	Set_Alarm_actuator(0);

}
