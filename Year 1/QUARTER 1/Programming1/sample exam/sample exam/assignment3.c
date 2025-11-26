#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

void replace_character(char string[], char first, char second)
{

    for (int i = 0; string[i] != '\0'; i++)
    {
        if (tolower(string[i]) == tolower(first))
        {
            string[i] = second;
        }
    }
}

int main(void)
{
    char string[100];
    size_t size = sizeof(string) / sizeof(string[0]);
    printf("Enter a string: ");
    read_string(string, size);

    printf("Enter a character to replace: ");
    char first = read_char();

    printf("Enter a character to replace it with: ");
    char second = read_char();

    replace_character(string, first, second);

    printf("Result: %s\n", string);

    return 0;
}
