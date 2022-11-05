/*
 * lcd.c
 *
 * Created: 4/22/2021 3:01:11 PM
 *  Author: Ahmed Aboraya
 */ 

#include "lcd.h"

void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_lcd_kick(){
	MCAL_GPIO_WritePIN(LCD_CTRL, EN_SWITCH,GPIO_PIN_SET);
	WAIT_ms(50);
	MCAL_GPIO_WritePIN(LCD_CTRL, EN_SWITCH,GPIO_PIN_RESET);
}

void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}
void LCD_GPIO_INIT(){

	/*MODE&CNF :make GPIOA (EN_SWITCH,RW_SWITCH,RS_SWITCH) pins
	 	 as floating input(reset state)
	 */
//	lcd_pinconfig.GPIO_PINNumber = EN_SWITCH;
//	lcd_pinconfig.GPIO_Mode = GPIO_Mode_IN_Float;
//	MCAL_GPIO_init(LCD_CTRL,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_CTRL, EN_SWITCH, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);


//	lcd_pinconfig.GPIO_PINNumber = RS_SWITCH;
//	lcd_pinconfig.GPIO_Mode = GPIO_Mode_IN_Float;
//	MCAL_GPIO_init (LCD_CTRL,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_CTRL, RS_SWITCH, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

//	lcd_pinconfig.GPIO_PINNumber = RW_SWITCH;
//	lcd_pinconfig.GPIO_Mode = GPIO_Mode_IN_Float;
//	MCAL_GPIO_init (LCD_CTRL,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_CTRL, RW_SWITCH, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

	MCAL_GPIO_WritePIN(LCD_CTRL ,RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePIN(LCD_CTRL ,RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePIN(LCD_CTRL ,EN_SWITCH, GPIO_PIN_RESET);


	/************************************************************/

	//MODE&CNF: init GPIOA PIN(0-7) as as push-pull outputs with 10MHZ speed
//	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN0;
//	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
//	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
//	MCAL_GPIO_init (LCD_PORT,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN0, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

//	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN1;
//	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
//	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
//	MCAL_GPIO_init (LCD_PORT,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN1, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

//	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN2;
//	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
//	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
//	MCAL_GPIO_init (LCD_PORT,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN2, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

//	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN3;
//	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
//	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
//	MCAL_GPIO_init (LCD_PORT,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN3, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);
//	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN4;
//	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
//	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
//	MCAL_GPIO_init (LCD_PORT,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN4, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);
//	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN5;
//	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
//	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
//	MCAL_GPIO_init (GPIOA,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN5, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);
//	lcd_pinconfig.GPIO_PINNumber = GPIO_PIN6;
//	lcd_pinconfig.GPIO_Mode = GPIO_Mode_OUT_PP;
//	lcd_pinconfig.GPIO_Speed = GPIO_Speed_10MHZ;
//	MCAL_GPIO_init (LCD_PORT,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN6, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);
//	lcd_pinconfig = { GPIO_PIN7, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ};
//  MCAL_GPIO_init (LCD_PORT,&lcd_pinconfig);
	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN7, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);


}

void LCD_INIT(){

	WAIT_ms(20);
	LCD_GPIO_INIT();
	WAIT_ms(15);
	LCD_clear_screen();
	#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	#ifdef FOUR_BIT_MODE
		//LCD_WRITE_COMMAND(0x02);		/* send for 4 bit initialization of LCD  */
		//LCD_WRITE_COMMAND(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
		//LCD_WRITE_COMMAND(0x0c);              /* Display on cursor off*/
		//LCD_WRITE_COMMAND(0x06);              /* Increment cursor (shift cursor to right)*/
		//LCD_WRITE_COMMAND(0x01);
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);	
}

void LCD_check_lcd_isbusy(){


	//MODE&CNF: make GPIOA PIN(0-7) as as floating input(reset state)
	//make sure that there is no output on LCD
	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN0, GPIO_Mode_IN_Float, GPIO_Speed_NONE);

	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN1, GPIO_Mode_IN_Float, GPIO_Speed_NONE);


	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN2, GPIO_Mode_IN_Float, GPIO_Speed_NONE);


	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN3, GPIO_Mode_IN_Float, GPIO_Speed_NONE);

	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN4, GPIO_Mode_IN_Float, GPIO_Speed_NONE);

	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN5, GPIO_Mode_IN_Float, GPIO_Speed_NONE);

	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN6, GPIO_Mode_IN_Float, GPIO_Speed_NONE);

	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN7, GPIO_Mode_IN_Float, GPIO_Speed_NONE);


	MCAL_GPIO_WritePIN(LCD_CTRL ,RW_SWITCH,GPIO_PIN_SET);
	MCAL_GPIO_WritePIN(LCD_CTRL ,RS_SWITCH,GPIO_PIN_RESET);
	LCD_lcd_kick();
	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN0, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN1, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);


	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN2, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);


	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN3, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN4, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN5, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN6, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

	MCAL_GPIO_SetPIN (LCD_PORT, GPIO_PIN7, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);

	MCAL_GPIO_WritePIN(LCD_CTRL ,RW_SWITCH,GPIO_PIN_RESET);
	
}


void LCD_WRITE_COMMAND(unsigned char command){
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
		MCAL_GPIO_WritePort(LCD_PORT ,command);
		MCAL_GPIO_WritePIN(LCD_CTRL ,RW_SWITCH,GPIO_PIN_RESET);
		MCAL_GPIO_WritePIN(LCD_CTRL ,RS_SWITCH,GPIO_PIN_RESET);
		WAIT_ms(1);
		LCD_lcd_kick();
	#endif
//	#ifdef FOUR_BIT_MODE
//		LCD_check_lcd_isbusy();
//		LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
//		LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
//		LCD_lcd_kick ();
//		LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
//		LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
//		LCD_lcd_kick();
//	#endif
}
void LCD_WRITE_CHAR(unsigned char character){
	LCD_check_lcd_isbusy();
	MCAL_GPIO_WritePort(LCD_PORT ,character);
	MCAL_GPIO_WritePIN(LCD_CTRL ,RW_SWITCH,GPIO_PIN_RESET);
	MCAL_GPIO_WritePIN(LCD_CTRL ,RS_SWITCH,GPIO_PIN_SET);
	WAIT_ms(1);
	LCD_lcd_kick();	
}


void LCD_WRITE_STRING(char* string){
	int count = 0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}
void LCD_WRITE_NUM(uint32_t number){
	
	int p, k=0;
	int num[20];
	
	while(number)
	{
		num[k]=(number%10)+'0';
		number /= 10;
		k++;
	}
	k--;
	for (p=k;p>=0;p--)
	{
		LCD_WRITE_CHAR(num[p]);
	}
	
		
}
