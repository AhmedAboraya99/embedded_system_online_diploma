/*
 ============================================================================
 Name        : EX5-area_of_circle_macros.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#define pi 3.14285714286

int main(void) {
	int r;
	float area;
	printf("Enter the radius :");
	fflush(stdout);
	scanf("%d",&r);
	area = pi*r*r;
	printf("Area = %.2f",area);
}
