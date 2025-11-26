#include "split.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

string_t copy_string(const char *string);

void add_string(string_array_t *array, string_t string);


string_array_t split(const char *string) {
    (void) string;  // TODO: Remove this line

    // Create a new string array
    string_array_t words = {NULL, 0, 0};

    // TODO: Find the first word in the string and append it to the words array
    // TODO: Loop: find next word in the string and append it to the words array
    //             until no more words are found

    // return the words array
    return words;
}

const char *find_first_word(const char *string) {
    // skip spaces and find first word
    while (*string != '\0' && isspace(*string)) {   // skip spaces
        string++;
    }

    if (*string == '\0') return NULL;   // end of string, so no words
    else return string;                 // return pointer to first word
}

const char *find_next_word(const char *string) {
    // skip current word (if any) and find next word
    while (*string != '\0' && !isspace(*string)) {  // skip current word
        string++;
    }

    while (*string != '\0' && isspace(*string)) {   // skip spaces
        string++;
    }

    if (*string == '\0') return NULL;   // end of string, so no more words
    else return string;                 // return pointer to next word
}

void free_string_array(string_array_t *array) {
    for (size_t i = 0; i < array->count; i++) {
        free(array->strings[i]);
    }
    free(array->strings);
}
