#include "uart.h"
unsigned char String_buffer[100] = "Learn-in-depth:<Ahmed Aboraya>";

void main()
{
	/* Versatilepb physical Board */
	Uart_send_string(String_buffer);
}