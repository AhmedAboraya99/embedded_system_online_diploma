/*
 ============================================================================
 Name        : HW2-Ex3.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float a ;
	printf("Enter a number :");
	fflush(stdout);
	scanf("%f", &a);
	if (a == 0){
		printf(" You entered zero ") ;
	}
	else if(a > 0){
		printf(" %f is positive ", a );
	}
	else {
		printf(" %f is negative ", a );
	}
}
