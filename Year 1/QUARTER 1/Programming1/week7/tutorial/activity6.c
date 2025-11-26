#include <stdio.h>
#include "functions.h"
#include "week7.h"
/// @brief Bubbles the longest string to the end of the array.
/// @param strings the array of strings
/// @param size the number of strings in the array
/// @return The number of swaps made
int bubble_longest_string(char strings[][100], size_t size){
    int swaps = 0;
    for(size_t i = 0; i < size - 1; i++){
        if(strlen(strings[i]) > strlen(strings[i + 1]) ){
            swap_strings(strings[i + 1], strings[i]);
            swaps++;
        }
    }
    return swaps;
}



int main(void) {
    char sentences[][100] = {
        "The quick brown fox jumps over the lazy dog.",
        "The five boxing wizards jump quickly.",
        "Pack my box with five dozen liquor jugs.",
        "How vexingly quick daft zebras jump!",
        "Mary had a little lamb.",
        "How much wood would a woodchuck chuck if a woodchuck could chuck wood?",
        "Bright vixens jump; dozy fowl quack.",
        "The quick onyx goblin jumps over the lazy dwarf.",
        "Peter Piper picked a peck of pickled peppers.",
        "She sells seashells by the seashore."
    };

    size_t size = sizeof(sentences) / sizeof(sentences[0]);

    // print the sentences
    printf("The sentences are:\n");
    for (size_t i = 0; i < size; i++) {
        printf("%s\n", sentences[i]);
    }

    bubble_longest_string(sentences, size);

    // print all sentences
    printf("\nAfter bubbling, this is the order of the sentences:\n");
    for (size_t i = 0; i < size; i++) {
        printf("%s\n", sentences[i]);
    }

    // print longest sentence (should be the last element)
    printf("\nThe longest sentence should be the last one:\n %s\n", sentences[size - 1]);
}
