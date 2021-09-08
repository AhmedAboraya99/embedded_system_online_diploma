#include "Queue.h"
//----initialization of Stack----
	//Dynamic Buffer *Linked list*
Buffer_Status FIFO_init (FIFO_Buff_t* P_Buff,element_type* Buff_item,uint32_t Buff_length){
	//set Base Pointer
	P_Buff->base =Buff_item;
	//set Length
	P_Buff->length = Buff_length;
	//set head pointer
	P_Buff->head = P_Buff->base;
	//set tail pointer
	P_Buff->tail = P_Buff->base;
	//set current count
	P_Buff->count = 0;
	if (P_Buff->base && P_Buff->length)
		return FIFO_no_error;
	else
		return FIFO_Null ;
	}
Buffer_Status Buffer_Full (FIFO_Buff_t* P_Buff){
	//check if Queue is valid
	if(!P_Buff || !P_Buff->base || !P_Buff->head || !P_Buff->tail)
		return FIFO_Null ;
	//check if buffer is full
	if(P_Buff->count >= P_Buff->length){
		printf("Queue is full \n");
		return FIFO_full ;
	}
	return FIFO_no_error ;
    }
Buffer_Status FIFO_enqueue (FIFO_Buff_t* P_Buff,element_type ENQ_Data){
	//check if buffer is valid
	if(Buffer_Full (P_Buff) == FIFO_no_error){
		*(P_Buff->head) = ENQ_Data ;
		P_Buff->count++;
		//Circular FIFO
		if(P_Buff->head == (P_Buff->base +(P_Buff->length * sizeof(element_type))))
				P_Buff->head = P_Buff->base;
		else
			P_Buff->head++;
		return FIFO_no_error ;
	}
	else
		return Buffer_Full(P_Buff) ;
}
Buffer_Status FIFO_dequeue(FIFO_Buff_t* P_Buff,element_type* DEQ_Data){
	//check if buffer is valid
	if(!P_Buff || !P_Buff->base || !P_Buff->head )
			return FIFO_Null ;
	//check if buffer is empty
	if(P_Buff->count==0)
			return FIFO_empty ;
	//change pointers and pop value of item from Queue
	*(DEQ_Data)=*(P_Buff->tail);
	P_Buff->count--;
	//Circular FIFO
	if(P_Buff->tail == (P_Buff->base +(P_Buff->length * sizeof(element_type))))
		P_Buff->tail = P_Buff->base;
	else
		P_Buff->tail++;

	return FIFO_no_error;
}

void print_FIFO(FIFO_Buff_t* P_Buff){
	element_type temp;
	int i;
	if (P_Buff->count == 0){
		printf("Queue is empty \n");
	}
	printf("\n====FIFO PRINT====\n");
	temp = *(P_Buff->tail);
	for(i=0; i<P_Buff->count ;i++ ){
		printf("\t  (%d) \n",temp);
		temp++ ;
	}
	printf("=================\n");
}
