#include "CA.h"
#include "US.h"
#include "DC.h"

void setup()
{
	//init states of CA robot
	//init modules of SOC
	US_init();
	DC_init();
	state = STATE(waiting);
	US_state = STATE(US_busy);
	DC_state = STATE(DC_idle);
}

void main()
{
	volatile int d;
	setup();
	while (1)
	{	
		//detect state of motor
		state();
		US_state();
		DC_state();
		//delay
		for(d = 0; d <=1000;d++);
	}
}
