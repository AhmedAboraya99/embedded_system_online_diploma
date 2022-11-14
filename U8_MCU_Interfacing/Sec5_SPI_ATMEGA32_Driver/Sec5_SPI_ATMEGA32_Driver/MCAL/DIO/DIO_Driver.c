
//-----------------------------
//Includes
//-----------------------------

#include "DIO_Driver.h"

//assisted functions
void MCAL_PIN_Direction(DIO_TypeDef* DIOx ,uint8_t PIN_Number,uint8_t value ){
	
	if(value == OUTPUT_PIN)
		 Set_Pin(DIOx->DDRx , PIN_Number);
	else
		Reset_Pin(DIOx->DDRx, PIN_Number);
	
}

void MCAL_PORT_Direction(DIO_TypeDef* DIOx ,uint8_t value ){
	
	
	if(value == OUTPUT_PORT)
		Set_Port(DIOx->DDRx) ;
	else
		Reset_Port(DIOx->DDRx) ;
}

void WAIT_ms(uint8_t t){
	uint8_t i,j;
	for(i=0;i<t;i++){
		for(j=0;j<255;j++);
	}
}
//APIs

/**================================================================
* @Fn- MCAL_DIO_init
* @brief 		-Initializes the PORTx PINy according to the specified parameters of PinConfig
* @param [in] 	-PORTx : where x can be (A..E depending on device used) to select DIO peripheral
*  @param [in]	-PinConfig : Pointer to DIO_PinConfig_t which contains
 * 				 the configuration info for specified DIO
* @retval		-none
* Note			-STM32F103C6 MCU has DIO A,B,C,D,E ports
 * 				 but LQFP48 Package has A,B ,Part of C&D
*/

void  MCAL_DIO_init (DIO_TypeDef* DIOx ,DIO_PinConfig_t* PINConfig){

	// DIO PIN mode is output
	if ((PINConfig->DIO_Mode == DIO_Mode_OUT_High)||(PINConfig->DIO_Mode == DIO_Mode_OUT_Low))
	{
		
		MCAL_PIN_Direction(DIOx,PINConfig->DIO_PINNumber,OUTPUT_PIN);
		//Output High
		if (PINConfig->DIO_Mode == DIO_Mode_OUT_High)
		{
			Set_Pin(DIOx->PORTx, PINConfig->DIO_PINNumber);
		}
		//Output Low
		else
			Reset_Pin(DIOx->PORTx,PINConfig->DIO_PINNumber);
	}

	else {
		//DIO PIN Mode is input
		if ((PINConfig->DIO_Mode == DIO_Mode_IN_HI_Z) ||  (PINConfig->DIO_Mode == DIO_Mode_IN_PU))
			{
				MCAL_PIN_Direction(DIOx,PINConfig->DIO_PINNumber,INPUT_PIN);
			//Input HI-Z
			if (PINConfig->DIO_Mode == DIO_Mode_IN_HI_Z)
			{
				Reset_Pin(DIOx->PORTx,PINConfig->DIO_PINNumber);
			}
			//Input Pull-Up
			else{
				Set_Pin(DIOx->PORTx,PINConfig->DIO_PINNumber);
				Reset_Pin(SFIOR, DIO_PIN2);
			
			}
		}
	}
}

/**================================================================
* @Fn-			 MCAL_DIO_SetPin
* @brief 		-Initializes the PORTx PINy according to the specified parameters of PinConfig
* @param [in] 	-PORTx : where x can be (A..E depending on device used) to select DIO peripheral
*  @param [in]	-Pin_Number : pin number to be set or configured
*  @param [in]	-Pin_Number : pin mode to be set or configured (input-> pull-Down/HI-Z or output-> Low/High)
* @retval -		-none
* Note			-STM32F103C6 MCU has DIO A,B,C,D,E ports
 * 				 but LQFP48 Package has A,B ,Part of C&D
*/
void  MCAL_DIO_SetPin (DIO_TypeDef* DIOx ,uint8_t Pin_Number, uint8_t Pin_Mode ){


	// DIO PIN mode is output
	if ((Pin_Mode == DIO_Mode_OUT_High)||(Pin_Mode == DIO_Mode_OUT_Low))
	{
		
		MCAL_PIN_Direction(DIOx, Pin_Number, OUTPUT_PIN);
		//Output High
		if (Pin_Mode == DIO_Mode_OUT_High)
		{
			Set_Pin(DIOx->PORTx ,Pin_Number);
		}
		//Output Low
		else
			Reset_Pin(DIOx->PORTx, Pin_Number);
			
	}

	else {
		//DIO PIN Mode is input
		if ((Pin_Mode == DIO_Mode_IN_HI_Z) ||  (Pin_Mode == DIO_Mode_IN_PU))
			{
				MCAL_PIN_Direction(DIOx,Pin_Number,INPUT_PIN);
			//Input HI-Z
			if (Pin_Mode == DIO_Mode_IN_HI_Z)
				Reset_Pin(DIOx->PORTx ,Pin_Number);
				
				
			//Input Pull-UP
			else{
				
				Set_Pin(DIOx->PORTx, Pin_Number);
				Reset_Pin(SFIOR, DIO_PIN2);
			}
		}
	}
}


