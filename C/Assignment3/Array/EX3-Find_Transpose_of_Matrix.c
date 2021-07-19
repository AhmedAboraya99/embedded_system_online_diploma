/*
 ============================================================================
 Name        : EX3-Find_Transpose_of_Matrix.c
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
	int r,c,i,j;
	printf ("Enter the row and column of matrix: \n");
	fflush(stdout);
	scanf("%d %d",&r,&c);
	int a[r][c] , b[c][r] ;
	printf ("Enter elements of matrix\n");
	for(i=1;i<=r;i++)
	{
		for(j=1;j<=c;j++)
		{
			printf ("Enter element a%d%d:",i,j);
				fflush(stdout); fflush(stdin);
				scanf("%d",&a[i][j]);
		}
	}
	printf ("Entered matrix:\n");
	for(i=1;i<=r;i++)
		{
			for(j=1;j<=c;j++)
			{
				printf("%d\t",a[i][j]);
			}
			printf("\r\n");
		}
		printf ("Transpose of matrix:\n");
		for(i=1;i<=c;i++)
		{
			for(j=1;j<=r;j++)
			{
				b[i][j] = a[j][i];
			}
				}
		for(i=1;i<=c;i++)
		{
			for(j=1;j<=r;j++)
			{
				printf("%d\t",b[i][j]);
			}
			printf("\r\n");
		}
    return 0;
}
