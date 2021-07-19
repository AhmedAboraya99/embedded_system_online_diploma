/*
 ============================================================================
 Name        : EX3-Reverse.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {

	int i,c,temp ;
	printf ("Enter the string:");
	char str[100];
	fflush(stdout);
	gets(str);
	c = strlen(str)-1;
	for (i = 0 ; i < c ; i++)
		{
			temp = str[i];
			str[i] = str[c] ;
			str[c] = temp ;
			c--;
		}
	printf(" reverse string is :%s",str);
}
