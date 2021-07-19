/*
 ============================================================================
 Name        : EX2-Calculate_Average_Using_Arrays.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i;
	float sum;
	printf ("Enter the number of data:");
	fflush(stdout);
	scanf ("%d",&n);
	float arr[n];
	for (i = 1; i <= n; i++)
	{
		printf("%d. Enter number:",i);
		fflush(stdout);
		fflush(stdin);
		scanf ("%f",&arr[i]);
		sum += arr[i];
	}
	printf("Average = %.2f", sum/n);
}
