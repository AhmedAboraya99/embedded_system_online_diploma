/*
 * Timer.h
 *
 * Created: 11/26/2022 11:24:18 AM
 *  Author: Ahmed Aboraya
 */ 


#ifndef TIMER_H_
#define TIMER_H_

//-----------------------------
//Includes
//-----------------------------

#include "DIO_Driver.h"

/* ================================================================ */
/* ======================= Generic Macros ========================= */
/* ================================================================ */
#define TCCR0_Reg	TIMER0->TCCR0.reg
#define TIMSK0		TIMER0->TIMSK
#define TCNT0		TIMER0->TCNT0
#define OCR0		TIMER0->OCR0

#define OVERFLOW_INDEX			0
#define COMPAREMATCH_INDEX		1

//-----------------------------
//User type definitions (Enum)
//-----------------------------

//@ref Timer_Clock_Define
typedef enum{
	TIMER0_NOCLKSRC = ~(7<<0),
	TIMER0_NOPRESCALER = 1,
	TIMER0_CLKPRESCALER_8,
	TIMER0_CLKPRESCALER_64,
	TIMER0_CLKPRESCALER_256,
	TIMER0_CLKPRESCALER_1024,
	TIMER0_EXTCLKSRC_FALLING,
	TIMER0_EXTCLKSRC_RISING,
}TIMER0_ClkSrc_t;

//@ref TIMER0_Mode_Define
typedef enum{
	TIMER0_NORMAL_MODE = ~(1<<3)|~(1<<6),		//(WGM01:0 = 0). In this mode the counting direction is always up (incrementing), and no counter clear is performed. 
	TIMER0_PHASE_PWM_MODE = (1<<3),				//(WGM01:0 = 1) provides a high resolution (phase correct PWM) waveform generation option.
	TIMER0_CTC_MODE = (1<<6),					//(WGM01:0 = 2) Clear Timer on Compare Match (CTC) Mode
	TIMER0_FAST_PWM_MODE = (1<<3)|(1<<6),		//(WGM01:0 = 3) provides a high frequency PWM waveform generation option
}TIMER0_Mode_t;

//@ref Compare_Mode_Define
typedef enum{
	TIMER0_NORMAL_PORT_OP = ~(1<<4)|~(1<<5),
	TIMER0_TOGGLE_OC0_CM = (1<<4),
	TIMER0_NONINVERTING_CLEAR= (1<<5),
	TIMER0_INVERTING_SET = (1<<4)|(1<<5),
}Compare_Mode_t;

// @ref TIMER0_IRQ_Define
typedef enum{
	TIMER0_IRQ_DISABLE = ~(3<<0),
	TIMER0_IRQ_TOIE  = 1,
	TIMER0_IRQ_OCIE,
	TIMER0_IRQ_TOIE_OCIE
}TIMER0_IRQ_t;
//-----------------------------
//User type definitions (structures)
//-----------------------------


//-----------------------------
//Configure structure for Timer
//-----------------------------
typedef struct{
	TIMER0_Mode_t		TIMER0_Mode;			//control the counting sequence, the maximum value and type of Waveform Generation of the counter
	// This parameter must be set based on @ref TIMER0_Mode_Define
	TIMER0_ClkSrc_t		TIMER0_ClockSrc;		//select the clock source to be used by the Timer/Counter0.
	// This parameter must be set based on @ref Timer_Clock_Define
	Compare_Mode_t		Compare_Match_Mode;		//Compare Match Output Mode
	// This parameter must be set based on @ref Compare_Mode_Define
	TIMER0_IRQ_t		TIMER0_IRQ;				// Enable or Disable IRQ
	// This parameter must be set based on @ref TIMER0_IRQ_Define
		
	void (*P_TIMER0_IRQ_CallBack[2])(void);				//set the C Function which will be called once TIMER0 overflow or/and Compare Match IRQ Happens
	
		
}TIMER0_Config_t;


/* ================================================================ */
/* =========== APIs Supported by "MCAL TIMER0 DRIVER" ============= */
/* ================================================================ */

void MCAL_TIMER0_Init(TIMER0_Config_t *TIMER0_Config);
void MCAL_TIMER0_DeInit(void);
void MCAL_TIMER0_GetCountVal(uint8_t* countVal);
void MCAL_TIMER0_SetCompareVal(uint8_t compVal);

void MCAL_PWM_DutyCycle(uint8_t Duty_Cycle);


#endif /* TIMER_H_ */