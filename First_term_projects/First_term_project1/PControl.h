#ifndef _PC_H_
#define _PC_H_
#include "state.h"
#include "driver.h"
#include "PSensor.h"
#include "Alarm.h"

//define states
enum {
	receiving,
	PressureDetection
}state_id;
//global pointer to function
void (*state)();

//signal connections
void StorePressureVal(int p);
//APIs
STATE_define(receiving);
STATE_define(PressureDetection);

#endif
