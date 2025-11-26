#include "stringfun.h"
#include <string.h>
#include <ctype.h>

void reverse(char *string) {
    char *last = string + strlen(string) - 1;
    while (string < last) {
        char temp = *string;
        *string = *last;
        *last = temp;
        string++;
        last--;
    }
}

bool is_palindrome(const char *string) {
    const char *last = string + strlen(string) - 1;
    while (last > string && !isalpha(*last)) last--;
    while (string < last && !isalpha(*string)) string++;

    while (string < last) {
        if (tolower(*string) != tolower(*last)) return false;
        string++;
        last--;
        while (last > string && !isalpha(*last)) last--;
        while (string < last && !isalpha(*string)) string++;
    }
    return true;
}
