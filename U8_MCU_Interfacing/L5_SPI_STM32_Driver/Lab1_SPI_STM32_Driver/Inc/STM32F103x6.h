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

#define USART1_Base		(Peripherals_Base+0x00013800UL)



//SPI1
#define SPI1_Base				(Peripherals_Base+0x00013000UL)
//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

#define RCC_Base		(Peripherals_Base+0x00021000UL)

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------
#define USART2_Base		(Peripherals_Base+0x00004400UL)
#define USART3_Base		(Peripherals_Base+0x00004800UL)

//SPI2
#define SPI2_Base			(Peripherals_Base+0x00003800UL)


//NVIC
#define NVIC_BASE						0xE000E100UL
#define NVIC_ISER0						*(volatile uint32_t*)(NVIC_BASE + 0x000)
#define NVIC_ISER1						*(volatile uint32_t*)(NVIC_BASE + 0x004)
#define NVIC_ISER2						*(volatile uint32_t*)(NVIC_BASE + 0x008)
#define NVIC_ICER0						*(volatile uint32_t*)(NVIC_BASE + 0x080)
#define NVIC_ICER1						*(volatile uint32_t*)(NVIC_BASE + 0x084)
#define NVIC_ICER2						*(volatile uint32_t*)(NVIC_BASE + 0x088)


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
	volatile uint32_t EXTICR[4];
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


typedef struct{

	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;

}USART_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t SPI_CR1;
	volatile uint32_t SPI_CR2;
	volatile uint32_t SPI_SR;
	volatile uint32_t SPI_DR;
	volatile uint32_t SPI_CRCPR;
	volatile uint32_t SPI_RXCRCR;
	volatile uint32_t SPI_TXCRCR;
	volatile uint32_t SPI_I2SCFGR;
	volatile uint32_t SPI_I2SPR;
}SPI_TypeDef;
//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------
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
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;

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

EXTI_TypeDef *EXTI  =	(EXTI_TypeDef *)  EXTI_Base;
AFIO_TypeDef *AFIO  = 	(AFIO_TypeDef *)  AFIO_Base;
RCC_TypeDef  *RCC   = 	(RCC_TypeDef *)   RCC_Base;

USART_TypeDef  *USART1   = (USART_TypeDef *)   USART1_Base;
USART_TypeDef  *USART2   = (USART_TypeDef *)   USART2_Base;
USART_TypeDef  *USART3   = (USART_TypeDef *)   USART3_Base;

SPI_TypeDef *SPI1 = (SPI_TypeDef *)   SPI1_Base;

SPI_TypeDef *SPI2 = (SPI_TypeDef *)   SPI2_Base;



//-*-*-*-*-*-*-*-*-*-*-*-
//IVT Macros
//-*-*-*-*-*-*-*-*-*-*-*
// @ref IVT_IRQ_Number
#define EXTI0_IRQ	6
#define EXTI1_IRQ	7
#define EXTI2_IRQ	8
#define EXTI3_IRQ	9
#define EXTI4_IRQ	10
#define EXTI5_IRQ	23
#define EXTI6_IRQ	23
#define EXTI7_IRQ	23
#define EXTI8_IRQ	23
#define EXTI9_IRQ	23
#define EXTI10_IRQ	40
#define EXTI11_IRQ	40
#define EXTI12_IRQ	40
#define EXTI13_IRQ	40
#define EXTI14_IRQ	40
#define EXTI15_IRQ	40

#define USART1_IRQ	37
#define USART2_IRQ	38
#define USART3_IRQ	39

//SPI
#define SPI1_IRQ		35
#define SPI2_IRQ		36

// NVIC_IRQ Enable / Disable
#define NVIC_IRQ6_EXTI0_ENABLE()			(NVIC_ISER0 |= 1<<EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_ENABLE()			(NVIC_ISER0 |= 1<<EXTI1_IRQ)
#define NVIC_IRQ8_EXTI2_ENABLE()			(NVIC_ISER0 |= 1<<EXTI2_IRQ)
#define NVIC_IRQ9_EXTI3_ENABLE()			(NVIC_ISER0 |= 1<<EXTI3_IRQ)
#define NVIC_IRQ10_EXTI4_ENABLE()			(NVIC_ISER0 |= 1<<EXTI4_IRQ)
#define NVIC_IRQ23_EXTI5_9_ENABLE()			(NVIC_ISER0 |= 1<<EXTI5_IRQ)
#define NVIC_IRQ40_EXTI10_15_ENABLE()		(NVIC_ISER1 |= 1<<8) 	//40-32

#define NVIC_IRQ6_EXTI0_DISABLE()			(NVIC_ICER0 |= 1<<EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_DISABLE()			(NVIC_ICER0 |= 1<<EXTI1_IRQ)
#define NVIC_IRQ8_EXTI2_DISABLE()			(NVIC_ICER0 |= 1<<EXTI2_IRQ)
#define NVIC_IRQ9_EXTI3_DISABLE()			(NVIC_ICER0 |= 1<<EXTI3_IRQ)
#define NVIC_IRQ10_EXTI4_DISABLE()			(NVIC_ICER0 |= 1<<EXTI4_IRQ)
#define NVIC_IRQ23_EXTI5_9_DISABLE()		(NVIC_ICER0 |= 1<<EXTI5_IRQ)
#define NVIC_IRQ40_EXTI10_15_DISABLE()		(NVIC_ICER1 |= 1<<8)	//40-32

//USART
#define NVIC_IRQ37_USART1_ENABLE()			(NVIC_ISER1 |= 1<<(USART1_IRQ-32))
#define NVIC_IRQ38_USART2_ENABLE()			(NVIC_ISER1 |= 1<<(USART2_IRQ-32))
#define NVIC_IRQ39_USART3_ENABLE()			(NVIC_ISER1 |= 1<<(USART3_IRQ-32))

#define NVIC_IRQ37_USART1_DISABLE()			(NVIC_ICER1 |= 1<<(USART1_IRQ-32))
#define NVIC_IRQ38_USART2_DISABLE()			(NVIC_ICER1 |= 1<<(USART2_IRQ-32))
#define NVIC_IRQ39_USART3_DISABLE()			(NVIC_ICER1 |= 1<<(USART3_IRQ-32))

//SPI
#define NVIC_IRQ35_SPI1_ENABLE()				(NVIC_ISER1 |= 1<<(SPI1_IRQ-32))
#define NVIC_IRQ36_SPI2_ENABLE()				(NVIC_ISER1 |= 1<<(SPI2_IRQ-32))

#define NVIC_IRQ35_SPI1_DISABLE()				(NVIC_ICER1 |= 1<<(SPI1_IRQ-32))
#define NVIC_IRQ36_SPI2_DISABLE()				(NVIC_ICER1 |= 1<<(SPI2_IRQ-32))

#endif

