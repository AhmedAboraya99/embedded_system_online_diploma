/*
 * ADC.h
 *
 * Created: 12/4/2022 4:19:52 PM
 *  Author: ahmed
 */ 


#ifndef ADC_H_
#define ADC_H_

//-----------------------------
//Includes
//-----------------------------

#include "DIO_Driver.h"

/* ================================================================ */
/* ======================= Generic Macros ========================= */
/* ================================================================ */

#define ADCSRA_Reg		ADC->ADCSRA.reg
#define ADMUX_Reg		ADC->ADMUX.reg
//-----------------------------
//User type definitions (Enum)
//-----------------------------

 //@ref ADC_Mode_Define
 typedef enum{
	 // •  Bit 5,6 –  ADATE: ADC Auto Trigger Enable, ADSC: ADC Start Conversion
	 ADC_STOP_CONVERSION = ~(0b11<<5),
	 ADC_SINGLE_CONVERSION_MODE = (1<<5),
	 ADC_AUTO_TRIGGERING = (1<<5),
	 ADC_FREE_RUNNING_MODE = (1<<5)|(1<<6),
 }ADC_Mode_t;
 
//@ref Reference_Selection_Define
typedef enum{
	//• Bit 7:6 – REFS1:0: Reference Selection Bits
	ADC_AREF_PIN = ~(1<<6)|~(1<<7),
	ADC_EXTERNAL_AVCC = (1<<6),
	ADC_INTERNAL_256V = (1<<6)|(1<<7),
}Ref_Selection_t;

//@ref  ADC_Prescaler_Define
typedef enum{
	// • Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
	ADC_PRESCALER_2 = ~(0b111<<0),
	ADC_PRESCALER_4 = 2,
	ADC_PRESCALER_8,
	ADC_PRESCALER_16,
	ADC_PRESCALER_32,
	ADC_PRESCALER_64,
	ADC_PRESCALER_128,

}ADC_Prescaler_t;


//@ref ADC_Channels_Define
//select ADC Channel to receive from
typedef enum{
	// • Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits
	ADC_CHANNEL0 = 0,
	ADC_CHANNEL1 = 1,
	ADC_CHANNEL2,
	ADC_CHANNEL3,
	ADC_CHANNEL4,
	ADC_CHANNEL5,
	ADC_CHANNEL6,
	ADC_CHANNEL7

}ADC_Channels_t;

 
//@ref  ADC_TriggerSrc_Define
typedef enum{
	// • Bit 7:5 – ADTS2:0: ADC Auto Trigger Source
	ADC_FREE_TRIGGERING = ~(0b111<<5),
	ANALOG_COMPARATOR_TRIGGER = (1<<5),
	EXTERNAL_IRQ0_TRIGGER = (1<<6),
	ADC_COMPMATCH_TRIGGER = (1<<5)|(1<<6),
	ADC_OVERFLOW_TRIGGER = (1<<7),
	TIMER1_COMPMATCHB_TRIGGER = (1<<5)|(1<<7),
	TIMER1_OVERFLOW_TRIGGER = (1<<6)|(1<<7),
	TIMER1_CAPTUREEVENT_TRIGGER = (1<<5)|(1<<6)|(1<<7)

}ADC_TriggerSrc_t;

// @ref ADC_IRQ_Define
typedef enum{
	ADC_IRQ_DISABLE = ~(1<<3),
	ADC_IRQ_ENABLE  = (1<<3),
}ADC_IRQ_t;

//-----------------------------
//User type definitions (structures)
//-----------------------------


//-----------------------------
//Configure structure for ADC
//-----------------------------

typedef struct{
	ADC_Mode_t		ADC_Mode;			//control the Conversion either Free Running or Single Conversion Mode
	// This parameter must be set based on @ref ADC_Mode_Define
	
	ADC_Prescaler_t		ADC_Prescale;		//select the Prescaler to be used by the ADC
	// This parameter must be set based on @ref ADC_Prescaler_Define
	
	Ref_Selection_t ADC_Reference;			//select Voltage Reference to be used by the ADC
	// This parameter must be set based on @ref ADC_Reference_Define

	ADC_TriggerSrc_t	ADC_TriggerSrc;		//select ADC Trigger Source
	// This parameter must be set based on @ref ADC_Trigger_Define
	
	ADC_IRQ_t		ADC_IRQ;				// Enable or Disable ADC Conversion Complete IRQ
	// This parameter must be set based on @ref ADC_IRQ_Define
	
	void (*P_ADC_IRQ_CallBack)(void);				//set the C Function which will be called once ADC Conversion Complete IRQ Happens
	
	
}ADC_Config_t;

/* ================================================================ */
/* ======================= Generic Varabiles ====================== */
/* ================================================================ */
ADC_Config_t G_ADC_Config;
/* ================================================================ */
/* =========== APIs Supported by "MCAL ADC DRIVER" ============= */
/* ================================================================ */
void MCAL_ADC_Init(ADC_Config_t* ADC_Config);
void MCAL_ADC_DeInit(void); 

uint16_t MCAL_ADC_Read(ADC_Channels_t Read_Channel);


#endif /* ADC_H_ */