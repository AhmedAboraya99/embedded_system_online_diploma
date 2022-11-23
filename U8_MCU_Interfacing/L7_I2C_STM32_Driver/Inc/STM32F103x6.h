#ifndef _STM32F103X6_H_
#define _STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------
#include "Bit_Math.h"
#include "Platform_Types.h"
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

#define GPIOA_Base			(Peripherals_Base+0x00010800UL)
#define GPIOB_Base			(Peripherals_Base+0x00010C00UL)
#define GPIOC_Base			(Peripherals_Base+0x00011000UL)
#define GPIOD_Base			(Peripherals_Base+0x00011400UL)
#define GPIOE_Base			(Peripherals_Base+0x00011800UL)

#define EXTI_Base			(Peripherals_Base+0x00010400UL)
#define AFIO_Base			(Peripherals_Base+0x00010000UL)

#define USART1_Base			(Peripherals_Base+0x00013800UL)



//SPI1
#define SPI1_Base			(Peripherals_Base+0x00013000UL)
//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

#define RCC_Base			(Peripherals_Base+0x00021000UL)

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------
#define USART2_Base			(Peripherals_Base+0x00004400UL)
#define USART3_Base			(Peripherals_Base+0x00004800UL)

//SPI
#define SPI2_Base			(Peripherals_Base+0x00003800UL)
#define SPI3_Base			(Peripherals_Base+0x00003C00UL)

//I2C
#define I2C1_Base			(Peripherals_Base+0x00005400UL)
#define I2C2_Base			(Peripherals_Base+0x00005800UL)

//NVIC
#define NVIC_BASE						0xE000E100UL
#define NVIC_ISER0						*(vuint32_t*)(NVIC_BASE + 0x000)
#define NVIC_ISER1						*(vuint32_t*)(NVIC_BASE + 0x004)
#define NVIC_ISER2						*(vuint32_t*)(NVIC_BASE + 0x008)
#define NVIC_ICER0						*(vuint32_t*)(NVIC_BASE + 0x080)
#define NVIC_ICER1						*(vuint32_t*)(NVIC_BASE + 0x084)
#define NVIC_ICER2						*(vuint32_t*)(NVIC_BASE + 0x088)


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	vuint32_t CRL;
	vuint32_t CRH;
	vuint32_t IDR;
	vuint32_t ODR;
	vuint32_t BSRR;
	vuint32_t BRR;
	vuint32_t LCKR;

}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	vuint32_t EVCR;
	vuint32_t MAPR;
	vuint32_t EXTICR[4];
	uint32_t 	RESERVED0;
	vuint32_t MAPR2;

}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	vuint32_t IMR;
	vuint32_t EMR;
	vuint32_t RTSR;
	vuint32_t FTSR;
	vuint32_t SWIER;
	vuint32_t PR;

}EXTI_TypeDef;


typedef struct{

	vuint32_t SR;
	vuint32_t DR;
	vuint32_t BRR;
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t CR3;
	vuint32_t GTPR;

}USART_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	vuint32_t SPI_CR1;
	vuint32_t SPI_CR2;
	vuint32_t SPI_SR;
	vuint32_t SPI_DR;
	vuint32_t SPI_CRCPR;
	vuint32_t SPI_RXCRCR;
	vuint32_t SPI_TXCRCR;
	vuint32_t SPI_I2SCFGR;
	vuint32_t SPI_I2SPR;
}SPI_TypeDef;

