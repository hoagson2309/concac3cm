#include <stdio.h>

int main(int argc, char *argv[]){
    //loop and print each argument
    for(int i = 0; i < argc; i++){
        printf("Argument %d: %s\n",i ,argv[i]);
    }
    return 0;
}
