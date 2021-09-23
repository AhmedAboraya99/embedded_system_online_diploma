#ifndef _TYPE_H_
#define _TYPE_H_

#include<stdint.h>
#include <stdio.h>
#include <stdlib.h>


#define DPRINTF(...) {fflush(stdin);fflush(stdout);\
					printf(__VA_ARGS__);\
					fflush(stdin);fflush(stdout);\
				 }

//select element type
#define element_type uint32_t
#define FIFO_Buff_length 50


//Define return data types define. status of Buffer
typedef enum{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_Null,
}Buffer_Status ;

typedef struct{
	int Roll;
	char FirstName[50];
	char LastName[50];
	float GPA;
	int Course_ID[10];
}SData;

//Define some pointers and variables defined and changed at each address in buffer
typedef struct {
	uint32_t length;
	SData* base;
	SData* head;
	SData* tail;
	uint32_t count;
}FIFO_Buff_t;


#endif
