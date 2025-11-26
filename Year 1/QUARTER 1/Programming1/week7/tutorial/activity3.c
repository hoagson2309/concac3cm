#include <stdio.h>
#include "functions.h"
#include "week7.h"

int main(void) {
    int unique_nums[] = {2, 3, 5, 7, 11, 13, 17, 19};
    size_t size = sizeof(unique_nums) / sizeof(unique_nums[0]);

    int duplicate_nums[] = {2, 3, 5, 7, 11, 13, 17, 19, 2, 3, 5, 7, 11, 13, 17, 19};
    size_t duplicate_size = sizeof(duplicate_nums) / sizeof(duplicate_nums[0]);
    
    if (has_duplicates(unique_nums, size)) {
        printf("unique_nums contains duplicates: incorrect!\n");
    } else {
        printf("unique_nums contains duplicates: correct\n");
    }

    if (has_duplicates(duplicate_nums, duplicate_size)) {
        printf("duplicate_nums contains duplicates: correct\n");
    } else {
        printf("duplicate_nums contains duplicates: incorrect!\n");
    }
}
