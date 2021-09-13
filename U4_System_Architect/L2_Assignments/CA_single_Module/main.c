#include "CA.h"

void setup()
{
	//init state of CA robot motor
	//init modules of SOC
	state = STATE(waiting);
}

void main()
{
	volatile int d;
	setup();
	while (1)
	{	
		//detect state of motor
		state();
		//delay
		for(d = 0; d <=1000;d++);
	}
}
