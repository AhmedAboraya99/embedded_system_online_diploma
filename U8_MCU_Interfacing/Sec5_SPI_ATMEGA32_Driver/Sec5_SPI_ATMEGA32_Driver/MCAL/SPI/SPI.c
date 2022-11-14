/*
 * SPI.c
 *
 * Created: 8/17/2022 5:26:45 PM
 *  Author: Ahmed Aboraya
 */ 
//-----------------------------
//Includes
//-----------------------------

#include "DIO_Driver.h"

#include "SPI.h"




/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/



/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

/**================================================================
* @Fn- MCAL_SPI_init
* @brief 		-Initializes the SPIx according to the specified parameters of SPI_Config
* @param [in] 	-SPIx : where x can be (A..E depending on device used) to select SPI peripheral
*  @param [in]	-SPI_Config : Pointer to SPI_Config_t which contains
*  							  the configuration information for the specified SPI Module
 * 				 None
* Note			-STM32F103C6 MCU has SPI MASTER/Slave modes  & NSS Hardware/Software
 *
*/
void  MCAL_SPI_Init(SPI_TypeDef * SPIx, SPI_Config_t * SPI_Config){
	uint8_t Temp_SPCR = 0;
	
	//enable SPI Module
	//When this bit is cleared the SPI prescalers and outputs are stopped
	//Set_Bitfield(SPIx->SPCR.bits.SPE);
	Set_Bit(Temp_SPCR,6);

	//Set_Bitfield(SPIx->SPCR.bits.MSTR);
	//select SPI Frame Format(LSB First/MSB First)
	Set_Pin (Temp_SPCR, SPI_Config->Frame_Format);

	//Select SPI Communication Mode
	//Set_Pin (SPIx -> SPCR.reg, SPI_Config->Communication_Mode);
	//Select Clock Polarity
	Set_Pin (Temp_SPCR, SPI_Config->Clock_Polarity);
	//Select Clock Phase
	Set_Pin (Temp_SPCR, SPI_Config->Clock_Phase);

	//configure SPI communication clock baud rate(for MASTER)
	if (SPI_Config-> Clock_Speed == Clock_Speed_Double){
		
		Set_Pin (Temp_SPCR, SPI_Config->BaudRate_Prescalar);
		//enable clock speed double
		Set_Pin(SPIx-> SPSR.reg, Clock_Speed_Double);
	}else {
		
		Set_Pin (Temp_SPCR, SPI_Config->BaudRate_Prescalar);
		//disable clock speed double
		Set_Pin (SPIx-> SPSR.reg, Clock_Speed_Normal) ;
	}
	////Select SPI Mode (MASTER/Slave)
	//Bit 4 MSTR:> 1: MASTER , 0: Slave
	Set_Pin (Temp_SPCR, SPI_Config->SPI_Mode);
	//enable SPI IRQ
	if(SPI_Config-> IRQ_Enable != SPI_IRQ_ENABLE_NONE)
	{
		//open global interrupt
		Global_Interrupt_Enable();
		//enable interrupt
		Set_Pin (Temp_SPCR, SPI_Config-> IRQ_Enable);

	}else
	 {
		//disable interrupt
		Set_Pin (Temp_SPCR, SPI_Config-> IRQ_Enable);
	 }
	SPIx->SPCR.reg = Temp_SPCR;
	Global_SPI_Config = SPI_Config; 
}


/**================================================================
 * @Fn			-MCAL_SPI_Deinit
 * @brief 		-Reset all the SPI registers
 * @param [in] 	-SPIx : where x can be (1..3 depending on device used) to select SPI peripheral
 * @retval	 	-none
 * Note			- Reset The module by RCC & Disable NVIC
 */

void MCAL_SPI_DeInit(SPI_TypeDef * SPIx) {


	//reset SPI & disable SPI clock
	//disable SPI Module

	Reset_Port(SPIx -> SPCR.reg);
	//disable Clock speed double
	Set_Bitfield(SPIx->SPSR.bits.SPI2X) ;


}
/**================================================================
 * @Fn 				-	MCAL_SPI_Send_Data
 * @brief 			-	Send TX Buffer With SPI
 */
