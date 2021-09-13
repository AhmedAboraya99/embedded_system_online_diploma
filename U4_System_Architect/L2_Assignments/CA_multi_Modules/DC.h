#ifndef _DC_H_
#define _DC_H_
#include "CA.h"
//define states
enum {
	DC_idle,
	DC_busy
}DC_state_id;
//global pointer to function
void (*DC_state)();

//APIs
void DC_init();
STATE_define(DC_idle);
STATE_define(DC_busy);

#endif
