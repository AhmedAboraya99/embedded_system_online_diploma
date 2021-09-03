#include "Platform_Types.h"

#define SYSCTL_RCGC2_R	 	(*((vuint32 *) 0x400FE108))
#define GPIO_PORTF_DATA_R 	(*((vuint32 *) 0x400253FC))
#define GPIO_PORTF_DIR_R 	(*((vuint32 *) 0x40025400))
#define GPIO_PORTF_DEN_R 	(*((vuint32 *) 0x4002551C))

int main(void)
{
	vuint32 delay_count;
	SYSCTL_RCGC2_R = 0x00000020;	//enable PORTF
	for ( delay_count = 0; delay_count<200; delay_count++); //wait a while until enabling PORTF get submitted
	GPIO_PORTF_DIR_R |= 1<<3 ;
	GPIO_PORTF_DEN_R |= 1<<3 ;	//enable bit no 3
	while(1)
	{
		GPIO_PORTF_DATA_R |= 1<<3; 		//open led 
		for ( delay_count = 0; delay_count<200000; delay_count++);
		GPIO_PORTF_DATA_R &= ~(1<<3);	//close led
		for ( delay_count = 0; delay_count<200000; delay_count++);
	}
return 0;
}	