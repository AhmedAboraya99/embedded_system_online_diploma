/*
 ============================================================================
 Name        : EX2-Add_Two_Distances.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct SDistance {
	int feet ;
	float inch ;
}D1, D2, sum;
int main(void) {

printf("Enter information of 1st distance:\n");
printf("Enter feet:"); //get distance feet
fflush(stdout);
scanf("%d",&D1.feet);
printf("Enter inch:");//get distance inch
fflush(stdout);
scanf("%f",&D1.inch);

printf("\nEnter information of 2nd distance:\n");
printf("Enter feet:"); //get distance feet
fflush(stdout);
scanf("%d",&D2.feet);
printf("Enter inch:");//get distance inch
fflush(stdout);
scanf("%f",&D2.inch);

sum.feet = D1.feet + D2.feet;
  sum.inch = D1.inch + D2.inch;

  // convert inches to feet
  while (sum.inch >= 12.0) {
     sum.inch = sum.inch - 12.0;
     ++sum.feet;
  }
printf("\nSum of distances =%d'-%.1f\"",sum.feet,sum.inch);
}
