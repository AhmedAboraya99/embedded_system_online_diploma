//-----------------------------
//Includes
//-----------------------------

#include "STM32F103_I2C_Driver.h"

/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/

I2C_Config_t Global_I2C_Config[2] = {0} ;


//-----------------------------
//User type definitions (structures)
//-----------------------------

//*********Global Functions*********//
uint8_t Get_I2C_Index(I2C_TypeDef* I2Cx){

	uint8_t I2C_Index = I2Cx == I2C1?  I2C1_INDEX : I2C2_INDEX ;
	return I2C_Index;

}
/*
 * ===============================================================
 *
 *                      Generic Functions "APIs"
 *
 * ===============================================================
 */

/**================================================================
* @Fn				-I2C_Generate_Start
* @brief		  	-generate start condition to start transmitter .
* @param [in] 		- I2Cx : where x can be (1 or 2 ) to select I2C peripheral
* @param [in] 		- Start:  send start or Repeated start
* @param [in] 		- State: Enable or disable Start generation
* @retval 			- none
* Note				- none
*/
void I2C_Generate_Start(I2C_TypeDef *I2Cx,I2C_Start_t Start, Functional_State_t State)
{
	/* Check the type of start (Start or Repeated Start) */
	if(Start != Repeated_Start)
	{
		/* Check if the bus is idle */
		while(I2C_BUSY(I2Cx));
	}

	/* Write start condition */
	/*
	 *	Bit 8 START: Start generation
		This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
		In Master Mode:
		0: No Start generation
		1: Repeated start generation
		In Slave mode:
		0: No Start generation
		1: Start generation when the bus is free
	 */
	if(State != DISABLE)
	{
		/* Generate a START condition */
		Set_Bitfield(I2Cx->I2C_CR1.bits.START);
	}
	else
	{
		/* Disable the START condition generation */
		Reset_Bitfield(I2Cx->I2C_CR1.bits.START);
	}
}

/**================================================================
* @Fn				-I2C_Generate_Stop
* @brief		  	-generate stop condition to end transmitter .
* @param [in] 		-I2Cx:  specified I2Cx x=[ 1 : 2 ]
* @retval 			-none
* Note				-none
*/
void I2C_Generate_Stop(I2C_TypeDef* I2Cx )
{
	Set_Bitfield(I2Cx->I2C_CR1.bits.STOP);
}

/**================================================================
* @Fn				- I2C_Send_Address
* @brief		  	- send address by I2C from master to slave
* @param [in] 		- I2Cx : where x can be (1 or 2 ) to select I2C peripheral
* @param [in] 		- Slave_Address: slave address
* @param [in] 		- Direction: Direction of communication ( Transmitter or Receiver )
* @retval 			- none
* Note				- none
*/
void I2C_Send_Address(I2C_TypeDef *I2Cx, uint16_t Slave_Address, I2C_Direction_t Direction)
{

	/*  SB=1, cleared by reading SR1 register followed by writing the DR register */
	while(!EV5(I2Cx));
	/* for 10-bit address mode  */
	if(I2Cx->I2C_OAR1.bits.ADDMODE){
		/* send The 10-bit Address Header with 2 MSB of Slave Address */
		Write_Port(I2Cx->I2C_DR.reg, ((Slave_Address & 0x300)>>8)|(0b11110<<2)) ;
		while(!EV9(I2Cx));
	}

	if(Direction == Receiver)
	{
		/* Set the address bit 0 for read */
		Write_Port(I2Cx->I2C_DR.reg, (Slave_Address << 1) | (0x01));
		/* for 10-bit address mode  */
		if(I2Cx->I2C_OAR1.bits.ADDMODE){

				while(!EV6(I2Cx));
				I2C_Generate_Start(I2Cx, Repeated_Start, ENABLE);
				/* send The 10-bit Address Header with 2 MSB of Slave Address */
				Write_Port(I2Cx->I2C_DR.reg, ((Slave_Address & 0x300)>>8)|(0b11110<<2)) ;
			}
	}
	else if(Direction == Transmitter)
	{
		/* Reset the address bit 0 for write */
		Write_Port(I2Cx->I2C_DR.reg, Slave_Address << 1);
	}


}

/**================================================================
* @Fn				-Get_flag_stutus
* @brief		  	-check the current state to I2C ( busy , receive data , receive address ...... ) .
* @param [in] 		-flag: the status to be check
* @param [in] 		-I2Cx:   where x can be (1 or 2)
* @retval 			-FlagStatus
* Note				-none
*/

