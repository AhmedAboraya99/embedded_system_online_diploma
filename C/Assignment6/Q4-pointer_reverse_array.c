/*
 ============================================================================
 Name        : Q4-pointer_reverse_array.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int num ;
	printf ("Input the number of elements to store in the array (max 15):");
	fflush(stdout);
	scanf("%d",&num);
	int arr[15];
	int reverse[15];
	int* p_num = arr;
	int i;
	for (i = 0 ; i < num ; i++)
		{
		printf("element - %d :",i+1);
		fflush(stdout);
		scanf("%d",(p_num+i));
		}

	printf("\nThe elements of array in reverse order are :\n");
	for (i = num-1 ; i >= 0 ; i--)
		{
		reverse[num-1-i] = *(p_num+i);
		printf("element - %d :%d\n",i+1,reverse[num-1-i]);
		}
}
