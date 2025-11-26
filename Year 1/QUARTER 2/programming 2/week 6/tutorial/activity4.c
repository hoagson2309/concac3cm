#include <stdio.h>
#include "functions.h"

// FIXME: make this function more generic so that it works with any type
void swap(void *a, void *b, size_t size) {
    // TODO: implement this function
    char temp;
    char *pa = (char *)a; //A char is always 1 byte in size, so casting to (char *) ensures the function works with the smallest memory unit.
    char *pb = (char *)b;

    for(size_t i = 0; i < size; i++){
        temp = pa[i];
        pa[i]= pb[i];
        pb[i] = temp;
    }
}

int main(void) {
    int int1 = 5, int2 = 10;
    double double1 = 3.14, double2 = 6.28;
    char char1 = 'a', char2 = 'b';
    const char *string1 = "hello", *string2 = "world";

    printf("Before swap:\n");
    printf("  int1 = %d, int2 = %d\n", int1, int2);
    printf("  double1 = %f, double2 = %f\n", double1, double2);
    printf("  char1 = %c, char2 = %c\n", char1, char2);
    printf("  string1 = \"%s\", string2 = \"%s\"\n", string1, string2);

    swap(&int1, &int2, sizeof(int));
    swap(&double1, &double2, sizeof(double));
    swap(&char1, &char2, sizeof(char)); //sizeof(char) is for swapping single characters(1 byte). 
    swap(&string1, &string2, sizeof(char *)); //sizeof(char *) is for swapping pointers to characters (or strings in this case)(4 bytes, 8 bytes). 

    
    printf("After swap:\n");
    printf("  int1 = %d, int2 = %d\n", int1, int2);
    printf("  double1 = %f, double2 = %f\n", double1, double2);
    printf("  char1 = %c, char2 = %c\n", char1, char2);
    printf("  string1 = \"%s\", string2 = \"%s\"\n", string1, string2);
}
