#ifndef _STM32F103X6_H_
#define _STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------
#include <stdlib.h>
#include <stdint.h>

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define Flash_Memory_Base 				0x08000000UL
#define	System_Memory_Base				0x1FFFF000UL

#define	SRAM_Base						0x20000000UL
#define Peripherals_Base 				0x40000000UL
#define Cortex_M3_Peripherals_Base 		0xE0000000UL


//-----------------------------
//Base addresses for ABP2 Peripherals
//-----------------------------
//GPIO

//0x4001 1400 - 0x4001 17FF GPIO Port D
//0x4001 1000 - 0x4001 13FF GPIO Port C
//0x4001 0C00 - 0x4001 0FFF GPIO Port B
//0x4001 0800 - 0x4001 0BFF GPIO Port A
//0x4001 0400 - 0x4001 07FF EXTI Section
//0x4001 0000 - 0x4001 03FF AFIO

#define GPIOA_Base		(Peripherals_Base+0x00010800UL)
#define GPIOB_Base		(Peripherals_Base+0x00010C00UL)
#define GPIOC_Base		(Peripherals_Base+0x00011000UL)
#define GPIOD_Base		(Peripherals_Base+0x00011400UL)
#define GPIOE_Base		(Peripherals_Base+0x00011800UL)

#define EXTI_Base		(Peripherals_Base+0x00010400UL)
#define AFIO_Base		(Peripherals_Base+0x00010000UL)

//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

#define RCC_Base		(Peripherals_Base+0x00021000UL)


//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;

}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	uint32_t 	RESERVED0;
	volatile uint32_t MAPR2;

}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;

}RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants
//-*-*-*-*-*-*-*-*-*-*-*
//#define GPIOA						((GPIO_TypeDef*)GPIOA_Base)
//#define GPIOB						((GPIO_TypeDef*)GPIOB_Base)
//#define GPIOC						((GPIO_TypeDef*)GPIOC_Base)
//#define GPIOD						((GPIO_TypeDef*)GPIOD_Base)
//#define GPIOE						((GPIO_TypeDef*)GPIOE_Base)
GPIO_TypeDef *GPIOA = 	(GPIO_TypeDef *) GPIOA_Base;
GPIO_TypeDef *GPIOB = 	(GPIO_TypeDef *) GPIOB_Base;
GPIO_TypeDef *GPIOC = 	(GPIO_TypeDef *) GPIOC_Base;
GPIO_TypeDef *GPIOD = 	(GPIO_TypeDef *) GPIOD_Base;
GPIO_TypeDef *GPIOE = 	(GPIO_TypeDef *) GPIOE_Base;

EXTI_TypeDef *EXTI =	(EXTI_TypeDef *)  EXTI_Base;
AFIO_TypeDef *AFIO = 	(AFIO_TypeDef *)  AFIO_Base;
RCC_TypeDef *RCC   = 	(RCC_TypeDef *)   RCC_Base;

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLOCK_EN() 	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLOCK_EN() 	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLOCK_EN() 	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOE_CLOCK_EN() 	(RCC->APB2ENR |= 1<<5)

#define RCC_AFIO_CLOCK_EN() 	(RCC->APB2ENR |= 1<<0)



#endif
