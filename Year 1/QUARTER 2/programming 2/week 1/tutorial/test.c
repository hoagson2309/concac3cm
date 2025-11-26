#include <stdio.h>

int main(void) {
    // FIXME: change the contents of the array `obfuscated_text` in such a way that the program prints
    //        the exact string that was given to you by your lab teacher.

    const char *target_string = "Ignorance is bliss";  // change this to the string you were given (on paper)
    // you may want to write some code here to print the string as an array of integers, rather
    int *ptr = (int*)target_string;
    printf("%d\n", ptr);
return 0;
}