Std_Status_t I2C_GetFlagStatus(I2C_TypeDef* I2Cx, Std_Bool_t flag )
{
	Std_Status_t Flag_State ;

	if (flag == I2C_BUSY(I2Cx)){
		if (I2C_BUSY(I2Cx))
			Flag_State=SET ;
		else
			Flag_State=RESET ;
	}else if(flag == EV5(I2Cx)){
		if (EV5(I2Cx))
			Flag_State=SET ;
		else
			Flag_State=RESET ;
	}else if(flag ==  EV6(I2Cx)){
		if (EV6(I2Cx))
			Flag_State=SET ;
		else
			Flag_State=RESET ;
		}

	else if(flag ==  EV7(I2Cx)) {
		if (EV7(I2Cx))
			Flag_State=SET ;
		else
			Flag_State=RESET ;
		}
	else if(flag ==  EV8(I2Cx)) {
		if (EV8(I2Cx))
			Flag_State=SET ;
		else
			Flag_State=RESET ;
		}
	else if(flag ==  EV8_1(I2Cx)) {
		if (EV8_1(I2Cx))
			Flag_State=SET ;
		else
			Flag_State=RESET ;
		}
	else if(flag ==  EV8_2(I2Cx)) {
		if (EV8_2(I2Cx))
			Flag_State=SET ;
		else
			Flag_State=RESET ;
		}
	else if(flag ==  EV9(I2Cx)) {
		if (EV9(I2Cx))
			Flag_State=SET ;
		else
			Flag_State=RESET ;
		}
	return Flag_State ;
}

