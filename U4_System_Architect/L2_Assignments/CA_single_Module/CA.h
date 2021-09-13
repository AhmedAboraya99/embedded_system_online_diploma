#ifndef _CA_H_
#define _CA_H_

#include <stdio.h>
#include <stdlib.h>


#define STATE_define(_stateFunc_) void ST_##_stateFunc_()
#define STATE(_stateFunc_) ST_##_stateFunc_

//define states
enum {
	waiting,
	driving
}state_id;
//global pointer to function
void (*state)();

//APIs
STATE_define(waiting);
STATE_define(driving);

#endif
