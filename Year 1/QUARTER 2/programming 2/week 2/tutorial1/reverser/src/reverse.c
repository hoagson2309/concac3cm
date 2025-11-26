#include <ctype.h>
#include "reverse.h"

char *skip_whitespace(char *str) {
    while (isspace(*str)) str++;
    return str;
}

char *end_of_word(char *str) {
    while (*str && !isspace(*str)) str++;
    return str;
}

void reverse(char *start, char *end) {
    end--;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverse_words(char *sentence) {
    char *start = skip_whitespace(sentence);
    while (*start != '\0') {
        char *end = end_of_word(start);
        reverse(start, end);
        start = skip_whitespace(end);
    }
}

