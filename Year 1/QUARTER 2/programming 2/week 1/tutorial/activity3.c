#include <stdio.h>

/// @brief Function to swap two floats 
/// @param pa pointer to the first float
/// @param pb pointer to the second float
void swap_floats(float *pa, float *pb) {
    // FIXME: this function is not implemented correctly
    float temp = *pa;
    *pa = *pb;
    *pb = temp;
}

int main(void) {
    float a = 3.14f, b = 2.71f;
    printf("Before swap: a = %.4f, b = %.4f\n", a, b);
    swap_floats(&a, &b);
    printf("After swap: a = %.4f, b = %.4f\n", a, b);
    return 0;
}
