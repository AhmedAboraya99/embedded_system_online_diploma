#ifndef _QUEUE_H
#define _QUEUE_H
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
//select element type
#define element_type uint8_t
//Define some pointers and variables defined and changed at each address in buffer
typedef struct{
	uint32_t length;
	element_type* base;
	element_type* head;
	element_type* tail;
	uint32_t count;
}FIFO_Buff_t ;
//Define return data types define status of Buffer
typedef enum{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_Null,
}Buffer_Status ;

//Call to APIs
Buffer_Status FIFO_init (FIFO_Buff_t* P_Buff,element_type* Buff_item,uint32_t Buff_length);
Buffer_Status FIFO_enqueue (FIFO_Buff_t* P_Buff,element_type ENQ_Data);
Buffer_Status FIFO_dequeue (FIFO_Buff_t* P_Buff,element_type* DEQ_Data);
Buffer_Status Buff_Full (FIFO_Buff_t* P_Buff);
void print_FIFO(FIFO_Buff_t* P_Buff);

#endif
