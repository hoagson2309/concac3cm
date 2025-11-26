#include <stdio.h>      // for printf

int main(void) {
    int i = 99;            // initialization
    for (i = 99; i >= 1; i-=3)
    {
        printf("%d\n", i);
    }
    return 0;
}