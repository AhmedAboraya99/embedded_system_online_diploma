/*
 ============================================================================
 Name        : Question5.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char ch; int a;
	printf("Enter a character:");
		fflush(stdout);
		scanf("%c", &ch);
		a = ch;
		printf("ASCII value of %c = %d ", ch, a);
	}

