#include "Platform_Types.h"
//register address
#define RCC_BASE 	 0x40021000
#define GPIOA_BASE 	 0x40010800  //base address of Port A
#define RCC_APB2ENR	 *(vuint32 *)(RCC_BASE + 0x18)
#define GPIOA_CRH 	 *(vuint32 *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR 	 *(vuint32 *)(GPIOA_BASE + 0x0C)

//bit fields
#define RCC_IOPEAN (1<<2)
#define GPIOA13    (1UL<<13)

//make access to pin 13
typedef union{
	vuint32 all_fields;
	struct {
		vuint32 reserved:13 ;
		vuint32 P_13:1;
	}Pin;
} R_ODR_t;
//add offset address of ODR register
volatile R_ODR_t* R_ODR= (volatile R_ODR_t*)(GPIOA_BASE + 0x0C);

int main(void)
{
	RCC_APB2ENR |= RCC_IOPEAN; //set bit 2
	GPIOA_CRH &= 0xFF0FFFFF ; //clear 4 bits (20-24)
	GPIOA_CRH |= 0x00200000; //set the same 4 bits

	/* Loop forever */
	while(1){
	int i;
	R_ODR->Pin.P_13 = 1; 		 //set bit 13
	for(i = 0; i<5000;i++); // delay
	R_ODR->Pin.P_13 = 0;		 // clear bit 13
	for(i = 0; i<5000;i++); // delay
	}

}
