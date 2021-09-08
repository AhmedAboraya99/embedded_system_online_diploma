#include "Stack.h"
//----initialization of Stack----
	//Dynamic Buffer *Linked list*
Buffer_Status LIFO_init (LIFO_Buff_t* P_Buff,uint32_t* Buff_item,uint32_t Buff_length){
	//set Base Pointer
	P_Buff->base =Buff_item;
	//set Length
	P_Buff->length = Buff_length;
	//set head pointer
	P_Buff->head = P_Buff->base;
	//set current count
	P_Buff->count = 0;
	if (P_Buff->base && P_Buff->length)
		return LIFO_no_error;
	else
		return LIFO_Null ;
	}

Buffer_Status LIFO_push_item (LIFO_Buff_t* P_Buff,uint32_t Buff_item){
	//check if buffer is valid
	if(!P_Buff || !P_Buff->base || !P_Buff->head )
		return LIFO_Null ;
	//check if buffer is full
	if(P_Buff->head == (P_Buff->base + P_Buff->length) )
		return LIFO_full ;
	//push value of item in the stack and change pointers
	*(P_Buff->head) = Buff_item ;
	P_Buff->head++;
	P_Buff->count++;

	return LIFO_no_error ;
}
Buffer_Status LIFO_pop_item (LIFO_Buff_t* P_Buff,uint32_t* Buff_item){
	//check if buffer is valid
	if(!P_Buff || !P_Buff->base || !P_Buff->head )
			return LIFO_Null ;
	//check if buffer is empty
	if(P_Buff->head == P_Buff->base)
			return LIFO_empty ;
	//change pointers and pop value of item from stack
	P_Buff->head--;
	*(Buff_item)=*(P_Buff->head);
	P_Buff->count--;

	return LIFO_no_error;
}
