#include <stdio.h>

int main(void) {
    int integer = 42;
    int *p_integer = &integer;

    float pi = 3.14159265359f;
    float *p_pi = &pi;

    char letter = 'A';
    char *p_letter = &letter;

    printf("Value of integer: %d\n", integer);
    printf("The memory address of the integer: %p\n", p_integer);
    printf("The memory address of the p_integer: %p\n", &p_integer);

    printf("Value of pi: %.8f\n", pi);
    printf("The memory address of the pi: %p\n", p_pi);
    printf("The memory address of the p_pi: %p\n", &p_pi);

   printf("Value of letter: %c\n", letter);
   printf("The memory address of the letter: %p\n", p_letter);
   printf("The memory address of the p_letter: %p\n", &p_letter);
    return 0;
}