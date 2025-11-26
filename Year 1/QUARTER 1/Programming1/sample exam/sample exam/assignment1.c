#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include <stdbool.h>



int main(void) {
    // Write your program for assignment 1 here
    bool print_first = false;
    int sum = 0;
    printf("Enter a number: ");
    int ans = read_int();
    printf("Divisors: ");
    for(int i = 1; i <= ans; i++){
        if(ans % i == 0){
            
            if (print_first) printf(", ");
            print_first = true;
            printf("%d", i);
            sum += i;
        }
    }
    printf("\nSum of divisors: %d\n", sum);
    return 0;
}
