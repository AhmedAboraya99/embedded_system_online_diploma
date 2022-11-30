/*
 * Timer.c
 *
 * Created: 11/26/2022 11:24:02 AM
 *  Author: Ahmed Aboraya
 */ 

//-----------------------------
//Includes
//-----------------------------


#include "Timer.h"

/* ================================================================ */
/* ======================= Generic Variables ====================== */
/* ================================================================ */

void (*GP_TIMER0_IRQ_CallBack[2])(void) = {NULL, NULL};

TIMER0_Config_t G_TIMER0_Config;
/* ================================================================ */
/* =========== APIs Supported by "MCAL TIMER0 DRIVER" ============= */
/* ================================================================ */

void MCAL_TIMER0_Init(TIMER0_Config_t *TIMER0_Config){
		uint8_t Temp_TCCR0 = 0;
		/* Save TIMER0 Current Configuration */
		G_TIMER0_Config = *TIMER0_Config;
		
		/* Select Timer Mode */
		RESET_Config(Temp_TCCR0, TIMER0_NORMAL_MODE);
		if (TIMER0_Config->TIMER0_Mode != TIMER0_NORMAL_MODE)
			SET_Config(Temp_TCCR0, TIMER0_Config->TIMER0_Mode);
		
		/* Set  Compare Output Mode  */
		RESET_Config(Temp_TCCR0, TIMER0_NORMAL_PORT_OP);
		if(TIMER0_Config->Compare_Match_Mode != TIMER0_NORMAL_PORT_OP)		//OC0 Connected
		{
			if(TIMER0_Config->Compare_Match_Mode != TIMER0_TOGGLE_OC0_CM || TIMER0_Config->TIMER0_Mode == TIMER0_NORMAL_MODE){
				/* Configure OC0 (PINB3) as Output */
				MCAL_PIN_Direction(DIOB, DIO_PIN3, OUTPUT_PIN);

			}	//else OC0 is Disconnected
				//Clear or Set or Toggle OC0 on Compare match
				SET_Config(Temp_TCCR0, TIMER0_Config->Compare_Match_Mode);
		}

		/* Select Clock Source */
		RESET_Config(Temp_TCCR0, TIMER0_NOCLKSRC);
		if(TIMER0_Config->TIMER0_ClockSrc != TIMER0_NOCLKSRC){
			if(TIMER0_Config->TIMER0_ClockSrc == TIMER0_EXTCLKSRC_FALLING || TIMER0_Config->TIMER0_ClockSrc == TIMER0_EXTCLKSRC_RISING)
			{
				/* Configure T0 (PINB0) as Input */
				MCAL_PIN_Direction(DIOB, DIO_PIN0, INPUT_PIN);
			}
			SET_Config(Temp_TCCR0, TIMER0_Config->TIMER0_ClockSrc);
		}
		
		/* Enable Or Disable IRQ */

		if(TIMER0_Config->TIMER0_IRQ != TIMER0_IRQ_DISABLE)
		{
			/* Enable Global Interrupt */
			Global_Interrupt_Enable();
			SET_Config(TIMSK0, TIMER0_Config->TIMER0_IRQ);
			
		}else {
			/* Disable Global Interrupt */
			Global_Interrupt_Disable();
			RESET_Config(TIMSK0, TIMER0_IRQ_DISABLE);
		}
		/* Call back function address */
		GP_TIMER0_IRQ_CallBack[OVERFLOW_INDEX] = TIMER0_Config->P_TIMER0_IRQ_CallBack[OVERFLOW_INDEX];
		GP_TIMER0_IRQ_CallBack[COMPAREMATCH_INDEX] = TIMER0_Config->P_TIMER0_IRQ_CallBack[COMPAREMATCH_INDEX];
		ASSIGN_Port(TCCR0_Reg, Temp_TCCR0);
		
}

void MCAL_TIMER0_DeInit(void){
	RESET_Port(TCCR0_Reg);
	ASSIGN_Port(TIMSK0, TIMER0_IRQ_DISABLE);
}


/**================================================================
* @Fn			- MCAL_TIMER0_GetCountVal
* @brief 		- Get Timer counter value
* @param [in] 	- countVal :  8-bit value of counter value (TCNT0) Register
* @retval		- none
*/
void MCAL_TIMER0_GetCountVal(uint8_t* countVal){
	countVal = TCNT0;
}
/**================================================================
* @Fn			- MCAL_TIMER0_SetCompareVal
* @brief 		- The Output Compare Register contains an 8-bit value
*				  that is continuously compared with the counter value (TCNT0)
* @param [in] 	- compVal :  8-bit value of  Output Compare Register
* @retval		- none
*/
void MCAL_TIMER0_SetCompareVal(uint8_t compVal){
	OCR0 = compVal;
}


/**================================================================
 * @Fn 				-	MCAL_PWM_DutyCycle
 * @brief 			-	Set PWM duty cycle in Fast or Phase Correct PWM Mode
 * @param [in] 		- 	duty_cycle : Value of PWM duty cycle (from 0 to 100)
 * @retval 			-	none
 */
void MCAL_PWM_DutyCycle(uint8_t Duty_Cycle){
	
	////The N variable represents the prescale factor (1, 8, 64, 256, or 1024)
	//uint8_t prescale_factor[5] = {1, 8, 64, 256, 1024};
	//uint8_t N = prescale_factor[TIMER0->TCCR0.bits.CS0n-1];
	//uint8_t Fpwm = 8000000 /(N*510);
	if( 0< Duty_Cycle && Duty_Cycle <= 100){
		if(G_TIMER0_Config.TIMER0_Mode != TIMER0_NORMAL_MODE ||G_TIMER0_Config.TIMER0_Mode != TIMER0_CTC_MODE){
			if(G_TIMER0_Config.TIMER0_Mode == TIMER0_PHASE_PWM_MODE ){
				OCR0 = (uint8_t)(255-((255*Duty_Cycle)/100)/2);
			}else if(G_TIMER0_Config.TIMER0_Mode == TIMER0_FAST_PWM_MODE)
			{
				if(G_TIMER0_Config.Compare_Match_Mode == TIMER0_NONINVERTING_CLEAR)
					OCR0 = (uint8_t)((255*Duty_Cycle)/100);
			
				else if(G_TIMER0_Config.Compare_Match_Mode == TIMER0_INVERTING_SET)
					OCR0 = (uint8_t)(255 -((255*Duty_Cycle)/100));
				
			}
		}
	}
}


/* ================================================================ */
/* =========== ISR APIs for "MCAL TIMER0 DRIVER" ================== */
/* ================================================================ */

/* OVERFLOW ISR */
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void){
	GP_TIMER0_IRQ_CallBack[OVERFLOW_INDEX]();
}
/* COMPARE MATCH ISR */

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void){
	GP_TIMER0_IRQ_CallBack[COMPAREMATCH_INDEX]();

}