typedef struct{

	volatile union {
		vuint32_t	reg;
		struct{
			vuint32_t PE:1;
			vuint32_t SMBUS:1;
			uint32_t Reserved0:1;
			vuint32_t SMBTYPE:1;
			vuint32_t ENARP:1;
			vuint32_t ENPEC:1;
			vuint32_t ENGC:1;
			vuint32_t NOSTRETCH:1;
			vuint32_t START:1;
			vuint32_t STOP:1;
			vuint32_t ACK:1; /* Acknowledge enable: when Set > Acknowledge returned after a byte is received (matched address or data) */
			vuint32_t POS:1;
			vuint32_t PEC:1;
			vuint32_t ALERT:1;
			uint32_t Reserved1:1;
			vuint32_t SWRST:1;
		}bits;
	}I2C_CR1;
	volatile union {
		vuint32_t	reg;
		struct{
			vuint32_t FREQ:6;
			uint32_t Reserved0:1;
			vuint32_t ITEREN:1;
			vuint32_t ITEVTEN:1;
			vuint32_t ITBUFEN:1;
			vuint32_t DMAEN:1;
			vuint32_t LAST:1;
			uint32_t Reserved1:3;
		}bits;
	}I2C_CR2;
	volatile union {
		vuint32_t	reg;
		struct{
			vuint32_t ADD0:1;
			vuint32_t ADD:9;
			uint32_t Reserved:5;
			vuint32_t ADDMODE:1;
		}bits;
	}I2C_OAR1;
	volatile union {
		vuint32_t	reg;
		struct{
			vuint32_t ENDUAL:1;
			vuint32_t ADD2:7;
			uint32_t Reserved:8;
		}bits;
	}I2C_OAR2;
	volatile union {
		vuint32_t	reg;
		struct{
			vuint32_t DR:8;
			uint32_t Reserved:8;
		}bits;
	}I2C_DR;
	volatile union {
		vuint32_t	reg;
		struct{
			vuint32_t SB:1;			//Start bit (Master mode) Set when a Start condition generated.Cleared by reading SR1 followed by writing DR, or when PE=0
			uint32_t ADDR:1;		//Address sent (master mode)/matched (slave mode) >>cleared by reading SR1 followed reading SR2, or by hardware when PE=0.
			vuint32_t BTF:1;		//Byte transfer finished >> Set by hardware when NOSTRETCH=0
			vuint32_t ADD10:1;
			vuint32_t STOPF:1;
			uint32_t Reserved0:1;
			vuint32_t RxNE:1;
			vuint32_t TxE:1;
			vuint32_t BERR:1;
			vuint32_t ARLO:1;
			vuint32_t AF:1;
			vuint32_t OVR:1;
			vuint32_t PECERR:1;
			uint32_t Reserved1:1;
			vuint32_t TIMEOUT:1;
			vuint32_t SMBALERT :1;
		}bits;
	}I2C_SR1;
	volatile union {
		vuint32_t	reg;
		struct{
			vuint32_t MSL:1;			//"r" Master/slave
			vuint32_t BUSY:1;			//"r"Bus busy : Set by hardware once detection of SDA or SCL low _ cleared when Stop condition
			vuint32_t TRA:1;			//"r" Data bytes Transmitter/receiver
			uint32_t Reserved:1;
			vuint32_t GENCALL:1;		// General call address receive detection (Slave mode)
			vuint32_t SMBDEFAULT:1;
			vuint32_t SMBHOST:1;
			vuint32_t DUALF:1;			// Dual flag (Slave mode) >> Received address matched with 0: OAR1 1: with OAR2
			vuint32_t PEC:8;
		}bits;
	}I2C_SR2;
	volatile union {
		vuint32_t	reg;
		struct{
			vuint32_t CCR:12;		//Clock control register in Fm/Sm mode (Master mode)
			uint32_t Reserved:2;
			vuint32_t DUTY:1;		//Fm mode duty cycle
			vuint32_t F_S:1;		//I2C master mode selection
		}bits;
	}I2C_CCR;
	volatile union {
		vuint32_t	reg;
		struct{
			vuint32_t TRISE:6;		// Maximum rise time in Fm/Sm mode (Master mode)
			uint32_t Reserved:10;
		}bits;
	} I2C_TRISE;
}I2C_TypeDef;

//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	vuint32_t CR;
	vuint32_t CFGR;
	vuint32_t CIR;
	vuint32_t APB2RSTR;
	vuint32_t APB1RSTR;
	vuint32_t AHBENR;
	vuint32_t APB2ENR;
	vuint32_t APB1ENR;
	vuint32_t BDCR;
	vuint32_t CSR;
	vuint32_t AHBSTR;
	vuint32_t CFGR2;

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

I2C_TypeDef *I2C1 = (I2C_TypeDef *)   I2C1_Base;
I2C_TypeDef *I2C2 = (I2C_TypeDef *)   I2C2_Base;


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
//I2C
#define I2C1_EV_IRQ		31
#define I2C1_ER_IRQ		32
#define I2C2_EV_IRQ		33
#define I2C2_ER_IRQ		34

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

//I2C
#define NVIC_IRQ31_I2C1_EV_ENABLE()				(NVIC_ISER0 |= 1<<(I2C1_EV_IRQ))
#define NVIC_IRQ32_I2C1_ER_ENABLE()				(NVIC_ISER1 |= 1<<(I2C1_ER_IRQ-32))
#define NVIC_IRQ33_I2C2_EV_ENABLE()				(NVIC_ISER1 |= 1<<(I2C2_EV_IRQ-32))
#define NVIC_IRQ34_I2C2_ER_ENABLE()				(NVIC_ISER1 |= 1<<(I2C2_ER_IRQ-32))

#define NVIC_IRQ31_I2C1_EV_DISABLE()			(NVIC_ICER0 |= 1<<(I2C1_EV_IRQ))
#define NVIC_IRQ32_I2C1_ER_DISABLE()			(NVIC_ICER1 |= 1<<(I2C1_ER_IRQ-32))
#define NVIC_IRQ33_I2C2_EV_DISABLE()			(NVIC_ICER1 |= 1<<(I2C2_EV_IRQ-32))
#define NVIC_IRQ34_I2C2_ER_DISABLE()			(NVIC_ICER1 |= 1<<(I2C2_ER_IRQ-32))

#endif

