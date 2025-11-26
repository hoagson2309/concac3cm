#include <stdio.h>
#include "functions.h"
#include "week7.h"

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

    // sort the sentences
    int swaps = bubble_sort_strings(sentences, size);

    // print all sentences
    printf("\nAfter sorting by length, this is the order of the sentences:\n");
    for (size_t i = 0; i < size; i++) {
        printf("%s\n", sentences[i]);
    }

    printf("\n%d swaps were made while sorting.\n", swaps);
}
