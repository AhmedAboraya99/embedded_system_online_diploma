/*
 ============================================================================
 Name        : HW2.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 ============================================================================
 Name        : HW2-EX5.c
 Author      : Ahmed Aboraya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(void) {
	char a ;

	printf("Enter a character :");
	fflush(stdout);fflush(stdin);
	scanf("%c", &a);

	 if ((a >= 'a') && (a <= 'z') || (a>='A') && (a<='Z')){
		printf(" %c is an alphabet ", a) ;

			}
	 else  {
				printf(" %c is not an alphabet ", a);
					}

}
