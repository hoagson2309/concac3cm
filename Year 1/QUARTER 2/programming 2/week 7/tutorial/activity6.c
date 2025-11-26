#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// @brief Reads a string from a file and removes the newline character.
/// @param file The file to read from.
/// @param buffer The buffer to store the string in.
/// @param size The size of the buffer.
/// @return The buffer containing the string read from the file, or NULL if an error occurred.
char *read_string(FILE* file, char buffer[], size_t size);

/// @brief Reads the next integer from a file, skipping non-numbers
/// @param file The file to read from.
/// @return The integer read from the file.
/// @return true if an integer was read, false if the end of the file was reached.
bool read_int(FILE *file, int *value);

int main(void) {
    const int num_columns = 10;

    int number;
    int column = 0;

    //read interger from stdin (no nead for filename)
    while (read_int(stdin, &number)) {
        printf("%10d", number); //print the number with the width of 10
        column = (column + 1) % num_columns;
        if (column == 0) printf("\n");
    }

    printf("\n");  //ensure a newline at the end if the last line doesn't have 10 numbers
    return 0;
}

char *read_string(FILE* file, char buffer[], size_t size) {
    if (fgets(buffer, size, file) == NULL) return NULL;
    char *ptr = strrchr(buffer, '\n');
    if (ptr != NULL) *ptr = '\0';
    return buffer;
}

bool read_int(FILE *file, int *value) {
    char buffer[100];
    int result = fscanf(file, "%99s", buffer);
    while (result != EOF && sscanf(buffer, "%d", value) == 0) {
        result = fscanf(file, "%99s", buffer);
    }
    return result != EOF;
}