/**================================================================
* @Fn- MCAL_I2C_init
* @brief 		-Initializes the I2Cx according to the specified parameters of I2C_Config
* @param [in] 	-I2Cx : where x can be (1 or 2) to select I2C peripheral
*  @param [in]	-I2C_Config : Pointer to I2C_Config_t which contains
 * 				 the configuration info for specified I2C
* @retval -
* Note			- None
*/
void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_Config_t* I2C_Config){
	/* Safety for registers before the entire configuration be applied */
	uint16_t Temp_CR1 = 0;
	uint16_t Temp_CR2 = 0;
	uint16_t Temp_Reg = 0;
	uint32_t pclk1 = 0;
	uint16_t Temp_FreqReg = 0;
	//enable I2C clock
	if (I2Cx == I2C1)
	{
		RCC_I2C1_CLOCK_EN();
		Global_I2C_Config[I2C1_INDEX] = *I2C_Config;
	}
	else if (I2Cx == I2C2){

		RCC_I2C2_CLOCK_EN();
		Global_I2C_Config[I2C2_INDEX] = *I2C_Config;
	}
	//Set Bus Mode
	if(I2C_Config->Bus_Mode == SMBus_Mode)
		Set_Config(Temp_CR1, SMBus_Mode);
	else
		Reset_Config(Temp_CR1, I2C_Mode);


	// set Bits 5:0 FREQ[5:0]: Peripheral clock frequency
	pclk1 = MCAL_RCC_GetPCLCK1Freq();
	Temp_FreqReg = (uint16_t)(pclk1 / 1000000);
	Set_Config(Temp_CR2, Temp_FreqReg);

	Temp_FreqReg = 0;
	//Set CCR
	/* CCR register must be configured only when the I2C is disabled (PE = 0). */
	Reset_Bitfield(I2Cx->I2C_CR1.bits.PE);
	/* fSCL = 1/(Thigh + Tlow) */
	if ( I2C_Config->I2C_ClockSpeed.I2C_SpeedMode == Standard_Speed_Mode){
		Reset_Config(Temp_Reg, Standard_Speed_Mode);
		// CCR = Fpclk1 / (2 * I2C_ClockFreq )
		Temp_FreqReg = pclk1/(2*I2C_Config->I2C_ClockSpeed.I2C_ClockFreq);
		Set_Config(Temp_Reg, Temp_FreqReg);
	}else{ //Fast Mode
		Set_Config(Temp_Reg, Fast_Speed_Mode);
		if(I2C_Config->I2C_DutyCycle == I2C_DutyRatio_2){
			Temp_FreqReg = pclk1/(3*I2C_Config->I2C_ClockSpeed.I2C_ClockFreq);
			Set_Config(Temp_Reg, Temp_FreqReg);
		}else{			//I2C_DutyRatio_16_9
			Temp_FreqReg = pclk1/(25*I2C_Config->I2C_ClockSpeed.I2C_ClockFreq);
			Set_Config(Temp_Reg, Temp_FreqReg);
		}
	}
	Set_Config(I2Cx->I2C_CCR.reg, Temp_Reg);
	Temp_Reg = 0;


	//set Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
	/* These bits must be programmed with the maximum SCL rise freq
	 * given in the I2C bus specification, incremented by 1 */
	Write_Port(I2Cx->I2C_TRISE.reg, Temp_FreqReg+1);

	// set I2C ACK
	if(I2C_Config->I2C_ACK_Control == I2C_ACK_Enable){
		Set_Config(Temp_CR1, I2C_ACK_Enable);
	}else{
		Reset_Config(Temp_CR1, I2C_ACK_Disable);
	}

	// set I2C ENCG General call address enable
	if(I2C_Config->G_CallAddress_Detection == G_CallAddress_Enable){
		Set_Config(Temp_CR1, G_CallAddress_Enable);
	}else{
		Reset_Config(Temp_CR1, G_CallAddress_Disable);
	}
	//Set Address
	if(I2C_Config->I2C_DeviceAddress.Dual_Add_Ack == Dual_Adress_Enable){
		Set_Bitfield(I2Cx->I2C_OAR2.bits.ENDUAL);
		Set_Config(I2Cx->I2C_OAR2.reg,I2C_Config->I2C_DeviceAddress.Dual_Interface_Address<<1);

		Reset_Config(Temp_Reg, Addressing_Mode_7bit);
		Set_Config(Temp_Reg, I2C_Config->I2C_DeviceAddress.Own_Interface_Address<<1);
	}else{
		Reset_Bitfield(I2Cx->I2C_OAR2.bits.ENDUAL);
		if(I2C_Config->I2C_Addressing_Mode == Addressing_Mode_7bit){
			Reset_Config(Temp_Reg, Addressing_Mode_7bit);
			Set_Config(Temp_Reg, I2C_Config->I2C_DeviceAddress.Own_Interface_Address<<1);
		}else{
			Set_Config(Temp_Reg, Addressing_Mode_10bit);
			Set_Config(Temp_Reg, I2C_Config->I2C_DeviceAddress.Own_Interface_Address<<1);
		}
	}
	Set_Config(I2Cx->I2C_OAR1.reg, Temp_Reg);
	Temp_Reg = 0;
	//check interrupt mode (slave mode)
	if(I2C_Config->P_IRQ_CallBack != NULL){		//this enables Slave IRQ
		//Set interrupt event
		if( I2C_Config->IRQ_Enable == I2C_IRQ_EV_EN)
		{
			Set_Config(Temp_CR2, I2C_IRQ_EV_EN);
			if(I2Cx == I2C1)
			{
				NVIC_IRQ31_I2C1_EV_ENABLE();
			}

			else
			{
				NVIC_IRQ33_I2C2_EV_ENABLE();
			}

		}else if ( I2C_Config->IRQ_Enable == I2C_IRQ_ER_EN){
			Set_Config(Temp_CR2, I2C_IRQ_ER_EN);
			if(I2Cx == I2C1)
			{
				NVIC_IRQ32_I2C1_ER_ENABLE();
			}

			else
			{
				NVIC_IRQ34_I2C2_ER_ENABLE();
			}
		}else if ( I2C_Config->IRQ_Enable == I2C_IRQ_ER_EV_EN){
					Set_Config(Temp_CR2, I2C_IRQ_ER_EV_EN);
					if(I2Cx == I2C1)
					{
						NVIC_IRQ31_I2C1_EV_ENABLE();
						NVIC_IRQ32_I2C1_ER_ENABLE();
					}

					else
					{
						NVIC_IRQ33_I2C2_EV_ENABLE();
						NVIC_IRQ34_I2C2_ER_ENABLE();
					}
		}else{ //I2C_IRQ_Disable
			Reset_Config(Temp_CR2, I2C_IRQ_Disable);
			NVIC_IRQ31_I2C1_EV_DISABLE();
			NVIC_IRQ32_I2C1_ER_DISABLE();
			NVIC_IRQ33_I2C2_EV_DISABLE();
			NVIC_IRQ34_I2C2_ER_DISABLE();

		}
	}
	// Reset I2C Status Registers
	Reset_Port(I2Cx->I2C_SR1.reg);
	Reset_Port(I2Cx->I2C_SR2.reg);


	Set_Config(I2Cx->I2C_CR1.reg, Temp_CR1);
	Set_Config(I2Cx->I2C_CR2.reg, Temp_CR2);

	// Enable I2Cx Peripheral
	Set_Bitfield(I2Cx->I2C_CR1.bits.PE);

}
/**================================================================
 * @Fn			-MCAL_I2C_Deinit
 * @brief 		-Reset all the I2C registers
 * @param [in] 	-I2Cx : where x can be (1 or 2) to select I2C peripheral
 * @retval	 	-none
 * Note			-none
 */
