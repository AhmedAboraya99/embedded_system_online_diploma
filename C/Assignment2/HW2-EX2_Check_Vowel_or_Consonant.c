/*
 ============================================================================
 Name        : HW2-EX2.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char a;
	printf("Enter an alphabet :");
	fflush(stdout);
	scanf("%c", &a);
	switch (a)
	{
	case 'a':
	case 'A':
	case 'e':
	case 'E':
	case 'i':
	case 'I':
	case 'O':
	case 'o':
	case 'U':
	case 'u':
		printf(" %c is a vowel ", a );
	break;
	default:
		printf(" %c is a consonant ", a );
	}
}
