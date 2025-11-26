#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void encrypt(FILE *input, FILE *output, int shift);
int parse_shift(int argc, char *argv[], int *shift);
void print_usage(void);

int main(int argc, char *argv[]){
    if(argc < 2){
        print_usage();
        return 1;
    }

    char *input_filename = argv[1];
    FILE *input = fopen(input_filename, "r");
    if(input == NULL){
        fprintf(stderr, "Error: Could not open input file \"%s\".\n", input_filename);
        return 1;
    }

    FILE *output = stdout; //default to standard output
    int shift = 1; //default shift value
    if(parse_shift(argc, argv, &shift)){
        output = fopen(argv[argc - 1], "w");
        if(output == NULL){
            fprintf(stderr, "Error: Could not open output file.\n");
            fclose(input);
            return 1;
        }
    }

    encrypt(input, output, shift);
    fclose(input);
    if(output != stdout){
        fclose(output);
    }
    return 0;

}

void encrypt(FILE *input, FILE *output, int shift){
    int ch;
    while((ch = fgetc(input)) != EOF){
        if(isalpha(ch)){
            char base = (islower(ch)) ? 'a' : 'A';
            ch = (ch - base + shift) % 26 + base;
        }
        fprintf(output, "%c", ch); 
    }
}

int parse_shift(int argc, char *argv[], int *shift){
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0){
            if(i + 1 < argc){
                return 1; //output file specified
            } else {
                fprintf(stderr, "Error: Missing output filename.\n");
                print_usage();
                return 0;
            }
        }
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--shift") == 0) {
            if (i + 1 < argc) {
                *shift = atoi(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "Error: Missing shift value.\n");
                print_usage();
                return 0;
            }
        }
    }
    return 0;  // No output file specified, default is stdout
}

void print_usage(void) {
    printf("Usage: ./encrypt <input_file> [-o <output_file>] [-s <shift>]\n");
}


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