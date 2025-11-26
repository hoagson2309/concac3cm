#include <stdio.h>
#include "functions.h"
#include "stringfun.h"

int main(void) {
    char buffer[100];
        // TODO: this program never stops.
        const char *filename = "../palindromes.txt";

        FILE *file = fopen(filename, "w");
        if(file == NULL){
            printf("Failed to open file\n");
            return 1;
        }
    //       Fix the program so that it stops when the end-of-file is reached on stdin
    while (1) {
        printf("Enter a word: ");
        if(fscanf(stdin, "%99s", buffer) != 1){
            if(feof(stdin)){
                printf("End of file detected. Exiting program\n");
                return 1;
            } else {
                printf("Error reading input. Exiting program\n");
                return 1;
            }   
        } 
        reverse(buffer);
        printf("Reversed: %s (palindrome: ", buffer);
        if (is_palindrome(buffer)) {
            printf("yes)\n");
        } else {
            printf("no)\n");
        }
    }
}
