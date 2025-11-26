#include "morefuns.h"
#include <stdlib.h>
#include <string.h>

int count_digits(int number, int digit) {
    int count = 0;
    if (number < 0) number = -number;
    while (number > 0) {
        if (number % 10 == digit) count++;
        number /= 10;
    }
    return count;
}

bool is_vowel(char c) {
    return strchr("aeiouAEIOU", c) != NULL;
}


int *read_integers(FILE *file, size_t *count) {
    int *integers = NULL;
    *count = 0;
    size_t capacity = 0;

    int value;
    while (fscanf(file, "%d", &value) == 1) {
        if (*count == capacity) {
            capacity = capacity == 0 ? 1 : capacity * 2;
            int *ptr = (int*) realloc(integers, capacity * sizeof(int));
            if (ptr == NULL) return integers;
            integers = ptr;
        }
        integers[*count] = value;
        ++*count;
    }

    return integers;
}

char **read_lines(FILE *file, size_t *count) {
    char **lines = NULL;
    *count = 0;
    size_t capacity = 0;

    char buffer[200];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (*count == capacity) {
            capacity = capacity == 0 ? 1 : capacity * 2;
            char **ptr = (char**) realloc(lines, capacity * sizeof(char*));
            if (ptr == NULL) return lines;
            lines = ptr;
        }
        char *newline = strrchr(buffer, '\n');
        if (newline != NULL) *newline = '\0';

        lines[*count] = (char*) malloc(strlen(buffer) + 1);
        if (lines[*count] == NULL) return lines;

        strcpy(lines[*count], buffer);

        ++*count;
    }

    return lines;
}

void free_strings(char *lines[], size_t count) {
    for (size_t i = 0; i < count; ++i) {
        free(lines[i]);
        lines[i] = NULL;
    }
}

void print_integers(const int array[], size_t count) {
    if (count > 0) printf("%d", array[0]);
    for (size_t i = 1; i < count; ++i) {
        printf(", %d", array[i]);
    }
    printf("\n");
}

void print_lines(char *lines[], size_t count) {
    for (size_t i = 0; i < count; ++i) {
        printf("%s\n", lines[i]);
    }
}



