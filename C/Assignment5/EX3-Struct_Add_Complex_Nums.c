/*
 ============================================================================
 Name        : EX3-Struct_Add_Complex_Nums.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct SComplex {
	float real ;
	float img ;
}C1, C2, result;
int main(void) {

printf("for 1st complex number:\n");
printf("Enter real and imaginary respectively:");
fflush(stdout);
scanf("%f",&C1.real);//get real part
fflush(stdout);
scanf("%f",&C1.img);//get imaginary part

printf("\nfor 2nd complex number:\n");
printf("Enter real and imaginary respectively:");
fflush(stdout);
scanf("%f",&C2.real);//get real part
fflush(stdout);
scanf("%f",&C2.img);//get imaginary part

result.real = C1.real + C2.real;
result.img = C1.img + C2.img;

printf("\nSum =%.1f+%.1fi",result.real,result.img);
}
