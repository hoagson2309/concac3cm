#include <stdio.h>
#include <string.h>

int main(void) {
    // FIXME: change the contents of the array `obfuscated_text` in such a way that the program prints
    //        the exact string that was given to you by your lab teacher.

    const char *target_string = "Resistance is futile";  // change this to the string you were given (on paper)
    // you may want to write some code here to print the string as an array of integers, rather
    int *ptr = (int*)target_string;
    for(size_t i = 0; i < 7; i++){
        printf("%d ", *(ptr + i));
    }
    printf("\n");
    // than guessing the values to put in the array obfuscated_text below

    // change the contents of the array
    const int obfuscated_text[] = {1769170258, 1851880563, 1763730787, 1969627251, 1701603700, 543433984, 1986610944 };


    // don't make any changes to the following code
    const char *p = (const char *)&obfuscated_text;
    printf("%s\n", p);
    printf("Given string: %s\n", target_string);

    if (strcmp(p, target_string) == 0) {
        printf("You have successfully completed the task!\n");
    } else {
        printf("The task is not completed yet.\n");
    }

    return 0;
}