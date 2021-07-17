/*
 ============================================================================
 Name        : Question7.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float a ; float b  ;
		printf("Enter value of a :");
		fflush(stdout);
		scanf("%f", &a);
		printf("Enter value of b :");
		fflush(stdout);fflush(stdin);
		scanf("%f", &b);
		a=a+b;
		b=a-b;
		a=a-b;
		printf("after swapping, value of a : %f \n", a );
		printf("after swapping, value of b : %f ", b );
	}