void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx){
	if( I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_DISABLE();
		NVIC_IRQ32_I2C1_ER_DISABLE();
		RCC_I2C1_CLOCK_Disable();
		Reset_Bitfield(I2Cx->I2C_CR1.bits.PE);
	}
	else
	{
		NVIC_IRQ33_I2C2_EV_DISABLE();
		NVIC_IRQ34_I2C2_ER_DISABLE();
		RCC_I2C2_CLOCK_Disable();
		Reset_Bitfield(I2Cx->I2C_CR1.bits.PE);
	}
}
/**================================================================
 * @Fn			-MCAL_I2C_SetPIN
 * @brief 		-Set specific I2Cx Pin value & Direction
 * @param [in] 	-I2Cx : where x can be (1 or 2) to select I2C peripheral
 * @retval	 	-none
 * Note			-none
 */

void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx){
	GPIO_PinConfig_t I2C_PinCfg;
	if(I2Cx == I2C1)
	{
		//SCL :  PB6
		//SDA :  PB7
		I2C_PinCfg.GPIO_PINNumber =GPIO_PIN6;
		I2C_PinCfg.GPIO_Mode = GPIO_Mode_AF_OUT_OD;
		I2C_PinCfg.GPIO_Speed= GPIO_Speed_10MHZ;
		MCAL_GPIO_init(GPIOB, &I2C_PinCfg);

		I2C_PinCfg.GPIO_PINNumber =GPIO_PIN7;
		I2C_PinCfg.GPIO_Mode = GPIO_Mode_AF_OUT_OD;
		I2C_PinCfg.GPIO_Speed= GPIO_Speed_10MHZ;
		MCAL_GPIO_init(GPIOB, &I2C_PinCfg);
	}

	else
	{
		//SCL: PB10
		//SDA:  PB11
		I2C_PinCfg.GPIO_PINNumber =GPIO_PIN10;
		I2C_PinCfg.GPIO_Mode = GPIO_Mode_AF_OUT_OD;
		I2C_PinCfg.GPIO_Speed= GPIO_Speed_10MHZ;
		MCAL_GPIO_init(GPIOB, &I2C_PinCfg);

		I2C_PinCfg.GPIO_PINNumber =GPIO_PIN11;
		I2C_PinCfg.GPIO_Mode = GPIO_Mode_AF_OUT_OD;
		I2C_PinCfg.GPIO_Speed= GPIO_Speed_10MHZ;
		MCAL_GPIO_init(GPIOB, &I2C_PinCfg);
	}
}

/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_TX
 * @brief 			- I2C Master Transmit data
 * @param [in] 		- I2Cx : where x can be (1 or 2 ) to select I2C peripheral
 * @param [in] 		- slave address
 * @param [in] 		- pTxData : a pointer to the data which will be send
 * @param [in] 		- DataLength : number of data bytes to be Received
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */

void MCAL_I2C_Master_TX(I2C_TypeDef* I2Cx, uint16_t SlaveAddress, uint8_t* pTxData, uint8_t DataLength, I2C_Start_t Start, I2C_Stop_t Stop){
	uint8_t i ;
	/* Set the START bit in the I2C_CR1 register to generate a Start condition */
	I2C_Generate_Start(I2Cx, Start, ENABLE);
	/* SB=1, cleared by reading SR register followed by writing D2 register */
	while(!EV5(I2Cx));
	I2C_Send_Address(I2Cx, SlaveAddress, Transmitter);
	/* ADDR=1, cleared by reading SR1 register followed by reading SR2. */
	while(!EV6(I2Cx));
	/* TxE=1,TRA=1, BUSY=1,MSL=1 : Master Transmitter Event, shift register empty, data register empty, write Data1 in DR. */
	while(!EV8_1(I2Cx));
	for (i = 0; i < DataLength; i++)
		{
			/*  Write  the data to be sent on I2C DR register */
			Write_Port(I2Cx->I2C_DR.reg, pTxData[i]);

			/* EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register. */
			while(!EV8(I2Cx));
		}
	/* EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition. */
	while(!EV8_2(I2Cx));

	if(Stop == With_Stop){
		/* Set the STOP bit in the I2C_CR1 register to generate a Stop condition */
		I2C_Generate_Stop(I2Cx);
	}

}

