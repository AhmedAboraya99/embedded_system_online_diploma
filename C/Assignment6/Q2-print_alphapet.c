/*
 ============================================================================
 Name        : Q2-print_alphapet.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char alpha[26] ={'A','B','C', 'D', 'E', 'F', 'G', 'H', 'I', 'J','K', 'L', 'M','N',
								'O', 'P', 'Q','R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	char* p_alpha;
	p_alpha = alpha ;
	printf("The alphabets are :\n");
	int i = 0;
	while(i<=25)
	{
		printf("%c  ",*p_alpha++);
		i++;
	}


}
