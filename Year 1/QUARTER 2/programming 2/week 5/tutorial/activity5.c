#include <stdio.h>
#include <stdbool.h>
#include "functions.h"
#include "stringfun.h"
#include <string.h>

int main(void) {
    char buffer[100];
    printf("Enter the name of the file: ");
    read_string(buffer, sizeof(buffer));

    FILE *file = fopen(buffer, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file %s.\n", buffer);
        return 1;
    }

    // FIXME: this program reads one word at a time, but it should read one line at a time
    //        Fix the program so that it reads one line at a time, using fgets
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *ptr = strchr(buffer, '\n');
        if(ptr != NULL) *ptr = '\0';
        
        printf("%s -> ", buffer);
        reverse(buffer);
        printf("%s (palindrome: ", buffer);
        if (is_palindrome(buffer)) {
            printf("yes)\n");
        } else {
            printf("no)\n");
        }
    }

}
