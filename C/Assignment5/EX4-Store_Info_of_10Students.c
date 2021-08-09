/*
 ============================================================================
 Name        : EX4-Store_Info_of_10Students.c
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
struct SStudent St[10];
int i ;
//get information from students
printf("Enter information of students:\n");
for(i=0;i<10;i++){
	printf("\nfor roll number %d\n",i+1);
	printf("Enter name:"); //get student name
	fflush(stdout);
	scanf("%s",St[i].name);

	printf("Enter marks:");//get student marks
	fflush(stdout);
	scanf("%f",&St[i].marks);
}

//display information of students
printf("\nDisplaying Information of students:\n");
for(i=0;i<10;i++){
	printf("\nfor roll number %d:\n",i+1);
	printf("name: %s\n",St[i].name);
	printf("Marks: %.2f\n",St[i].marks);
}
}
