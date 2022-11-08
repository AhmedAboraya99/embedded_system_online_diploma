/*
 * lcd.c
 *
 * Created: 9/5/2021 4:22:17 PM
 *  Author: Ahmed Aboraya
 */ 

#include "lcd.h"


void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_lcd_kick(){
	
	MCAL_DIO_WritePIN(LCD_CTRL, EN_SWITCH, DIO_PIN_SET);
	_delay_ms(50);
	MCAL_DIO_WritePIN(LCD_CTRL, EN_SWITCH, DIO_PIN_RESET);

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

void LCD_DIO_INIT(){
		
	/*MODE&CNF : make DIOA (EN_SWITCH,RW_SWITCH,RS_SWITCH) pins
	 	 as Output Pins
	 */
	/************************************************************/

//make control Pins output & reset them
	MCAL_DIO_SetPin(LCD_CTRL, EN_SWITCH, DIO_Mode_OUT_Low );
	MCAL_DIO_SetPin(LCD_CTRL, RS_SWITCH, DIO_Mode_OUT_Low );
	MCAL_DIO_SetPin(LCD_CTRL, RW_SWITCH, DIO_Mode_OUT_Low );

	//MODE&CNF: init DIOA PIN(0-7)  as outputs
	#ifdef EIGHT_BIT_MODE
	MCAL_PIN_Direction (LCD_DIO, DIO_PIN0, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_DIO, DIO_PIN1, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_DIO, DIO_PIN2, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_DIO, DIO_PIN3, OUTPUT_PIN);
	#endif
	MCAL_PIN_Direction (LCD_DIO, DIO_PIN4, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_DIO, DIO_PIN5, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_DIO, DIO_PIN6, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_DIO, DIO_PIN7, OUTPUT_PIN);	
	
}

void LCD_INIT(){

	_delay_ms(20);
	LCD_DIO_INIT();
	_delay_ms(15);
	LCD_clear_screen();
	#ifdef EIGHT_BIT_MODE
		LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	#ifdef FOUR_BIT_MODE
		LCD_WRITE_COMMAND(LCD_RETURN_HOME);		/* send for 4-bit initialization of LCD  */
		LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);              /* 2 line, 5*7 matrix in 4-bit mode */
	#endif

	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
	
}

void LCD_check_lcd_isbusy(){

	//DataDir_LCD_DIO &= ~(0xFF<<DATA_shift);
	//LCD_CTRL |= (1 << RW_SWITCH);
	//LCD_CTRL &= ~(1 << RS_SWITCH);
	//LCD_lcd_kick();
	//DataDir_LCD_DIO |= (0xFF<<DATA_shift);
	//LCD_CTRL &= ~(1 << RW_SWITCH);
	
	//make sure that there is no output on LCD
	#ifdef EIGHT_BIT_MODE
	Reset_Pin(DataDir_LCD_PORT, 0xFF) ;
	#endif 
	
	#ifdef FOUR_BIT_MODE
	Reset_Pin(DataDir_LCD_PORT, 0xFF<<DATA_shift) ;
	#endif
	
	MCAL_DIO_WritePIN(LCD_CTRL ,RW_SWITCH,DIO_PIN_SET);
	MCAL_DIO_WritePIN(LCD_CTRL ,RS_SWITCH,DIO_PIN_RESET);
	
	LCD_lcd_kick();
	//make data lines as output
	#ifdef EIGHT_BIT_MODE
	Set_Pin(DataDir_LCD_PORT, 0xFF) ;
	#endif
	
	#ifdef FOUR_BIT_MODE
	Set_Pin(DataDir_LCD_PORT, 0xFF<<DATA_shift) ;
	#endif
	MCAL_DIO_WritePIN(LCD_CTRL ,RW_SWITCH, DIO_PIN_RESET);

}


void LCD_WRITE_COMMAND(unsigned char command){
	LCD_check_lcd_isbusy();
	#ifdef EIGHT_BIT_MODE
		
		
		MCAL_DIO_WritePort(LCD_DIO, command);
		MCAL_DIO_WritePIN(LCD_CTRL, RW_SWITCH, DIO_PIN_RESET);
		MCAL_DIO_WritePIN(LCD_CTRL, RS_SWITCH, DIO_PIN_RESET);

		LCD_lcd_kick();

	#endif
	#ifdef FOUR_BIT_MODE
		
		LCD_check_lcd_isbusy();

		/* take 1st 4 bits of command */
		//LCD_PORT = ((LCD_PORT & 0x0F) | (command & 0xF0));
		MCAL_DIO_WritePort(LCD_DIO,(LCD_PORT & 0x0F) | (command & 0xF0));
		
		//turn RW&RS OFF for instruction write mode.
		MCAL_DIO_WritePIN(LCD_CTRL, RS_SWITCH, DIO_PIN_RESET);
		MCAL_DIO_WritePIN(LCD_CTRL, RW_SWITCH, DIO_PIN_RESET);
		
		LCD_lcd_kick();
		
		/*send 2nd 4 bits of command */
		//LCD_PORT= (LCD_PORT & 0x0F) | (command<<4);
		MCAL_DIO_WritePort(LCD_DIO,(LCD_PORT & 0x0F) |(command<<DATA_shift));
		
		//turn RW&RS OFF for instruction write mode.
		MCAL_DIO_WritePIN(LCD_CTRL, RS_SWITCH, DIO_PIN_RESET);
		MCAL_DIO_WritePIN(LCD_CTRL, RW_SWITCH, DIO_PIN_RESET);

		LCD_lcd_kick();
		
	#endif
}
void LCD_WRITE_CHAR(unsigned char character){
	
	
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
		//write mode
		MCAL_DIO_WritePort(LCD_DIO ,character);
		MCAL_DIO_WritePIN(LCD_CTRL ,RW_SWITCH,DIO_PIN_RESET);
		MCAL_DIO_WritePIN(LCD_CTRL ,RS_SWITCH,DIO_PIN_SET);
		_delay_ms(1);
		LCD_lcd_kick();	
	#endif
	#ifdef FOUR_BIT_MODE
		//turn RS ON & RW OFF for Data write mode.
		MCAL_DIO_WritePIN(LCD_CTRL, RS_SWITCH, DIO_PIN_SET);
		MCAL_DIO_WritePIN(LCD_CTRL, RW_SWITCH, DIO_PIN_RESET);

		
		//LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
		MCAL_DIO_WritePort(LCD_DIO,(LCD_PORT & 0x0F) | (character & 0xF0));
		
		LCD_lcd_kick();

		//LCD_PORT = (LCD_PORT & 0x0F) | (character<<4);
		MCAL_DIO_WritePort(LCD_DIO,(LCD_PORT & 0x0F) | (character<<DATA_shift));
		//turn RS ON & RW OFF for Data write mode.
		MCAL_DIO_WritePIN(LCD_CTRL, RS_SWITCH, DIO_PIN_SET);
		MCAL_DIO_WritePIN(LCD_CTRL, RW_SWITCH, DIO_PIN_RESET);

		LCD_lcd_kick();
	#endif
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
void LCD_WRITE_NUM(uint8_t number){
	
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
