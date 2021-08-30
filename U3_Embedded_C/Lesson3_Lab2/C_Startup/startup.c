#include "Platform_Types.h"
extern int main(void);
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;
extern unsigned int _E_text ;
extern unsigned int _STACK_SP ;

//define vector handlers
void Reset_Handler (void)
{
	//copy data from ROM to RAM
	unsigned int DATA_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA ;
	unsigned char* P_src = (unsigned char*)&_E_text ;
	unsigned char* P_dst = (unsigned char*)&_S_DATA ;
	for (int i=0 ;i < DATA_size ;i++ ) {
	*((unsigned char*) P_dst++) = *((unsigned char*) P_src++) ;
	}

	//init .bss with zero
	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss ;
	P_dst = (unsigned char*) &_S_bss ;
	for (int i=0 ;i<bss_size ;i++ ){
	*((unsigned char*) P_dst++) = (unsigned char)0 ;
	}

	// jump to main
	main();
}
 void Default_Handler(void)
{
	Reset_Handler();
}
/* make handlers point to the same address
 and do the same action using alias */

/*using weak attribute to make the symbol of vector
 "weak" can be defined more than once */
void NMI_Handler(void) __attribute__ ((weak,alias ("Default_Handler")));;
void H_fault_Handler(void) __attribute__ ((weak,alias ("Default_Handler")));;
void MM_Fault_Handler(void)__attribute__ ((weak,alias ("Default_Handler")));;
void Bus_Fault(void) __attribute__ ((weak,alias ("Default_Handler")));;
void Usage_Fault_Handler(void) __attribute__ ((weak,alias ("Default_Handler")));;

/* create vector section in text section using array and _attribute_ pragma */
uint32_t vectors[]__attribute__((section(".vectors"))) = {
(uint32_t)&_STACK_SP,
(uint32_t)&Reset_Handler,
(uint32_t)&NMI_Handler ,
(uint32_t)&H_fault_Handler ,
(uint32_t)&MM_Fault_Handler ,
(uint32_t)&Bus_Fault ,
(uint32_t)&Usage_Fault_Handler
};