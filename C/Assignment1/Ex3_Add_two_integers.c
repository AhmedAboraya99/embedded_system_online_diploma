/*
 ============================================================================
 Name        : Question3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int a ; int b ; int sum ;
	printf("Enter two integers :");
	fflush(stdout);
	scanf("%d \n", &a );
	scanf("%d", &b );
	sum = a + b ;
	printf("Sum : %d ", sum );
}
