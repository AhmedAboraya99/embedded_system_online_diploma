/*
 ============================================================================
 Name        : HW2-EX39.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float a, b, c;
	printf("Enter three numbers :");
	fflush(stdout);
	scanf("%f", &a);
	fflush(stdout); fflush(stdin);
	scanf("%f", &b);
	fflush(stdout); fflush(stdin);
		scanf("%f", &c);
	if (a > b){
		if(a > c)
			{printf(" largest number = %f ",a) ;}
		else
			{printf(" largest number = %f ",c) ;}
	}
	else if(a<b && b>c)
	{ printf(" largest number = %f ",b) ;}
}
