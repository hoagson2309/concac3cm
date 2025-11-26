#include <stdio.h>
#include <stdbool.h>
#include "stringfun.h"

int main(void) {
    char buffer[100];
    printf("Enter a line of text: ");
    
    // read a string until the next newline or space
    while (fscanf(stdin, " %99[^,]", buffer) == 1) {
        printf("%s\n", buffer);
            
        int ch = getchar();// to consume all of the ',' to ch
        if(ch != ','){
            break;
        }
    }
    return 0;
}
  