void  MCAL_SPI_Send_Data(SPI_TypeDef * SPIx, char* pTxBuffer, enum SPI_Polling_Mechanism Polling_EN)
{
	
	// Send Data to SPI Data register
	SPIx-> SPDR = (*pTxBuffer);

	//Bit 7 SPIF:?SPI Interrupt Flag

	if (Polling_EN == SPI_Polling_Enable)
		/* Wait for transmission complete */
		while(!(SPIx->SPSR.bits.SPIF));


}

/**================================================================
 * @Fn 				-	MCAL_SPI_Recieve_Data
 * @brief 			-	Receive data from SPI RX Buffer
 */

void  MCAL_SPI_Recieve_Data(SPI_TypeDef * SPIx, char* pTxBuffer, enum SPI_Polling_Mechanism Polling_EN){

	//Bit 7 SPIF:?SPI Interrupt Flag

	if (Polling_EN == SPI_Polling_Enable)
		//Wait for reception complete
		while(!(SPIx->SPSR.bits.SPIF));

	//receive data
	(*pTxBuffer) = SPIx-> SPDR ;
	
}

/**================================================================
 * @Fn 				-	MCAL_SPI_TX_RX
 * @brief 			-	Transmit and Receive Data
 */
void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx, char* pTxBuffer, enum SPI_Polling_Mechanism Polling_EN)
{
	// Send Data to SPI Data register
	SPIx-> SPDR = (pTxBuffer);

	//Bit 7 SPIF:?SPI Interrupt Flag

	if (Polling_EN == SPI_Polling_Enable)
		//wait until SPIF flag is set
		while(!(SPIx->SPSR.bits.SPIF));


	//receive data
	(*pTxBuffer) = SPIx-> SPDR ;


}

void MCAL_SPI_DIO_Set_Pins(SPI_TypeDef *SPIx){

	
	//=========MASTER========//
	if(Global_SPI_Config->SPI_Mode == SPI_Mode_MASTER){

		//	SPIx_SCK -> PB5
		MCAL_DIO_SetPin (SPI_DIO, DIO_PIN5, DIO_Mode_OUT_Low );

		//	SPIx_MISO -> PB6
		MCAL_DIO_SetPin (SPI_DIO, DIO_PIN6, DIO_Mode_IN_HI_Z );

		//SPIx_MOSI -> PB7
		MCAL_DIO_SetPin (SPI_DIO, DIO_PIN7, DIO_Mode_OUT_Low );
			
		//SPIx_SS -> PB4
		MCAL_DIO_SetPin (SPI_DIO, DIO_PIN4, DIO_Mode_OUT_Low );
		
		}
	//=========SLAVE========//
	else if(Global_SPI_Config ->SPI_Mode == SPI_Mode_SLAVE){
		//	SPIx_SCK -> PB5
		MCAL_DIO_SetPin (SPI_DIO, DIO_PIN5, DIO_Mode_IN_HI_Z );

		//	SPIx_MISO -> PB6
		MCAL_DIO_SetPin (SPI_DIO, DIO_PIN6, DIO_Mode_OUT_Low );

		//SPIx_MOSI -> PB7
		MCAL_DIO_SetPin (SPI_DIO, DIO_PIN7, DIO_Mode_IN_HI_Z );
		
		//SPIx_SS -> PB4
		MCAL_DIO_SetPin (SPI_DIO, DIO_PIN4, DIO_Mode_IN_HI_Z );

	}


}
void __vector_12 (void) __attribute__((signal));
void __vector_12 (void){
		Global_SPI_Config -> P_IRQ_CallBack();

}

//ISR
//ISR(SPI_STC_vect)
//{
//
	//Global_SPI_Config -> P_IRQ_CallBack();
//}




