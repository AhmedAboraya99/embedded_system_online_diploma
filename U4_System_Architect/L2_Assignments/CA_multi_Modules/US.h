#ifndef _US_H_
#define _US_H_
#include "CA.h"

//define states
enum {
	US_busy
}US_state_id;
//global pointer to function
void (*US_state)();

//APIs
void US_init();
STATE_define(US_busy);

#endif
