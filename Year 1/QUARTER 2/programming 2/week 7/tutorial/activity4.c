#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// @brief Reads a string from a file and removes the newline character.
/// @param file The file to read from.
/// @param buffer The buffer to store the string in.
/// @param size The size of the buffer.
/// @return The buffer containing the string read from the file, or NULL if an error occurred.
char *read_string(FILE* file, char buffer[], size_t size);

/// @brief Reads an integer from the user.
/// @param prompt The prompt to display to the user.
/// @return The integer read from the user.
int read_int(const char *prompt);


/// @brief Parses command line arguments for the filename and character limit.
/// @param argc The number of arguments.
/// @param argv The array of argument strings.
/// @param chars The number of characters per line.
/// @param filename The filename to be processed.
/// @return 1 if successful, 0 if there was an error.
int parse_arguments(int argc, char *argv[], int *chars, char *filename);

int main(int argc, char *argv[]) {

    int chars = -1; //default: unlimited characters per line

    char filename[100];

    //parse arguments
    if(!parse_arguments(argc, argv, &chars, filename)){
        return 1;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", filename);
        return 1;
    }

    char buffer[100];
    while (read_string(file, buffer, sizeof(buffer)) != NULL) { //calls the read_string function to read a line from the file into buffer.
        if (chars > 0 && chars < sizeof(buffer)) buffer[chars] = '\0';
        printf("%s\n", buffer);
    }

    fclose(file);

    return 0;
}

char *read_string(FILE* file, char buffer[], size_t size) {
    if (fgets(buffer, size, file) == NULL) return NULL;
    char *ptr = strrchr(buffer, '\n');
    if (ptr != NULL) *ptr = '\0'; //remove newline character if exists
    return buffer;
}

int parse_arguments(int argc, char *argv[], int *chars, char *filename) {
    for (int i = 1; i < argc; i++) {
        //check for named arguments (-c or --chars)
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--chars") == 0) {
            if (i + 1 < argc && sscanf(argv[i + 1], "%d", chars) == 1) { //the next argument can be parsed as an integer.(That next argument is a valid integer)
                i++;  //skip the next argument (the number for -c or --chars)
            } else {
                fprintf(stderr, "Error: Please provide an integer after -c or --chars\n");
                return 0;
            }
        } 
        //check for positional argument (filename)
        else if (strcmp(argv[i], "--") == 0) {
            if (i + 1 < argc) {
                //the first argument after "--" is the filename (positional argument)
                strcpy(filename, argv[i + 1]);
                i++;  //skip the next argument which is the filename
            } else {
                fprintf(stderr, "Error: Missing filename after '--'\n");
                return 0;
            }
        } 
        else {
            strcpy(filename, argv[i]);//if the current argument (argv[i]) is not -- and has not been parsed as a named argument, it is treated as the filename.
        }
    }
    
    if (strlen(filename) == 0) {
        fprintf(stderr, "Error: No filename provided.\n");
        return 0;
    }
    
    return 1;
}

