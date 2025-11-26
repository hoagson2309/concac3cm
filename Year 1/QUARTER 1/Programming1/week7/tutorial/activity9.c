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

    // find the sentence with the fewest vowels
    size_t index_of_fewest_vowels = find_string_with_fewest_vowels(sentences, size);

    // print the sentence with the fewest vowels
    printf("\nThe sentence with the fewest vowels is:\n  %s\n", sentences[index_of_fewest_vowels]);
    printf("It contains %zu vowels.\n", count_vowels(sentences[index_of_fewest_vowels]));
}
