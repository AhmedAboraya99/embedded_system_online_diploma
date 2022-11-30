/*
 * Atmega32_TIMER0_CTC.c
 *
 * Created: 11/27/2022 6:30:43 PM
 *  Author: Ahmed Aboraya
 */ 

//-----------------------------
//Includes : Header Files
//-----------------------------

#include "Atmega32_TIMER0_CTC.h"

/* ================================================================ */
/* ======================= Generic Variables ====================== */
/* ================================================================ */
vuint32_t Timer_Counter = 0, NumofCompare = 0;


/* ================================================================ */
/* ======================= Functions Prototypes =================== */
/* ================================================================ */
static void TIMER0_CompareMatch_CallBackHandler(void);
static void TIMER0_Overflow_CallBackHandler(void);

/* ================================================================ */
/* ======================= CallBack Functions ====================== */
/* ================================================================ */
static void TIMER0_CompareMatch_CallBackHandler(void)
{
	NumofCompare++;
	if(NumofCompare == 50)
	{
		
		TOGGLE_Pin(PORTB, DIO_PIN0);
		/* Clear Counter */
		NumofCompare = 0;
	}
	
}

static void TIMER0_Overflow_CallBackHandler(void)
{
	Timer_Counter++;
	if(Timer_Counter == 3921) //3921 = 1 sec
	{
		/* Toggle Led every one second */
		TOGGLE_Pin(PORTD, DIO_PIN0);
		
		/* Clear Counter */
		Timer_Counter = 0;
	}
	
}

/* ================================================================ */
/* ======================= Main Program ========================== */
/* ================================================================ */

void TIMER0_CTC_Test(uint8_t CompareVal){
		
		//Configure PINB0&PIND0 as Output
		MCAL_PIN_Direction(DIOB, DIO_PIN0, OUTPUT_PIN);
		MCAL_PIN_Direction(DIOD, DIO_PIN0, OUTPUT_PIN);
		//set Compare value
		MCAL_TIMER0_SetCompareVal(CompareVal);
		//set timer configuration
		TIMER0_Config_t Timer0_cfg;
		Timer0_cfg.TIMER0_Mode = TIMER0_CTC_MODE;
		Timer0_cfg.Compare_Match_Mode = TIMER0_NONINVERTING_CLEAR;
		Timer0_cfg.TIMER0_ClockSrc = TIMER0_CLKPRESCALER_8;
		Timer0_cfg.TIMER0_IRQ = TIMER0_IRQ_TOIE_OCIE;
		Timer0_cfg.P_TIMER0_IRQ_CallBack[OVERFLOW_INDEX] = TIMER0_Overflow_CallBackHandler;
		Timer0_cfg.P_TIMER0_IRQ_CallBack[COMPAREMATCH_INDEX] = TIMER0_CompareMatch_CallBackHandler;
		MCAL_TIMER0_Init(&Timer0_cfg);
		
		 	while(1)
		 	{

		 	}
}