/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_RX
 * @brief 			- I2C Master Receives data
 * @param [in] 		- I2Cx : where x can be (1 or 2 ) to select I2C peripheral
 * @param [in] 		- slave address
 * @param [in] 		- pRxData : a pointer to the data which will be received
 * @param [in] 		- DataLength : number of data bytes to be Received
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Master_RX(I2C_TypeDef* I2Cx, uint16_t SlaveAddress, uint8_t* pRxData, uint8_t DataLength, I2C_Start_t Start, I2C_Stop_t Stop){
	uint8_t i ;
	uint8_t I2Cx_INDEX = Get_I2C_Index(I2Cx);
	/* Set the START bit in the I2C_CR1 register to generate a Start condition */
	I2C_Generate_Start(I2Cx, Start, ENABLE);
	/* SB=1, cleared by reading SR register followed by writing D2 register */
	while(!EV5(I2Cx));
	I2C_Send_Address(I2Cx, SlaveAddress, Receiver);
	/* ADDR=1, cleared by reading SR1 register followed by reading SR2. */
	while(!EV6(I2Cx));

	/* Enable Acknowledge return after a byte is received (matched address or data)*/
	Set_Bitfield(I2Cx->I2C_CR1.bits.ACK);


	for (i = DataLength; i > 1 ; i--)
		{
			/*EV7: RxNE=1 cleared by reading DR register*/
			while(!EV7(I2Cx));
			/*  read the data to be sent on I2C DR register */
			*pRxData =  I2Cx->I2C_DR.reg;
			pRxData++;


		}
	/*EV7_1: RxNE=1 cleared by reading DR register, program ACK=0 and STOP request */
	/* Disable Acknowledge return after a byte is received (matched address or data)*/
	Reset_Bitfield(I2Cx->I2C_CR1.bits.ACK);
	if(Stop == With_Stop){
		/* Set the STOP bit in the I2C_CR1 register to generate a Stop condition */
		I2C_Generate_Stop(I2Cx);
	}
	// Return I2C ACK Config to its original
	if(Global_I2C_Config[I2Cx_INDEX].I2C_ACK_Control == I2C_ACK_Enable){
		Set_Bitfield(I2Cx->I2C_CR1.bits.ACK);
	}else{
		Reset_Bitfield(I2Cx->I2C_CR1.bits.ACK);
	}


}
/* ================================================================
 * @Fn 				- MCAL_I2C_Slave_TX
 * @brief 			- Slave send data to master using interrupt
 * @param [in] 		- I2Cx : where x can be (1 or 2 ) to select I2C peripheral
 * @param [in] 		- TxData : slave data to be sent to master
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Slave_TX(I2C_TypeDef *I2Cx, uint8_t TxData){
	Write_Port(I2Cx->I2C_DR.reg, TxData);
}
/* ================================================================
 * @Fn 				- MCAL_I2C_Slave_RX
 * @brief 			- Receive data by I2C from master to slave
 * @param [in] 		- I2Cx : where x can be (1 or 2 ) to select I2C peripheral
 * @retval 			- return data received from master .
 * Note 			- None
 */

uint8_t MCAL_I2C_Slave_RX(I2C_TypeDef* I2Cx){
	return (uint8_t)I2Cx->I2C_DR.reg;
}


/*
 * =============================================================
 *                      ISR Function Definitions
 * =============================================================
 */

void I2C1_EV_IRQHandler()
{
	uint8_t dummyRead;

	struct I2C_IRQ_Src irq_src;
	irq_src.I2C_EV_STOP = (I2C1->I2C_SR1.bits.STOPF);
	irq_src.I2C_EV_ADDR_Matched = (I2C1->I2C_SR1.bits.ADDR);
	irq_src.I2C_EV_DATA_REQ = (I2C1->I2C_SR2.bits.TRA);
	irq_src.I2C_EV_DATA_RCV = ~(I2C1->I2C_SR2.bits.TRA);
	// Slave mode
	if(!I2C1->I2C_SR2.bits.MSL){
		// Slave Received address matched
		if(irq_src.I2C_EV_ADDR_Matched){
			dummyRead  = I2C1->I2C_SR1.reg ;
			dummyRead  = I2C1->I2C_SR2.reg;
		}else if(irq_src.I2C_EV_DATA_RCV){
			dummyRead  = I2C1->I2C_DR.reg ;
		}else if(irq_src.I2C_EV_STOP){
			dummyRead  = I2C1->I2C_SR1.reg ;
			Set_Config(I2C1->I2C_CR1.reg, 0x0000);
		}
	}
	Global_I2C_Config[I2C1_INDEX].P_IRQ_CallBack(irq_src);
}

void I2C1_ER_IRQHandler()
{

}
