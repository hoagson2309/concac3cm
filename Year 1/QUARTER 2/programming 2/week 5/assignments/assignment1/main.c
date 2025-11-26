#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include <ctype.h>

/// @brief encrypts a string by rotating the letters 13 positions in the ASCII table.
/// @param string The string to encrypt.
void encrypt_string(char *string){
    for(int i = 0; string[i] != '\0'; i++){
        char ch = string[i];
        if(isalpha(ch)){
            if(islower(ch)){
                string[i] = 'a' + (ch - 'a' + 13) % 26; // calculates the zero-based position(number) -> shift forward 13 positions -> %26  ensures the result wraps around back to the beginning so that it's not exceed 26 which is Z -> then 'a' + .. is to convert back to ASCII character
            }
            if(isupper(ch)){
                string[i] = 'A' + (ch - 'A' + 13) % 26;
            }
        }
    }
}

int main(void) {
    // TODO:
    //  - Ask user to enter a filename
    char filename[100];
    printf("Enter the name of the file: ");
    if(fgets(filename, sizeof(filename), stdin) == NULL){
        fprintf(stderr, "Error reading filename\n");
        return 1;
    }

    char *ptr = strchr(filename, '\n');//removing trailing newline from filename, if present
    if(ptr != NULL) *ptr = '\0';

    //  - Open the file and read it line by line (print an error if it can't be opened)
    FILE *input_file = fopen(filename, "r");
    if(input_file == NULL){
        fprintf(stderr, "Failed to open %s file.\n", filename);
        return 1;
    }

    char output_filename[105]; // create output filename by appending .enc
    strcpy(output_filename, filename);
    strcat(output_filename, ".enc");

    FILE *output_file = fopen(output_filename, "w");
    if(output_file == NULL){
        fprintf(stderr, "Error, could not create a file %s.", output_filename);
        fclose(input_file);
        return 1;
    }
    //  - Write the encrypted line to a new file that has the same name as the original file, but with the extension .enc added
    char line[1024];
    while(fgets(line, sizeof(line), input_file) != NULL){
        encrypt_string(line); //  - Encrypt each line using the encrypt_string function
        fputs(line, output_file);//write the encrypted line to the output_file
    }

    //  - Close the files
    fclose(input_file);
    fclose(output_file);

    printf("File '%s' has been encrypted and saved as '%s'.\n", filename, output_filename);

    return 0;
}
