#include "typedef.h"
#include "Queue.h"
#include "Student_DataBase.h"


//----initialization of Stack----
	//Dynamic Buffer *Linked list*
Buffer_Status FIFO_init (FIFO_Buff_t* P_Buff,SData* Buff_item,element_type Buff_length){
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
	return FIFO_no_error;
	if( !P_Buff->base || !P_Buff->head || !P_Buff->tail)
		return FIFO_Null ;

	}
Buffer_Status Buffer_valid (FIFO_Buff_t* P_Buff){
	//check if Queue is valid
	if( !P_Buff->base || !P_Buff->head || !P_Buff->tail)
	{
		return FIFO_Null ;
	}
	if (P_Buff->count == 0)
	{
		return FIFO_empty ;
	}
	//check if buffer is full
	if(P_Buff->count >= P_Buff->length){

		return FIFO_full ;
	}
	return FIFO_no_error ;
}
void FIFO_enqueue (FIFO_Buff_t* P_Buff){

	SData* NewStudent = (SData*)P_Buff->head;
	int i;
	char temp_text[50];
	//Add Student Details
	DPRINTF("\n Enter Student Roll Number: ");
	gets(temp_text);
	NewStudent->Roll =atoi(temp_text);
	if(Check_Roll(P_Buff,NewStudent->Roll)==1){
		DPRINTF("[ERROR] Roll Number is already taken before \n");
		return;
	}
	DPRINTF("\n Enter Student First Name: ");
	gets(NewStudent->FirstName);

	DPRINTF("\n Enter Student Last Name: ");
	gets(NewStudent->LastName);

	DPRINTF("\n Enter Student GPA: ");
	gets(temp_text);
	NewStudent->GPA = atof(temp_text);

	DPRINTF("\n Enter Student Courses ID of each course: ");
	for(i=0;i<5;i++){
		DPRINTF("\n Enter Student Courses ID %d:",i+1);
		gets(temp_text);
		NewStudent->Course_ID[i] = atoi(temp_text);
	}
	P_Buff->count++;
	P_Buff->head++;
	DPRINTF("[INFO] Student Details are added successfully \n");
	DPRINTF("--------------------------------------------\n");
	DPRINTF("[INFO] the total number of students is : %d\n",P_Buff->count);
	DPRINTF("[INFO] you can add up to %d students \n",P_Buff->length);
	DPRINTF("[INFO] you can add more about %d students \n",P_Buff->length - P_Buff->count);
	DPRINTF("--------------------------------------------\n");
}
void print_FIFO(SData* CurrentStudent){
	int i;
	printf("\n=======STUDENT PRINT=======\n");
	DPRINTF("\n Student Roll Number: %d",CurrentStudent->Roll);
	DPRINTF("\n Student First Name: %s",CurrentStudent->FirstName);
	DPRINTF("\n Student Last Name: %s",CurrentStudent->LastName);
	DPRINTF("\n Student GPA: %f",CurrentStudent->GPA);
	DPRINTF("\n Student Courses ID: ");
	for(i=0;i<5;i++){
		DPRINTF("\n Courses ID :%d",CurrentStudent->Course_ID[i]);
	}
	printf("\n==================\n");
}
