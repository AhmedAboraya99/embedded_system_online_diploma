/*
 ============================================================================
 Name        : EX3-Reverse_Sentence.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int i ;
void reverse (char text[] ){
		if(text[i]!='\0'){
		i++;
		printf("%c",text[strlen(text)-i]);
		reverse(text);
	}
}
int main(void) {
		char text[100];
		printf("Enter a sentence : ") ;
		fflush(stdout);fflush(stdin);
		gets(text);
		reverse(text) ;
}
