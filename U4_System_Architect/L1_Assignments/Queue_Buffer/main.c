#include"Queue.h"
#define FIFO_Buff_length 5
element_type  Static_Buffer[FIFO_Buff_length];
int main(){
	element_type i , temp=0 ;
	FIFO_Buff_t Uart_FIFO, CAN_FIFO;
	//----initialization of Queue----
	//static Buffer *Array*
	element_type Static_Buffer [FIFO_Buff_length];

	if ( FIFO_init(&Uart_FIFO, Static_Buffer, FIFO_Buff_length)==FIFO_no_error)
			printf("Queue (static allocation) initialized  ---- Done \n");
	for(i=0; i<5 ;i++ ){

		if (FIFO_enqueue(&Uart_FIFO,i)== FIFO_no_error)
			printf("Queue enqueue: %d ---- Done \n",i);
		else if (FIFO_enqueue(&Uart_FIFO,i)==FIFO_full)
			printf("Queue is full \n");
		else
			printf("Queue enqueue: %d ---- Failed \n",i);
	}
	print_FIFO(&Uart_FIFO);

	for(i=0; i<5 ;i++ ){
		if (FIFO_dequeue(&Uart_FIFO,&temp)== FIFO_no_error)
			printf("Queue dequeue: %d ---- Done \n",temp);
		else if (FIFO_dequeue(&Uart_FIFO,&temp)== FIFO_empty)
						printf("Queue is empty \n");
		else
			printf("Queue dequeue: %d ---- Failed \n",temp);
	}
	//Dynamic Buffer *Linked list*
	element_type* Dynamic_Buffer = (element_type*) malloc(FIFO_Buff_length);

	if ( FIFO_init(&CAN_FIFO, Dynamic_Buffer, FIFO_Buff_length)==FIFO_no_error)
			printf("Queue (dynamic Allocation) initialized  ---- Done \n");
	for(i=0; i<6 ;i++ ){
		if (FIFO_enqueue(&CAN_FIFO,i)== FIFO_no_error)
			printf("Queue enqueue: %d ---- Done \n",i);
		else
			printf("Queue enqueue: %d ---- Failed \n",i);
	}
	for(i=0; i<3 ;i++ ){
		if (FIFO_dequeue(&CAN_FIFO,&temp)== FIFO_no_error)
			printf("Queue dequeue: %d ---- Done \n",temp);
		else if (FIFO_dequeue(&CAN_FIFO,&temp)== FIFO_empty)
			printf("Queue is empty \n");
		else
			printf("Queue dequeue: %d ---- Failed \n",temp);
		}
	return 0;
}
