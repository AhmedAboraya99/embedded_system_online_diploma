#ifndef _STM32F103X6_I2C_H_
#define _STM32F103X6_I2C_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6.h"
#include "STM32F103_RCC_Driver.h"
#include "STM32F103_GPIO_Driver.h"
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*




//-----------------------------
//User type definitions (enum)
//-----------------------------

typedef enum
{
	Transmitter,
	Receiver
}I2C_Direction_t;



//@ref Bus_Mode_define
typedef enum
{
	I2C_Mode =  ~(1<<1U),
	SMBus_Mode =  (1<<1U),
}Bus_Mode_t;

//@ref IRQ_Enable_define
typedef enum
{
	I2C_IRQ_Disable =  ~(7<<8U),
	I2C_IRQ_ER_EN 	=  (1<<8)|(1<<10),		//I2C Event error condition
	I2C_IRQ_EV_EN 	=  (1<<9)|(1<<10),		// successful I2C address/ data communication
	I2C_IRQ_ER_EV_EN = (1<<8)|(1<<9)|(1<<10)
}I2C_IRQ_t;



//@ref Addressing_Mode_define
typedef enum {
	Addressing_Mode_7bit =  ~(1<<15U),
	Addressing_Mode_10bit =  (1<<15U),
}Addressing_Mode_t;

//@ref Communication_Speed_define

//@ref I2C_SpeedMode_define
typedef enum {
	Standard_Speed_Mode = ~(1<<15U),		//up to 100 kHz
	Fast_Speed_Mode =  	   (1<<15U),			//up to 400 kHz
}I2C_SpeedMode_t;

//@ref I2C_ClockFreq_define
typedef enum {
	I2C_SM_50KHz =  	(50000U),
	I2C_SM_100KHz =  	(100000U),
	I2C_FM_200KHz =		(200000U),
	I2C_FM_400KHz =		(400000U),
}I2C_ClockFreq_t;


//@ref General_CallAddress_Define
typedef enum
{
	G_CallAddress_Disable =  ~(1<<6U),
	G_CallAddress_Enable = 	  (1<<6U)
}G_CallAddress_t;

//@ref I2C_ACK_Define
typedef enum
{
	I2C_ACK_Disable =  ~(1<<10U),
	I2C_ACK_Enable =    (1<<10)
}I2C_ACK_t;

//@ref Clock_Stretch_Define
typedef enum
{
	Clock_Stretch_Enable =     ~(1<<10U),
	Clock_Stretch_Disable =    (1<<10)
}Clock_Stretch_t;

// @ref I2C_DutyCycle_define
typedef enum
{
	I2C_DutyRatio_2 =     ~(1<<14U),
	I2C_DutyRatio_16_9 =  (1<<14)
}I2C_Duty_t;

//@ref Dual_Add_Ack_Define
typedef enum
{
	Dual_Adress_Disable =  ~(1<<0U),
	Dual_Adress_Enable =    (1<<0)
}Dual_Add_t;

//@ref I2C_Start_Define
typedef enum
{
	Start,
	Repeated_Start
}I2C_Start_t;
//@ref I2C_Stop_Define
typedef enum
{
	Without_Stop,
	With_Stop
}I2C_Stop_t;

//-----------------------------
//Configure structure for I2C
//-----------------------------
typedef struct {
	Dual_Add_t 		Dual_Add_Ack;				//@ref Dual_Add_Define
	uint16_t		Own_Interface_Address;
	uint16_t		Dual_Interface_Address;
}Address_Config_t;

typedef struct {
	I2C_SpeedMode_t 	I2C_SpeedMode;	//@ref I2C_SpeedMode_define
	I2C_ClockFreq_t		I2C_ClockFreq;	//@ref I2C_ClockFreq_define
}I2C_ClockSpeed_t;

//@ref I2C_IRQ_Src_define
struct I2C_IRQ_Src{
	uint8_t 	I2C_EV_STOP:1;				//Stop condition is detected
	uint8_t		I2C_EV_ADDR_Matched:1;		//address matched with the OAR registers or a general call Addresses
	uint8_t		I2C_EV_DATA_REQ:1;			//Data bytes Transmitted Request
	uint8_t		I2C_EV_DATA_RCV:1;			////Data bytes Received
	uint8_t			Reserved:4;
};
typedef struct {
	Bus_Mode_t	Bus_Mode;					//select SMBus / I2C Mode
											//@ref Bus_Mode_define

	I2C_ClockSpeed_t  I2C_ClockSpeed;		//configure I2C communication Speed Mode( SM or FM)
											//@ref Communication_Speed_define

	Clock_Stretch_t Clock_Stretch;				//enable or disable Stretch_Mode
											//@ref Clock_Stretch_Define

	I2C_Duty_t I2C_DutyCycle;					//select  Fm mode duty cycle
											// @ref I2C_DutyCycle_define

	Addressing_Mode_t I2C_Addressing_Mode;		//select addressing mode(7-bit/10-bit)
											//@ref Addressing_Mode_define

	Address_Config_t I2C_DeviceAddress;		//select number of Stop Bits
											//@ref StopBits_define

	I2C_ACK_t I2C_ACK_Control;				//enable or disable the ACK of transmitted data
											//@ref I2C_ACK_Define

	G_CallAddress_t G_CallAddress_Detection;			//enable or disable General Call Address Detection
											//@ref General_CallAddress_Define

	I2C_IRQ_t IRQ_Enable;					//enable or disable I2C IRQ Event/Error
											//@ref IRQ_Enable_define

	void (*P_IRQ_CallBack)(struct I2C_IRQ_Src);		//pointer to IRQ call back function which will be called once IRQ happened
													//Slave State is the source of IRQ @ref Slave_State_define
}I2C_Config_t;

//-----------------------------
//Macros Configuration References
//-----------------------------


/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/

#define I2C1_INDEX				0
#define I2C2_INDEX				1

#define I2C_BUSY(I2Cx)	(I2Cx->I2C_SR2.bits.BUSY)

#define EV5(I2Cx)		I2Cx->I2C_SR1.bits.SB
#define EV6(I2Cx)		I2Cx->I2C_SR1.bits.ADDR
#define EV7(I2Cx)		I2Cx->I2C_SR1.bits.RxNE
#define EV8(I2Cx)		I2Cx->I2C_SR1.bits.TxE
#define EV8_1(I2Cx)		((I2Cx->I2C_SR1.bits.TxE)&(I2Cx->I2C_SR2.bits.TRA)&(I2Cx->I2C_SR2.bits.BUSY)&(I2Cx->I2C_SR2.bits.MSL))
#define EV8_2(I2Cx)		((I2Cx->I2C_SR1.bits.TxE)&(I2Cx->I2C_SR1.bits.BTF))
#define EV9(I2Cx)		I2Cx->I2C_SR1.bits.ADD10

/*
* ===============================================
* APIs Supported by "MCAL I2C DRIVER"
* ===============================================
*/
void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_Config_t* I2C_Config);
void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx);
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx);

void MCAL_I2C_Master_TX(I2C_TypeDef* I2Cx, uint16_t SlaveAddress, uint8_t* pTxData, uint8_t DataLength, I2C_Start_t Start, I2C_Stop_t Stop);
void MCAL_I2C_Master_RX(I2C_TypeDef* I2Cx, uint16_t SlaveAddress, uint8_t* pRxData, uint8_t DataLength, I2C_Start_t Start, I2C_Stop_t Stop);
uint8_t MCAL_I2C_Slave_RX(I2C_TypeDef* I2Cx);
void MCAL_I2C_Slave_TX(I2C_TypeDef *I2Cx, uint8_t TxData);


#endif
