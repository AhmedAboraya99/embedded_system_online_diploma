#ifndef _PS_H_
#define _PS_H_
#include "state.h"
#include "driver.h"
#include "PControl.h"

//define states
enum {
	PS_reading
}PS_state_id;
//global pointer to function
void (*PS_state)();

//APIs
void ReadSensorValue(int v);
STATE_define(PS_reading);

#endif
