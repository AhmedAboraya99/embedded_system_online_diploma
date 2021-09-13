#include "DC.h"
//define system variables
unsigned int speed;


void DC_init(){
	//init DC motor by calling its driver
	printf("DC init \n");
}
//define states of robot motor speed
STATE_define(DC_idle){
	//state actions
	DC_state_id = DC_idle ;

	printf("DC idle state : speed = %d \n",speed );
}

STATE_define(DC_busy){
	//state actions
	DC_state_id = DC_busy ;
	DC_state = STATE(DC_idle);
	printf("DC busy state : speed = %d \n",speed );
}

void set_motor_speed(int s){
	speed = s;
	//set dc state to busy
	DC_state = STATE(DC_busy);
	printf("DC---------speed = %d------->CA\n",speed);
}
