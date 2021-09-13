#include "US.h"

//define system variables
unsigned int distance ;

//generate random number of distances
int generate_random(int low , int range,int count){

	int i ;
	int rand_num;
	for(i = 0; i < count; i++){
		rand_num = (rand()%(range-low+1)) + low;
	}
	return rand_num ;
}

void US_init(){
	//init US sensor by calling its driver
	printf("US init \n");
}
//define states of robot motor speed
STATE_define(US_busy){
	//state actions
	state_id = US_busy ;
	//read distance from US
	distance = generate_random(40,60,1);
	printf("US_busy state : distance = %d  \n",distance );
	read_US_distance(distance);
	US_state = STATE(US_busy);
}
