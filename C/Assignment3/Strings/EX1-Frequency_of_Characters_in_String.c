/*
 ============================================================================
 Name        : EX1-Frequency_of_Characters_in_String.c
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
	int i, c, sum = 0;
	printf ("Enter string:");
	char ch, str[100];
	fflush(stdout);
	gets(str);

	printf("\n Enter a character to find frequency:");
	fflush(stdout);
	scanf ("%c",&ch);
	c = strlen(str);
    for (i = 0; i < c; i++)
    	{
		if(str[i]==ch)
			sum += 1;
    	}
    printf(" frequency of %c = %d",ch,sum);

}
