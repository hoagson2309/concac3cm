#include <stdio.h>

int main(void) {
    int array[] = {1, 2, 3, 4, 5};
    int i;
    int *p = array;
    for (i = 0; i < 5; i++) {
        // FIXME: the & operator is used to obtain the address
        //        instead, use pointer arithmetic - use of & is not allowed!
        printf("Address of arr[%d]: %p\n", i, (void*)p);
        p++;
    }
  return 0;
}