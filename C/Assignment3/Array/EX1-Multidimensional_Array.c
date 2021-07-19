/*
 ============================================================================
 Name        : EX1-Multidimensional_Array.c
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
	float a[2][2] ;
	float b[2][2] ;
	printf ("Enter the elements of 1st matrix\n");
		printf ("Enter a11:");
			fflush(stdout);
			scanf("%f",&a[0][0]);
		printf ("Enter a12:");
			fflush(stdout);
			scanf("%f",&a[0][1]);
		printf ("Enter a21:");
				fflush(stdout);
				scanf("%f",&a[1][0]);
		printf ("Enter a22:");
				fflush(stdout);
				scanf("%f",&a[1][1]);
	printf ("Enter the elements of 2nd matrix \n");
		printf ("Enter b11:");
			fflush(stdout);
			scanf("%f",&b[0][0]);
		printf ("Enter b12:");
			fflush(stdout);
			scanf("%f",&b[0][1]);
		printf ("Enter b21:");
				fflush(stdout);
				scanf("%f",&b[1][0]);
		printf ("Enter b22:");
				fflush(stdout);
				scanf("%f",&b[1][1]);
		float c[2][2] = {a[0][0]+b[0][0], a[0][1]+b[0][1], a[1][0]+b[1][0], a[1][1]+b[1][1]};
	printf ("Sum of Matrix: \n %.1f \t %.1f \n %.1f \t %.1f",c[0][0], c[0][1], c[1][0], c[1][1]);
    return 0;
}
