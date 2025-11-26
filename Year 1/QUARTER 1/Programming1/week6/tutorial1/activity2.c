#include <stdio.h>
#include "functions.h"
#include <ctype.h>

int main(void) {
    for(int i = 0; i < 128; i++){
        if(isprint(i)){
            printf("%3d: %c\n", i , i);
        }
        else{
            printf("%3d: not printable\n", i);
        }
    }
    return 0;
}