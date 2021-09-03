#include "Platform_Types.h"

extern uint32_t _S_DATA;
extern uint32_t _E_DATA;
extern uint32_t _S_bss;
extern uint32_t _E_bss;
extern uint32_t _E_text ;

void Reset_Handler (void);
extern int main(void);

 void Default_Handler(void)
{
	Reset_Handler();
}
/* make handlers point to the same address using alias */
/*using weak attribute to make the weak symbol of vector */
void NMI_Handler(void) __attribute__ ((weak,alias ("Default_Handler")));;
void H_fault_Handler(void) __attribute__ ((weak,alias ("Default_Handler")));;

//reserve stack size
static uint32_t STACK_Top[256]; //256*4 = 1024 Byte

/* create vector section in text section using array and _attribute_ pragma */
void (* const GPFun_Vector[])() __attribute__((section(".vectors"))) = 
{
	(void (*)()) ((uint32_t)STACK_Top + sizeof(STACK_Top)),
	&Reset_Handler,
	&NMI_Handler ,
	&H_fault_Handler 
};

void Reset_Handler (void)
{
	//copy data from ROM to RAM
	uint32_t DATA_size = ( uint8_t*)&_E_DATA - ( uint8_t*)&_S_DATA ;
	uint8_t* P_src = ( uint8_t*)&_E_text ;
	uint8_t* P_dst = ( uint8_t*)&_S_DATA ;
	int i ;
	for ( i = 0 ;i < DATA_size ;i++ ) {
	*(( uint8_t*) P_dst++) = *(( uint8_t*) P_src++) ;
	}
	//init .bss with zero
	uint32_t bss_size = ( uint8_t*)&_E_bss - ( uint8_t*)&_S_bss ;
	P_dst = ( uint8_t*) &_S_bss ;
	for ( i = 0 ;i<bss_size ;i++ ){
	*(( uint8_t*) P_dst++) = ( uint8_t)0 ;
	}
	//Jump to main
	main();
}
