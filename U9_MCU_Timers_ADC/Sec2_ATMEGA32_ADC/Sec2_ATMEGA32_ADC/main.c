/*
 * main.c
 *
 * Created: 12/27/2021 7:16:01 AM
 *  Author: Ahmed Aboraya
 */ 

#define F_CPU 8000000UL
//-----------------------------
//Includes : Header Files
//-----------------------------

#include "ADC.h"
#include "lcd.h"

/* ================================================================ */
/* ======================= Global Macros ====================== */
/* ================================================================ */
#define LM35_REFVOLT				5000UL

/* ================================================================ */
/* ======================= Global Functions ====================== */
/* ================================================================ */
uint8_t ADC_GetTemprature(uint16_t ADCVal)
{
	uint8_t TempVal = 0 ;
	TempVal = ADCVal/(LM35_REFVOLT/1024);
	return TempVal;
}



/* ================================================================ */
/* ======================= Main Function ========================== */
/* ================================================================ */

int main(void)
{

	uint16_t ADC_ReadVal;
	uint8_t	TempSensorVal;
	char TempString[10];
	ADC_Config_t ADC_Cfg = {ADC_FREE_RUNNING_MODE, ADC_PRESCALER_64, ADC_INTERNAL_256V, ADC_FREE_TRIGGERING, ADC_IRQ_ENABLE};
	MCAL_ADC_Init(&ADC_Cfg);
	
	LCD_INIT();			/* Initialization of LCD */
	LCD_GOTO_XY(1,0);	/* LCD16x2 cursor position */
	
	LCD_WRITE_STRING("Temperature =");	/* Write string on 1st line of LCD */

	while(1){
			
			
			ADC_ReadVal=MCAL_ADC_Read(ADC_CHANNEL3);	/* Read ADC channel 7 */
			TempSensorVal = ADC_GetTemprature(ADC_ReadVal);
			itoa(TempSensorVal,TempString,10);	/* Integer to string conversion */
			LCD_GOTO_XY(2,0);	/* LCD16x2 cursor position */
			LCD_WRITE_STRING(TempString);
			
			LCD_WRITE_STRING(" C");
	}

}