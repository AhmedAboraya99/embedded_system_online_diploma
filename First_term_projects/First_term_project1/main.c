#include"state.h"
#include"PControl.h"

void setup()
{	
	//initialize GPIO driver
	GPIO_INITIALIZATION();
	//init states of PC drivers
	//init modules of SOC
	PS_state = STATE(PS_reading);
	state = STATE(receiving);
	Alarm_state = STATE(Alarm_OFF);
}

int main (){
	setup();
	while (1)
	{
		int d;
		PS_state();
		state();
		Alarm_state();
		for(d = 0; d <=1000;d++);
	}

}
