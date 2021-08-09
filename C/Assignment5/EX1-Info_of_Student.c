/*
 ============================================================================
 Name        : EX1-Info_of_Student.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

struct SStudent {
	char name[50];
	int roll ;
	float marks ;
};
int main(void) {
struct SStudent S1;
//get information from student
printf("Enter information of students:\n\n");
printf("Enter name:"); //get student name
fflush(stdout);
scanf("%s",S1.name);
printf("Enter roll number:");//get student roll number
fflush(stdout);
scanf("%d",&S1.roll);
printf("Enter marks:");//get student marks
fflush(stdout);
scanf("%f",&S1.marks);

printf("\nDisplaying Information:\n");

printf("name: %s\n",S1.name);
printf("Roll : %d\n",S1.roll);
printf("Marks: %.2f\n",S1.marks);
}
