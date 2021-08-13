/*
 ============================================================================
 Name        : Q1-handle_pointers.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int m = 29;
	int* ab;
	printf("Address of m : 0x%p\n", &m);
	printf("Value of m : %d\n\n", m);

	ab = &m;
	printf("now ab is assigned with the address of m\n");
	printf("Address of pointer ab : 0x%p\n", ab);
	printf("Content of pointer ab : %d\n\n", *ab);

	m = 34;
	printf("the value of m assigned to 34 now\n");
	printf("Address of pointer ab : 0x%p\n", ab);
	printf("Content of pointer ab : %d\n\n", *ab);

	*ab = 7;
	printf("The pointer variable ab is assigned with the value 7 now\n");
	printf("Address of m : 0x%p\n", &m);
	printf("Value of m : %d\n\n", m);

}
