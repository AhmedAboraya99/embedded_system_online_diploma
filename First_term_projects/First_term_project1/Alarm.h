#ifndef _AL_H_
#define _AL_H_
#include "driver.h"
#include "state.h"

//define states
enum {
	Alarm_OFF,
	Alarm_ON
}AL_state_id;
//global pointer to function
void (*Alarm_state)();

//APIs
STATE_define(Alarm_OFF);
STATE_define(Alarm_ON);

#endif
