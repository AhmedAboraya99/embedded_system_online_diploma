/*
 ============================================================================
 Name        : EX2-Factorial_of_Number.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int fact (unsigned int x){

	if (x>0)
		return x*fact(x-1);
	else
	        return 1;
}
int main(void) {
	 unsigned int num ;
		printf("Enter a positive integer: ") ;
		fflush(stdout);fflush(stdin);
		scanf("%d",&num);
		printf("factorial of %d = %d", num,fact (num)) ;
}
