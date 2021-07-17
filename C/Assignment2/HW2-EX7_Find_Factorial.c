/*
 ============================================================================
 Name        : HW2-EX7.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n, i, factor;
		printf("Enter an integer :");
		fflush(stdout);fflush(stdin);
		scanf("%d", &n);
		factor = n;
		if (n < 0 ){
		printf("Error!!! factorial of negative number doesn't exist. ") ;
		}
		else if (n == 0) { factor = 1 ;
		printf(" factorial = %d  ", factor) ;
		}
		else
		{
		for ( i =2 ; i <= n; i++){
				fflush(stdout);fflush(stdin);
				factor =factor * i;
					}
		printf(" factorial = %d  ", factor) ;
		}
}
