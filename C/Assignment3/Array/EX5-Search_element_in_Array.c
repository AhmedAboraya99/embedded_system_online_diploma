/*
 ============================================================================
 Name        : EX5-Search_element_in_Array.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n,element,i;
	printf ("Enter no of elements:");
	fflush(stdout);
	scanf ("%d",&n);
	int arr[n];
	for (i = 0; i < n; i++)
		{
		fflush(stdout); fflush(stdin);
		scanf ("%d",&arr[i]);
		}
	printf("\n Enter the element to be searched:");
	fflush(stdout);
	scanf ("%d",&element);

    i = 0 ;
	while( i<n && element != arr[i] ){
		i++;
	}
		if(i < n)
			printf(" Number found at location = %d",i+1);
		else
			printf(" Number not found ");

}
