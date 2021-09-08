#include"Stack.h"
#define LIFO_Buff_length 5

int main(){

	uint32_t i , temp=0 ;
	LIFO_Buff_t first_buffer, second_buffer;
	//----initialization of Stack----
	//static Buffer *Array*
	uint32_t Static_Buffer [LIFO_Buff_length];
	first_buffer.base = &Static_Buffer[0];

	if ( LIFO_init(&first_buffer, Static_Buffer, LIFO_Buff_length)==LIFO_no_error)
			printf("Stack (static allocation) initialized  ---- Done \n");
	for(i=0; i<7 ;i++ ){

		if (LIFO_push_item(&first_buffer,i)== LIFO_no_error)
			printf("Stack push (%d) ---- Done \n",i);
		else if (LIFO_push_item(&first_buffer,i)==LIFO_full)
							printf("Stack is full \n");
		else
			printf("Stack push (%d) ---- Failed \n",i);
	}
	for(i=0; i<7 ;i++ ){
			if (LIFO_pop_item(&first_buffer,&temp)== LIFO_no_error)
				printf("Stack pop (%d) ---- Done \n",temp);
			else if (LIFO_pop_item(&first_buffer,&temp)== LIFO_empty)
							printf("Stack is empty \n");
			else
				printf("Stack pop (%d) ---- Failed \n",temp);
		}
	//Dynamic Buffer *Linked list*
		uint32_t* Dynamic_Buffer = (uint32_t*) malloc(LIFO_Buff_length);
		second_buffer.base = Dynamic_Buffer;

		if ( LIFO_init(&second_buffer, Dynamic_Buffer, LIFO_Buff_length)==LIFO_no_error)
				printf("Stack (dynamic Allocation) initialized  ---- Done \n");
		for(i=0; i<7 ;i++ ){
			if (LIFO_push_item(&first_buffer,i)== LIFO_no_error)
				printf("Stack push (%d) ---- Done \n",i);
			else if (LIFO_push_item(&first_buffer,i)== LIFO_full)
					printf("Stack is full \n");
			else
				printf("Stack push (%d) ---- Failed \n",i);
		}
		for(i=0; i<7 ;i++ ){
			if (LIFO_pop_item(&second_buffer,&temp)== LIFO_no_error)
				printf("Stack pop (%d) ---- Done \n",temp);
			else if (LIFO_pop_item(&second_buffer,&temp)== LIFO_empty)
							printf("Stack is empty \n");
			else
				printf("Stack pop (%d) ---- Failed \n",temp);
			}
	return 0;
}
