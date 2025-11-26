#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>


size_t find_positional_arguments(char *argv[], char *positional_arguments[]);

/// @brief Reads a string from a file and removes the newline character.
/// @param file The file to read from.
/// @param buffer The buffer to store the string in.
/// @param size The size of the buffer.
void read_string(FILE* file, char buffer[], size_t size);

/// @brief Reads a yes or no response from the user.
/// @param prompt The prompt to display to the user.
char read_yes_no(const char *prompt);

/// @brief Counts the number of uppercase and lowercase characters in a string.
/// @param buffer The string to count the characters in.
/// @param upper A pointer to store the number of uppercase characters.
/// @param lower A pointer to store the number of lowercase characters.
void count_upper_lower(const char *buffer, int *upper, int *lower);

int main(int argc, char *argv[]) {
    if(argc < 2){
        fprintf(stderr, "Usage: %s [-l|--lower] [-u|--upper] <filename>\n", argv[0]);
        return 1;
    }
    
    //check for flags
    bool print_lower = false;
    bool print_upper = false;

    //allocate memory for positional arguments
    char **positional_argument = malloc((argc - 1) * sizeof(char *)); //argc - 1 to avoid wasting memory as argc[0] is always a program name not positional argument
    if(!positional_argument){                                         //Use char **positional_arguments when you need dynamic memory allocation for the array and flexibility in handling its size.
        fprintf(stderr, "Memory allocation failed.\n");               //Use char *positional_arguments[] when the size is fixed and known at compile time, or for array declarations in function signatures.
        return 1;
    }

    //parse the command-line arguments
    size_t positional_argument_count = 0;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lower") == 0){ // strcmp == 0 means equal, matched
            print_lower = true;
        }
            
        else if(strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--upper") == 0){
            print_upper = true;
        }

        else if(strcmp(argv[i], "--") == 0){
            positional_argument_count = find_positional_arguments(argv + i, positional_argument);
            break;
        }

        else if(argv[i][0] !=  '-'){ // remember ' ' not " " (because  this is a character not a string)
            positional_argument[positional_argument_count++] = argv[i];
        }
    }

    //validate positional arguments
    if(positional_argument_count < 1){
        fprintf(stderr, "Usage: %s[-l|--lower] [-u|--upper] <filename>\n", argv[0]);
        free(positional_argument);
        return 1;
    }

    const char *filename = positional_argument[0];

    //open the file     
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", filename);
        free(positional_argument);
        return 1;
    }

    int line_number = 1;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {   
        int upper = 0, lower = 0;
        count_upper_lower(buffer, &upper, &lower);
        printf("%3d: ", line_number);
        if (print_lower && print_upper) printf("lowercase: %d, uppercase: %d\n", lower, upper);
        else if (print_lower) printf("lowercase: %d\n", lower);
        else if (print_upper) printf("uppercase: %d\n", upper);
        else printf("%s", buffer);
        line_number++;
    }

    fclose(file);

    free(positional_argument);

    return 0;
}

size_t find_positional_arguments(char *argv[], char *positional_arguments[]) {
    size_t i = 1; //index of the first argument to check
    size_t positional_arguments_count = 0;
    while(argv[i] != NULL){
        if(strcmp(argv[i], "--") == 0){ // == 0 => matched
            while(argv[++i] != NULL){
                positional_arguments[positional_arguments_count++] = argv[i];
            }
            break;
        } else if (argv[i][0] != '-'){
            positional_arguments[positional_arguments_count++] = argv[i];
        }
        i++;
    }
    return positional_arguments_count;
}


void read_string(FILE* file, char buffer[], size_t size) {
    fgets(buffer, size, file);
    char *ptr = strrchr(buffer, '\n');
    if (ptr != NULL) {
        *ptr = '\0';
    }
}

void count_upper_lower(const char *buffer, int *upper, int *lower) {
    *upper = 0;
    *lower = 0;
    for (; *buffer != '\0'; buffer++) {
        if (isupper(*buffer)) {
            (*upper)++;
        } else if (islower(*buffer)) {
            (*lower)++;
        }
    }
}
