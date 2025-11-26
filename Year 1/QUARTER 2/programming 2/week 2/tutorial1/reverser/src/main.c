#include <stdio.h>
#include "functions.h"
#include "reverse.h"

int main(void) {
    char sentence[200];
    printf("Enter a sentence, and I will reverse all \"words\" in it!\n");
    printf("Your sentence?> ");
    read_string(sentence, sizeof(sentence));
    reverse_words(sentence);
    printf("Reversed: \"%s\"\n", sentence);
    return 0;
}

