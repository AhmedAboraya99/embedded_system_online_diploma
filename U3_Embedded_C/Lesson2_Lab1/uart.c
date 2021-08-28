#include "uart.h"
//UART Registers
#define UARTDR0 *((volatile unsigned int* const)((unsigned int*)0x101f1000))

void Uart_send_string(unsigned char* Ptx_string)
{
	while (*Ptx_string != '\0') 
	{
		UARTDR0 = (unsigned int)(*Ptx_string); /* Transmit char to uart */
		Ptx_string++ ; /* point to next char */
	}
}