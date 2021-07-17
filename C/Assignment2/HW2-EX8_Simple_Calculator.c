/*
 ============================================================================
 Name        : HW2-EX8.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char opt; float num1, num2, result = 0.0;
	printf("Enter operator either + or - or * or divide :");
			fflush(stdout);fflush(stdin);
			scanf("%c", &opt);
	printf("Enter two operands :");
				fflush(stdout);fflush(stdin);
				scanf("%f %f", &num1,&num2);
	switch (opt){
		case'+':
			result = num1 + num2;
			printf("%.1f + %.1f = %.1f",num1,num2,result );
			break;
		case'-':
			result = num1 - num2;
			printf("%.1f - %.1f = %.1f",num1,num2,result );
			break;
		case'*':
			result = num1 * num2;
			printf("%.1f * %.1f = %.1f",num1,num2,result );
			break;
		case'/':
			result = num1 / num2;
			printf("%.1f / %.1f = %.1f",num1,num2,result );
			break;
	}
}
