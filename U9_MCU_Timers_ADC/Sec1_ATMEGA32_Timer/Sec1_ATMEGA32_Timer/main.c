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

#include "Atmega32_TIMER0_CTC.h"
#include "Atmega32_TIMER0_PWM.h"




/* ================================================================ */
/* ======================= Main Function ========================== */
/* ================================================================ */

int main(void)
{

	//TIMER0_CTC_Test(20);
	TIMER0_PWM_Test(60);
}