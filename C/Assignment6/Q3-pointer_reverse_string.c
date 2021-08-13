/*
 ============================================================================
 Name        : Q3-pointer_reverse_string.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

int main(void) {

	int size ;
	printf ("Input the string:");
	char str[100];
	char reverse[100];
	char* p_ch = str;
	fflush(stdout);
	scanf("%s",str);
	size = strlen(str)-1;

	int i;
	for (i = size ; i >= 0 ; i--)
		{
		reverse[size-i] = *(p_ch+i);
		}
	reverse[size+1]='\0';
	printf("Reverse of string is %s",reverse);
}

