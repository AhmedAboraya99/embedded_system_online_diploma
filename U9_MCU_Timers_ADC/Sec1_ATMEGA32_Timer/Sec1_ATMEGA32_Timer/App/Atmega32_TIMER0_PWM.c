/*
 * Atmega32_TIMER0_PWM.c
 *
 * Created: 11/27/2022 7:05:41 PM
 *  Author: Ahmed Aboraya
 */ 


//-----------------------------
//Includes : Header Files
//-----------------------------

#include "Atmega32_TIMER0_PWM.h"

/* ================================================================ */
/* ======================= Generic Variables ====================== */
/* ================================================================ */


/* ================================================================ */
/* ======================= Functions Prototypes =================== */
/* ================================================================ */
static void TIMER0_CompareMatch_PWM_Handler(void);

/* ================================================================ */
/* ======================= CallBack Functions ====================== */
/* ================================================================ */
static void TIMER0_CompareMatch_PWM_Handler(void)
{
	RESET_Pin(PORTB, DIO_PIN3);

	TOGGLE_Pin(PORTD, DIO_PIN0);
}

static void TIMER0_Overflow_PWM_Handler(){
	TOGGLE_Pin(PORTD, DIO_PIN0);

}
/* =========== Main Program ========== */
void TIMER0_PWM_Test(uint8_t DutyCycle)
{
	//Configure PIND1&2 as Output
	MCAL_PIN_Direction(DIOD, DIO_PIN0, OUTPUT_PIN);
	
	//set timer configuration
	TIMER0_Config_t TIMER0_PWM_cfg;
	TIMER0_PWM_cfg.TIMER0_Mode = TIMER0_FAST_PWM_MODE;
	TIMER0_PWM_cfg.Compare_Match_Mode = TIMER0_INVERTING_SET;
	TIMER0_PWM_cfg.TIMER0_ClockSrc = TIMER0_CLKPRESCALER_256;
	TIMER0_PWM_cfg.TIMER0_IRQ = TIMER0_IRQ_TOIE_OCIE;
	TIMER0_PWM_cfg.P_TIMER0_IRQ_CallBack[OVERFLOW_INDEX] = TIMER0_Overflow_PWM_Handler;
	TIMER0_PWM_cfg.P_TIMER0_IRQ_CallBack[COMPAREMATCH_INDEX] = TIMER0_CompareMatch_PWM_Handler;
	MCAL_TIMER0_Init(&TIMER0_PWM_cfg);
	
	MCAL_PWM_DutyCycle(DutyCycle);

	while (1)
	{
		

	}
}