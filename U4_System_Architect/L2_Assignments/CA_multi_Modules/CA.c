#include "CA.h"
//define system variables
unsigned int distance, speed, threshold = 50;

//define states of robot motor speed
STATE_define(waiting){
	//state actions
	state_id = waiting ;
	//check reading from sensor
	printf("waiting state : distance = %d , speed = %d \n\n",distance,speed );
	speed = 0;
	set_motor_speed(speed);
}

STATE_define(driving){
	//state actions
	state_id = driving ;

	//check reading from sensor
	(distance <= threshold)? (state=STATE(waiting)) : (state=STATE(driving)) ;
	printf("driving state : distance = %d , speed = %d \n\n",distance,speed );
	//set motor speed to 30 (Turn on)
	speed = 30;
	set_motor_speed(speed);
}

void read_US_distance(int d){
	distance = d;
	//check reading from sensor
	(distance <= threshold)? (state=STATE(waiting)) : (state=STATE(driving)) ;
	printf("US---------distance = %d------->CA\n",distance);
}
