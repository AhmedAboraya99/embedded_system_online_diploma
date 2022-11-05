/*
 * 7_segment.c
 *
 * Created: 4/17/2022 5:52:21 PM
 *  Author: Ahmed Aboraya
 */

#include "7_segment.h"

//-----------------------------
//Functions
//-----------------------------
void INIT_7_Segment(){

/************************************************************/

	//MODE&CNF: init GPIOB PIN(9-15) as as push-pull outputs with 10MHZ speed

	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN9;
	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
	MCAL_GPIO_init (Segments_PORT,&lcd_pinconfig);

	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN10;
	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
	MCAL_GPIO_init (Segments_PORT,&lcd_pinconfig);

	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN11;
	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
	MCAL_GPIO_init (Segments_PORT,&lcd_pinconfig);

	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN12;
	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
	MCAL_GPIO_init (Segments_PORT,&lcd_pinconfig);


	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN13;
	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
	MCAL_GPIO_init (Segments_PORT,&lcd_pinconfig);

	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN14;
	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
	MCAL_GPIO_init (Segments_PORT,&lcd_pinconfig);

	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN15;
	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
	MCAL_GPIO_init (Segments_PORT,&lcd_pinconfig);
}
