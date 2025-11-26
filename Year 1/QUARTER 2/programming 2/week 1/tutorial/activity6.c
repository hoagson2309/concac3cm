#include <stdio.h>

/// @brief Prints a string, as well as its address
/// @param str the string to print
void print_string(const char *str) {
    // FIXME: print the address of the first character in the string
    //        and the characters in the string.
    // Example output: "0x7ffeefbff6e0 Hello, world!"
    
        printf("%p %s\n", (void*)str, str);
    
}
int main(void) {
    const char *str = "Hello, world!";
    char arr[] = "Hello, world!";
    print_string(str);
    print_string(arr);
    return 0;
}