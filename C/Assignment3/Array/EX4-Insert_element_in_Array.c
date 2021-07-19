/*
 ============================================================================
 Name        : EX4-Insert_element_in_Array.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n,i,ins,loc;
	printf ("Enter no of elements:");
	fflush(stdout);
	scanf ("%d",&n);
	int arr[n];
	for (i = 0; i < n; i++)
	{
	fflush(stdout); fflush(stdin);
	scanf ("%d",&arr[i]);
	}
	printf("\n Enter the element to be inserted:");
	fflush(stdout);
	scanf ("%d",&ins);

	printf("\nEnter the location:");
	fflush(stdout);
	scanf ("%d",&loc);

	for (i = n ; i >= loc; i--)
		arr[i] = arr[i-1];

	arr[loc - 1] = ins;

	for (i = 0; i <= n; i++)
			printf("%d ",arr[i]);
}
