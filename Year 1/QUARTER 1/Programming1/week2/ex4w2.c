#include <stdio.h>
#include "functions.h"

	int main(void){
	printf("Please enter 2 digits number: ");
	int num = read_int();
	if (num < 10 || num > 99){
		printf(" IT'S NOT A RIGHT 2 DIGITS NUMBER, PLEASE TYPE AGAIN! ");
	}
	else{
		int digit1 = num / 10;
		int digit2 = num % 10;
		printf("Digits of %d are %d and %d.\n", num, digit1, digit2);
	}
	return 0;
	}
