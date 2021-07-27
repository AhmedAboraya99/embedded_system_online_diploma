/*
 ============================================================================
 Name        : EX4-Calculate_Power_of_Num.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int result = 1;
int expo(int b,int p){
	if(p>0){
		result *= b;
		p--;
		expo(b,p);
		return result;
	}
	else
	return result;
}
int main(void) {
 int base ,power;
	printf("Enter base number: ") ;
	fflush(stdout);fflush(stdin);
	scanf("%d",&base);
	printf("Enter power number: ") ;
	fflush(stdout);fflush(stdin);
	scanf("%d",&power);
	printf("%d^%d = %d",base,power,expo(base,power));
}

