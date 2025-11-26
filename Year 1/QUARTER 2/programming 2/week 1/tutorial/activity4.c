#include <stdio.h>
#include "functions.h"

/// @brief Returns a pointer to the maximum of two integers
/// @param pa pointer to the first integer
/// @param pb pointer to the second integer
/// @return pointer to the maximum of the two integers
int *ptr_to_max(int *pa, int *pb);
int *ptr_to_max(int *pa, int *pb){
    if(*pa >= *pb){
        return pa;
    }
    else{
        return pb;
    }
}

int main(void) {
    int first, second;
    printf("This program will increment the highest of two integers.\n");
    printf("Enter the first integer: ");
    first = read_int();
    printf("Enter the second integer: ");
    second = read_int();

    int *p_max = ptr_to_max(&first, &second);
    printf("The highest integer is %d\n", *p_max);
    (*p_max)++;
    printf("After incrementing, the highest integer is %d\n", *p_max);

    return 0;
}