# Assignments - Week 6

You must complete two out of the three assignments, but you are encouraged to complete all three.
Below you will find, per assignment, instructions on what you need to include in this markdown file.

## Assignment 1 - Simple file encryption

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
// TODO: Include the contents of your `main.c` file here
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int parse_command_line(int argc, char *argv[], char **output, char **input, int *shift) {
    for (int i = 0; i < argc; i++) {
        if ((strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)) {
            if (i + 1 < argc) {
                *output = malloc(strlen(argv[i + 1]) + 1);
                if (*output == NULL) {
                    printf("Memory allocation failed for output file.\n");
                    return 1;
                }
                strcpy(*output, argv[i + 1]);
                i++;
            } else {
                printf("Can't find value for --output. Out!\n");
                return 1;
            }
        } else if ((strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--shift") == 0)) {
            if (i + 1 < argc) {
                if (sscanf(argv[i + 1], "%d", shift) == 1) {
                    i++;
                } else {
                    printf("Invalid value for shift. Out!\n");
                    return 1;
                }
            } else {
                printf("Can't find value for --shift. Out!\n");
                return 1;
            }
        } else {
            *input = malloc(strlen(argv[i]) + 1);
            if (*input == NULL) {
                printf("Memory allocation failed for input file.\n");
                return 1;
            }
            strcpy(*input, argv[i]);
        }
    }
    printf("Input file: %s \nOutput file: %s \n", *input, *output);
    return 0;
}

void shift_string(char *string, int shift) {
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (isalpha(string[i])) {
            int wrap = islower(string[i]) ? 'a' : 'A';
            string[i] = wrap + (string[i] - wrap + shift) % 26;
        }
    }
}

int main(int argc, char *argv[]) {
    int shift = 1;
    char *output = NULL;
    char *input = NULL;
    
    int status = parse_command_line(argc, argv, &output, &input, &shift);
    if (status) return status;

    FILE *in_file = fopen(input, "r");
    if (in_file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", input);
        free(output);
        free(input);
        return 1;
    }

    FILE *out_file = fopen(output, "w");
    if (out_file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", output);
        free(output);
        free(input);
        fclose(in_file);
        return 1;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), in_file) != NULL) {
        shift_string(buffer, shift);
        fprintf(out_file, "%s", buffer);
    }

    fclose(out_file);
    fclose(in_file);

    free(output);
    free(input);

    return 0; // 17 semicolons ;)
}
```

## Assignment 2 - File search

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
```

