/*
 * ADC.c
 *
 * Created: 12/4/2022 4:20:09 PM
 *  Author: ahmed
 */ 

//-----------------------------
//Includes
//-----------------------------
#include "ADC.h"

/* ================================================================ */
/* ======================= Generic Variables ====================== */
/* ================================================================ */



/* ================================================================ */
/* ============ APIs Supported by "MCAL ADC DRIVER" =============== */
/* ================================================================ */

void MCAL_ADC_Init(ADC_Config_t* ADC_Config){
		uint8_t Temp_ADCSRA = 0;
		/* Save ADC Current Configuration */
		G_ADC_Config = *ADC_Config;
		


		/* Select ADC Mode */
		RESET_Config(Temp_ADCSRA, ADC_STOP_CONVERSION);
		if (ADC_Config->ADC_Mode != ADC_STOP_CONVERSION){
			SET_Config(Temp_ADCSRA, ADC_Config->ADC_Mode);
			
			/* Select Trigger Source */
			if (ADC_Config->ADC_Mode > ADC_SINGLE_CONVERSION_MODE){
				RESET_Config(SFIOR, ADC_FREE_TRIGGERING);
				if (ADC_Config->ADC_Mode != ADC_FREE_RUNNING_MODE)
					SET_Config(SFIOR, ADC_Config->ADC_TriggerSrc);
				
			}
		}
			
		/* Select ADC Voltage Reference */
		RESET_Config(ADMUX_Reg, ADC_AREF_PIN);
		if(ADC_Config->ADC_Reference != ADC_AREF_PIN)
			SET_Config(ADMUX_Reg, ADC_Config->ADC_Reference);
		

		/* Select Prescaler */
		RESET_Config(Temp_ADCSRA, ADC_PRESCALER_2);
		if(ADC_Config->ADC_Prescale != ADC_PRESCALER_2)
			SET_Config(Temp_ADCSRA, ADC_Config->ADC_Prescale);
		
		/* Enable Or Disable IRQ */

		if(ADC_Config->ADC_IRQ != ADC_IRQ_DISABLE)
		{
			/* Enable Global Interrupt */
			Global_Interrupt_Enable();
			SET_Config(Temp_ADCSRA, ADC_IRQ_ENABLE);
			
			}else {
			/* Disable Global Interrupt */
			Global_Interrupt_Disable();
			RESET_Config(Temp_ADCSRA, ADC_IRQ_DISABLE);
		}

	
		/* Assign ADC Control and Status Register*/
		ASSIGN_Port(ADCSRA_Reg, Temp_ADCSRA);
		/* Enable ADC */
		SET_Bitfield(ADC->ADCSRA.bits.ADEN);
}

void MCAL_ADC_DeInit(void){
	RESET_Port(ADCSRA_Reg);
	RESET_Config(SFIOR, ADC_FREE_TRIGGERING);
}


uint16_t MCAL_ADC_Read(ADC_Channels_t Read_Channel){
	uint16_t ADCVal = 0;
	
	/* Select ADC Channel */
	SET_Config(ADMUX_Reg, Read_Channel);
	/* Enable Interrupt for Continuous Conversion */
	if (G_ADC_Config.ADC_Mode != ADC_SINGLE_CONVERSION_MODE)
	{
		SET_Bitfield(ADC->ADCSRA.bits.ADIE);
	}
	/* Start Conversion */	
	SET_Bitfield(ADC->ADCSRA.bits.ADSC);

	
	while(!ADC->ADCSRA.bits.ADIF);

	ADCVal = (ADC->ADCL) | (ADC->ADCH<<8);
	return ADCVal;
}



/* ================================================================ */
/* ================ ISR APIs for "MCAL ADC DRIVER" ================ */
/* ================================================================ */


/* ADC Conversion Complete ISR */

void __vector_16 (void) __attribute__((signal));
void __vector_16 (void){
	
	RESET_Bitfield(ADC->ADCSRA.bits.ADIE);
	
}