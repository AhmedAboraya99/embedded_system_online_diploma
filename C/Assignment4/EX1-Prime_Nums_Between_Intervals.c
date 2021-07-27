/*
 ============================================================================
 Name        : EX1-Prime_Nums_Between_Intervals.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void prime (int small , int big)
{
	int x = small ;
	x=small+1;
	int i = 0, n, flag ;

	printf("Prime Numbers between %d and %d are :",small,big);
	while(small<x && x<big)
		{
			for(n= 2 ; n<=x/2 ; n++ )
			{
			flag = 0 ; // initialization & reset
			if(x%n == 0 )
				flag = 1 ; //flag of non-prime numbers
			}
			if(flag == 0)
			printf("%d ",x);
			i++;
			x++;
		}
}
int main(void) {
   int small , big;
	printf("Enter two numbers ( intervals ): ") ;
	fflush(stdout);
	scanf("%d",&small);
	fflush(stdout);fflush(stdin);
	scanf("%d",&big);
	prime (small,big) ;
}
