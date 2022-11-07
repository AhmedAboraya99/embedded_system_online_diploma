/*
 * lcd.h
 *
 * Created: 9/5/2021 4:22:04 PM
 *  Author: Ahmed Aboraya
 */ 

#ifndef LCD_H_
#define LCD_H_
//-----------------------------
//Includes
//-----------------------------
#include "ATMEGA32.h"
#include "DIO_Driver.h"
#include <util/delay.h>



#define LCD_DIO				DIOA
#define LCD_PORT			PORTA
#define DataDir_LCD_PORT	DDRA

#define LCD_CTRL			DIOB
#define LCD_CTRL_PORT		PORTB
#define DataDir_LCD_CTRL	DDRB

#define EN_SWITCH			DIO_PIN3
#define RW_SWITCH			DIO_PIN2
#define RS_SWITCH			DIO_PIN1

#define DATA_shift  4 // in 8 bit mode 0 and in 4 bit mode 4

//LCD Mode Select
//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE

#define LCD_FUNCTION_8BIT_1LINE   					(0x30)
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)

#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_SHIFT   						(0x07)

#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_RETURN_HOME								(0x02)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)

#define GO_INTO_4BIT_MODE							(0x33)
#define START_4BIT_MODE								(0x32)
#define LCD_FUNCTION_4BIT_1LINE   					(0x20)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
DIO_PinConfig_t lcd_pinconfig;

void LCD_INIT();
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char character);
void LCD_WRITE_STRING(char* string);
void LCD_WRITE_NUM(uint8_t number);
void LCD_WRITE_DATA(unsigned int data);
void LCD_check_lcd_isbusy(void);
void LCD_lcd_kick(void);
void LCD_clear_screen();
void LCD_GOTO_XY(unsigned char line, unsigned char position);
void LCD_DIO_INIT();


#endif /* LCD_H_ */
