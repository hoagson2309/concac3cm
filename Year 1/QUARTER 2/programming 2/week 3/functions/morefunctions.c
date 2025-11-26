#include "morefunctions.h"
#include "functions.h"

static void swap(void *a, void *b, size_t size) {
    char *ptr = (char*) a;
    char *ptr2 = (char*) b;
    for (size_t i = 0; i < size; i++) {
        char temp = ptr[i];
        ptr[i] = ptr2[i];
        ptr2[i] = temp;
    }
}

void shuffle(void *array, size_t count, size_t element_size) {
    char *ptr = array;
    for (size_t i = 0; i < count - 1; i++) {
        size_t j = random_int(i, count - 1);
        swap(ptr + i * element_size, ptr + j * element_size, element_size);
    }
}
