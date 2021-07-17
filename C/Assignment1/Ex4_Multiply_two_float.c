/*
 ============================================================================
 Name        : Question4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float a ; float b ; float product ;
	printf("Enter two numbers :");
	fflush(stdout);
	scanf("%f \n", &a );
	scanf("%f", &b );
	product = a * b ;
	printf("Product : %f ", product );
}
