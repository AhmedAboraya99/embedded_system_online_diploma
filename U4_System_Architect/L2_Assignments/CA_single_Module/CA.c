#include "CA.h"
//define system variables
unsigned int distance, speed, threshold = 50;

//generate random number function
int generate_random(int low , int range,int count){

	int i ;
	int rand_num;
	for(i = 0; i < count; i++){
		rand_num = (rand()%(range-low+1)) + low;
	}
	return rand_num ;
}
//define states of robot motor speed
STATE_define(waiting){
	//state actions
	state_id = waiting ;
	speed = 0;
	distance = generate_random(40,60,1);
	//check reading from sensor
	(distance <= threshold)? (state=STATE(waiting)) : (state=STATE(driving)) ;
	printf("waiting state : distance = %d , speed = %d \n",distance,speed );
}
STATE_define(driving){
	//state actions
	state_id = driving ;
	speed = 30;
	distance = generate_random(40,60,1);
	//check reading from sensor
	(distance <= threshold)? (state=STATE(waiting)) : (state=STATE(driving)) ;
	printf("driving state : distance = %d , speed = %d \n",distance,speed );
}
