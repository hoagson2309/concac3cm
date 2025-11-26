#include <stdio.h>  // for printf
#include "functions.h"
#include <ctype.h>
#include <string.h>

int main(void) {
    char string[10][200];
    for(int i = 0; i < 10; i++){
        read_string(string[i], 200);
    }
    printf("You entered the following 10 sentences: \n");
    for(int i = 9; i >= 0; i--){
        printf("%s\n", string[i]);
    }
    return 0;
}