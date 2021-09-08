#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <stdio.h>
#include <stdlib.h>
#define DPRINTF(...) {fflush(stdin);fflush(stdout);\
						printf(__VA_ARGS__);\
						fflush(stdin);fflush(stdout);\
					 }

struct Sdata{
	int ID;
	char name[50];
	float height;
};
struct SStudent{
	struct Sdata Student_Data;
	struct SStudent* pNextStudent;
};

//APIs
void Fill_SData(struct SStudent* NewStudent);
void AddStudent();
int Delete_Student();
void DeleteAll();
void View_Students();
void GetNth(int index);
int getCount();
void get_end_Nth(int index);
void getMiddle();
void getReverse();

#endif
