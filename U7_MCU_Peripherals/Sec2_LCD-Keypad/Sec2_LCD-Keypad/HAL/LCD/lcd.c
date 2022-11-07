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
	//LCD_CTRL |= (1 << EN_SWITCH);
	//_delay_ms(50);
	//LCD_CTRL &= ~(1 << EN_SWITCH);	
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

void LCD_PORT_INIT(){
		
	/*MODE&CNF : make DIOA (EN_SWITCH,RW_SWITCH,RS_SWITCH) pins
	 	 as Output Pins
	 */
	
	/************************************************************/


	//DataDir_LCD_CTRL |=( (1<<EN_SWITCH) | (1<<RS_SWITCH) |(1<<RW_SWITCH));
	//Reset control Pins
	MCAL_DIO_SetPin(LCD_CTRL, EN_SWITCH, DIO_Mode_OUT_Low );
	MCAL_DIO_SetPin(LCD_CTRL, RS_SWITCH, DIO_Mode_OUT_Low );
	MCAL_DIO_SetPin(LCD_CTRL, RW_SWITCH, DIO_Mode_OUT_Low );

	//MCAL_DIO_WritePIN(LCD_CTRL , EN_SWITCH, DIO_PIN_RESET);
	//MCAL_DIO_WritePIN(LCD_CTRL , RS_SWITCH, DIO_PIN_RESET);
	//MCAL_DIO_WritePIN(LCD_CTRL , RW_SWITCH, DIO_PIN_RESET);
	
	
	//MODE&CNF: init DIOA PIN(0-7)  as outputs
	MCAL_PIN_Direction (LCD_PORT, DIO_PIN0, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_PORT, DIO_PIN1, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_PORT, DIO_PIN2, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_PORT, DIO_PIN3, OUTPUT_PIN);
		
	MCAL_PIN_Direction (LCD_PORT, DIO_PIN4, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_PORT, DIO_PIN5, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_PORT, DIO_PIN6, OUTPUT_PIN);

	MCAL_PIN_Direction (LCD_PORT, DIO_PIN7, OUTPUT_PIN);	
	
}

void LCD_INIT(){

	_delay_ms(20);
	LCD_PORT_INIT();
	_delay_ms(15);
	LCD_clear_screen();
	#ifdef EIGHT_BIT_MODE
		LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	#ifdef FOUR_BIT_MODE
		//LCD_WRITE_COMMAND(GO_INTO_4BIT_MODE);
		//LCD_WRITE_COMMAND(START_4BIT_MODE);
		LCD_WRITE_COMMAND(LCD_RETURN_HOME);		/* send for 4-bit initialization of LCD  */
		LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);              /* 2 line, 5*7 matrix in 4-bit mode */
		LCD_WRITE_COMMAND(LCD_DISP_OFF);
		LCD_clear_screen();
	#endif

	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
	
	
}

void LCD_check_lcd_isbusy(){

	//DataDir_LCD_PORT &= ~(0xFF<<DATA_shift);
	//LCD_CTRL |= (1 << RW_SWITCH);
	//LCD_CTRL &= ~(1 << RS_SWITCH);
	//LCD_lcd_kick();
	//DataDir_LCD_PORT |= (0xFF<<DATA_shift);
	//LCD_CTRL &= ~(1 << RW_SWITCH);
	
	//MODE&CNF: make DIOA PIN(0-7) as as HI-Z input
	//make sure that there is no output on LCD
	Reset_Pin(DataDir_LCD_PORT, 0xFF) ;

	MCAL_DIO_WritePIN(LCD_CTRL ,RW_SWITCH,DIO_PIN_SET);
	MCAL_DIO_WritePIN(LCD_CTRL ,RS_SWITCH,DIO_PIN_RESET);
	
	LCD_lcd_kick();
	//make data lines as output
	Set_Pin(DataDir_LCD_PORT, 0xFF) ;
	MCAL_DIO_WritePIN(LCD_CTRL ,RW_SWITCH, DIO_PIN_RESET);

}


void LCD_WRITE_COMMAND(unsigned char command){
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
		
		MCAL_DIO_WritePort(LCD_PORT ,command);
		MCAL_DIO_WritePIN(LCD_CTRL ,RW_SWITCH,DIO_PIN_RESET);
		MCAL_DIO_WritePIN(LCD_CTRL ,RS_SWITCH,DIO_PIN_RESET);
		_delay_ms(1);
		LCD_lcd_kick();
	#endif
	#ifdef FOUR_BIT_MODE
		_delay_ms(10);
		//LCD_check_lcd_isbusy();
		
		//LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
		MCAL_DIO_WritePIN(LCD_CTRL, RW_SWITCH, DIO_PIN_RESET);
		MCAL_DIO_WritePIN(LCD_CTRL, RS_SWITCH, DIO_PIN_RESET);
		
		 /* take 1st 4 bits of command */
		LCD_PORT = ((LCD_PORT & 0x0F) | (command & 0xF0));
		//MCAL_DIO_WritePort(LCD_PORT,(LCD_PORT & 0x0F) | (command & 0xF0));
		
		LCD_lcd_kick ();
		
		//LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
		MCAL_DIO_WritePIN(LCD_CTRL, RW_SWITCH, DIO_PIN_RESET);
		MCAL_DIO_WritePIN(LCD_CTRL, RS_SWITCH, DIO_PIN_RESET);
		
		/*send 2nd 4 bits of command */
		LCD_PORT= (LCD_PORT & 0x0F) | (command<<4);
		//MCAL_DIO_WritePort(LCD_PORT,(LCD_PORT & 0x0F) |(command<<4));
		
		LCD_lcd_kick();
	#endif
}
void LCD_WRITE_CHAR(unsigned char character){
	#ifdef EIGHT_BIT_MODE
		LCD_check_lcd_isbusy();
		//write mode
		MCAL_DIO_WritePort(LCD_PORT ,character);
		MCAL_DIO_WritePIN(LCD_CTRL ,RW_SWITCH,DIO_PIN_RESET);
		MCAL_DIO_WritePIN(LCD_CTRL ,RS_SWITCH,DIO_PIN_SET);
		_delay_ms(1);
		LCD_lcd_kick();	
	#endif
	#ifdef FOUR_BIT_MODE
		
		//LCD_check_lcd_isbusy();
		_delay_ms(10);
		LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
		//MCAL_DIO_WritePort(LCD_PORT,(LCD_PORT & 0x0F) | (character & 0xF0));
		
		MCAL_DIO_WritePIN(LCD_CTRL, RS_SWITCH, DIO_PIN_SET);
		MCAL_DIO_WritePIN(LCD_CTRL, RW_SWITCH, DIO_PIN_RESET);
		
		LCD_lcd_kick();
		MCAL_DIO_WritePIN(LCD_CTRL, RS_SWITCH, DIO_PIN_SET);
		MCAL_DIO_WritePIN(LCD_CTRL, RW_SWITCH, DIO_PIN_RESET);
		
		LCD_PORT = (LCD_PORT & 0x0F) | (character<<4);
		//MCAL_DIO_WritePort(LCD_PORT,(LCD_PORT & 0x0F) | (character<<4));
			
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
