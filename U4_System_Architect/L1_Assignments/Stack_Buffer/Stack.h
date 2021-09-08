#ifndef _SKACK_H
#define _SKACK_H
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

//Define some pointers and variables defined and changed at each address in buffer 
typedef struct{
	uint32_t length;
	uint32_t* base;
	uint32_t* head;
	uint32_t count;
}LIFO_Buff_t ;
//Define return data types define status of Buffer
typedef enum{
	LIFO_no_error,
	LIFO_full,
	LIFO_empty,
	LIFO_Null,
}Buffer_Status ;

//Call to APIs 
Buffer_Status LIFO_init (LIFO_Buff_t* P_Buff,uint32_t* Buff_item,uint32_t Buff_length);
Buffer_Status LIFO_push_item (LIFO_Buff_t* P_Buff,uint32_t item);
Buffer_Status LIFO_pop_item (LIFO_Buff_t* P_Buff,uint32_t* item);

#endif
