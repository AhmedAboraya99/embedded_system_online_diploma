/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdint.h>
#include "STM32f103X6.h"
#include "STM32f103X6_GPIO_Driver.h"
#include "SPI\STM32F103CX_SPI_Driver.c"
#include "UART\STM32F103x8_UART_Driver.c"

/* ================================= Global Variables and DataTypes ================================= */

typedef volatile unsigned int vuint32_t;
uint16_t  ch;
USART_Config_t uartCFG ;
SPI_Config_t SPI_CFG;

/*
 * =====================================
 * 		Global Functions
 * =====================================
 */
void WAIT_ms(uint32_t t){
	uint32_t i,j;
	for(i=0;i<t;i++){
		for(j=0;j<255;j++);
	}
}


void clock_init(void)
{
	//enable clock for GPIOA
	RCC_GPIOA_CLOCK_EN();
	//enable clock for GPIOB
	RCC_GPIOB_CLOCK_EN();
	//enable clock for Alternative IO
	RCC_AFIO_CLOCK_EN();

}

/*
 * =====================================
 * 		CallBack Functions
 * =====================================
 */

void USART_IRQ_CallBack (void)
{

	MCAL_USART_ReceiveData(USART1, &ch, Polling_Disable);
	MCAL_USART_SendData(USART1, &ch, Polling_Enable);

	//send Data to SPI Ports
	MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN4,GPIO_PIN_RESET);		//NSS LOW
	MCAL_SPI_TX_RX(SPI1, &ch, Polling_Enable);
	MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN4,GPIO_PIN_SET);		//NSS HIGH

}

/*
 * =====================================
 * 		Configuration Functions
 * =====================================
 */

void UART_Config_Init(){


	uartCFG.USART_Mode = USART_MODE_TX_RX;

	uartCFG.BaudRate = USART_BaudRate_115200;

	uartCFG.Payload_Length = USART_Payload_Length_8B ;

	uartCFG.Parity = USART_NONE_Parity;

	uartCFG.StopBits = USART_1_StopBit;

	uartCFG.HWFlowCTRL = USART_HWFlowCTRL_NONE;

	uartCFG.IRQ_Enable = USART_IRQ_Enable_RXNE;

	uartCFG.P_IRQ_CallBack = USART_IRQ_CallBack;

	MCAL_USART_init(USART1, &uartCFG);
	MCAL_USART_GPIO_SetPins(USART1);

}

void SPI_Config_Init(){

	SPI_CFG.SPI_Mode = SPI_Mode_MASTER;

	SPI_CFG.Frame_Format = Frame_Format_MSB_FIRST;

	SPI_CFG.Frame_Size = Frame_Size_8BIT ;

	SPI_CFG.Communication_Mode = Data_Mode_UNIDI_Full_Duplex;

	SPI_CFG.Clock_Polarity = Clock_Polarity_Idle_HIGH;

	SPI_CFG.Clock_Phase = Clock_Phase_Second_Capture;

	SPI_CFG.NSS_Management = NSS_Management_SW_SSI_SET;

	SPI_CFG.BaudRate_Prescalar = BaudRate_Prescalar_PLCK_Divide_BY_8;

	SPI_CFG.IRQ_Enable = SPI_IRQ_ENABLE_NONE;

	SPI_CFG.P_IRQ_CallBack = NULL ;


	MCAL_SPI_Init(SPI1, &SPI_CFG);
	MCAL_SPI_GPIO_Set_Pins(SPI1);
	//Configure GPIOA Pin 4 with NSS of SPI1
	MCAL_GPIO_SetPIN(GPIOA, GPIO_PIN4, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ);
	MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN4, GPIO_PIN_SET);		//NSS HIGH

}



int main(void)
{
	clock_init();

	UART_Config_Init();


	SPI_Config_Init();








    /* Loop forever */
	for(;;);
}