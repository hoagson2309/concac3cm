# Assignments - Week 5

You must complete two out of the three assignments, but you are encouraged to complete all three.
Below you will find, per assignment, instructions on what you need to include in this markdown file.

## Assignment 1 - Simple file encryption

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
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

```

## Assignment 2 - Reading coordinates

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

/// @brief A structure representing a coordinate in 2D space.
typedef struct {
    int x;
    int y;
} coordinate_t;

/// Checks if the string contains a valid coordinate in the form (x, y).
/// @param string The string to check.
/// @param coordinate The coordinate to store the values in.
/// @return `true` if the string contains a valid coordinate without trailing characters, `false` otherwise.
bool read_coordinate(const char *string, coordinate_t *coordinate){
    char extra;
    int matched = sscanf(string, "(%d, %d)%c", &coordinate->x, &coordinate->y, &extra); //& to pass the address of x and y in coordinate. Using &coordinate->x gives sscanf the precise memory location to store the parsed x value.// vi track x trong pointer *coordinate nen phai co &

    //make sure there's no extra trailing character, the only valid input is (x, y)
    return matched == 2;
}

/// Calculates the distance between two coordinates.
/// @param first The first coordinate.
/// @param second The second coordinate.
/// @return The distance between the two coordinates.
double distance(coordinate_t first, coordinate_t second);

int main(void) {
    // TODO:
    char input[300];
    coordinate_t previous, current;
    bool has_previous = false;

    //   - read a line from the standard input
    printf("Please enter a coordinate: ");

    while(fgets(input, sizeof(input), stdin) != NULL){
        char *ptr = strchr(input, '\n');
        if(ptr != NULL){
            *ptr = '\0';
        }

    //   - check if the line contains a valid coordinate
    if(read_coordinate(input, &current)){
        if(has_previous){
            //   - if it does, compute the distance between this coordinate and the previous one (if there is a previous one)
            double dist = distance(previous, current);
            printf("The distance between (%d, %d) and (%d, %d) is %.6f.\n", previous.x, previous.y, current.x, current.y, dist);
        }
        previous = current;
        has_previous = true;
    } else {
        printf("Invalid input, please try again.\n");
    }

    printf("Please enter a coordinate: ");
    }
    printf("Bye!\n");
    return 0;
}

double distance(coordinate_t first, coordinate_t second) {
    return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

```

## Assignment 3 - Usernames and passwords

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here

```

