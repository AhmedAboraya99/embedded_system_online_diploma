/*
 ============================================================================
 Name        : EX2-Find_Length_of_String.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int i ,length = 0;
	printf ("Enter string:");
	char str[100];
	fflush(stdout);
	gets(str);

	for (i = 0; str[i]!= 0 ; i++)
		{
			length += 1;
		}
	printf(" length of string = %d",length);
}
