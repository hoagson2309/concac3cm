#include <stdio.h>
#include "functions.h"
#include "concatenate.h"

int main(void) {
    char line[200];
    printf("Enter a line of text: ");

    // Create a new string_t structure that contains an empty string.
    string_t string = new_string("");

    // Read a line of text from the user.
    read_string(line, sizeof(line));

    // repeat while the line is not empty
    while (line[0] != '\0') {
        // TODO: Append the line to the string by calling append_string.
        append_string(&string, line);
        printf("Enter a line of text: ");
        read_string(line, sizeof(line));
    }

    printf("The concatenated string is: %s\n", string.data);
    
    // TODO: free the memory used by the string by calling free_string.
    free_string(&string);
    return 0;
}
