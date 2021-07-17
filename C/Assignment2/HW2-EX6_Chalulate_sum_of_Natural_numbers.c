/*
 ============================================================================
 Name        : HW2.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n, i, sum = 0;
	printf("Enter an integer :");
		fflush(stdout);fflush(stdin);
		scanf("%d", &n);
	for ( i = 1; i<= n; i++){
			fflush(stdout);fflush(stdin);

			sum += i;
				}

	printf(" sum = %d  ", sum) ;
}