/**================================================================
 * @Fn			-MCAL_DIO_Deinit
 * @brief 		-Reset all the DIO registers
 * @param [in] 	-PORTx : where x can be (A..E depending on device used) to select DIO peripheral
 * @retval	 	-none
 * Note			-none
 */

void MCAL_DIO_Deinit (uint8_t PORTx ){

MCUCSR |=  EXT_RESET;
}

/**================================================================
 * @Fn			-MCAL_DIO_ReadPin
 * @brief 		-Read specific PORTx Pin value
 * @param [in] 	-PORTx : where x can be (A..E depending on device used) to select DIO peripheral
 * @param [in] 	-PinNumber : set pin number to read
 * @retval	 	-The Reading value of the input pin
 * Note			-none
 */
uint8_t MCAL_DIO_ReadPIN (DIO_TypeDef* DIOx ,uint8_t PIN_Number)
{
	uint8_t BitStatus;
	if (( DIOx->PINx & PIN_Number) != (uint8_t)DIO_PIN_RESET)
	{
		BitStatus = DIO_PIN_SET ;
	}else
	{
		BitStatus = DIO_PIN_RESET ;
	}

	return BitStatus ;
}


/**================================================================
 * @Fn			-MCAL_DIO_ReadPort
 * @brief		-Read DIO Value
 * @param [in] 	-PORTx : where x can be (A..E depending on device used) to select the DIO Peripheral
 * @retval 		-The input DIO value (two values based on @ref DIO_PIN_State)
 * Note 		-None
 */

uint8_t MCAL_DIO_ReadPort (DIO_TypeDef* DIOx ){

	uint16_t PortVal;
		PortVal = (uint16_t) DIOx -> PINx;
		return PortVal ;
}

/**================================================================
 * @Fn			-MCAL_DIO_WritePin
 * @brief		-Write value on specific PIN
 * @param [in] 	-PORTx : where x can be (A..E depending on device used) to select the DIO Peripheral
 * @param [in]	-PinNumber : Specific Pin number to be Write on according to @ref DIO_PINS_Define
 * @param [in]	-Value : PIN value
 * @retval 		-None
 * Note 		-None
 */
void MCAL_DIO_WritePIN (DIO_TypeDef* DIOx ,uint8_t PIN_Number,uint8_t value ){

	if (value == DIO_PIN_SET )
		{
		//Port bit set/reset register (PORTx_BRR)
		//BRy: Port x Reset bit y (y= 0 ... 15)
		//0: No action on the corresponding ODRx bit
		//1: Reset the corresponding ODRx bit
		Set_Pin( DIOx->PORTx , PIN_Number) ;
		}
	else
		// Port bit set/reset register (PORTx_BSRR)
		// BSy: Port x Reset bit y (y= 0 ... 15)
		// 0: No action on the corresponding ODRx bit
		// 1: Set the corresponding ODRx bit
		Reset_Pin(DIOx->PORTx, PIN_Number) ;
		
}

/**================================================================
 * @Fn			-MCAL_DIO_WritePort
 * @brief		-Write value on DIO
 * @param [in] 	-PORTx : where x can be (A..E depending on device used) to select the DIO Peripheral
 * @param [in]	-Value : DIO value
 * @retval 		-None
 * Note 		-None
 */

void MCAL_DIO_WritePort (DIO_TypeDef* DIOx, uint8_t value ){

	DIOx->PORTx = (uint8_t) value;
}

/**================================================================
 * @Fn			-MCAL_DIO_TogglePin
 * @brief		-Toggle a specific PIN
 * @param [in] 	-PORTx : where x can be (A..E depending on device used) to select the DIO Peripheral
 * @param [in]	-PinNumber : Specific Pin number to be Toggled according to @ref DIO_PINS_Define
 * @retval 		-None
 * Note 		-None
 */

void MCAL_DIO_TogglePIN (DIO_TypeDef* DIOx, uint8_t PIN_Number){

	DIOx->PORTx ^= PIN_Number;
}

/**================================================================
 * @Fn			-MCAL_DIO_LockPin
 * @brief		-Locking allows the IO configuration to be frozen
 * @param [in] 	-PORTx : where x can be (A..E depending on device used) to select the DIO Peripheral
 * @param [in]	-PinNumber : Specific Pin number to be Locked according to @ref DIO_PINS_Define
 * @retval 		-Ok if lock is successful , Error if not (according to @ref DIO_LOCK_State
 * Note 		-None
 */
