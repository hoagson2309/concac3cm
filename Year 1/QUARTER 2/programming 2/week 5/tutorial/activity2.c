#include <stdio.h>
#include "functions.h"
#include <string.h>

int main(void) {
    char buffer[100];
    printf("Enter the name of the file: ");
    read_string(buffer, sizeof(buffer));

    // TODO: open the filename for writing
    FILE *file = fopen(buffer, "w");
    //       print "Failed to open file." if the file could not be opened
    if(file == NULL){
        printf("Failed to open file.\n");
        return 1;
    }
    
    do {
        printf("Enter a string: ");
        read_string(buffer, sizeof(buffer));
        if (strlen(buffer) > 0) {
            // TODO: write the string to the file using fprintf
            fprintf(file, "%s\n", buffer);
        }
    }
    while (strlen(buffer) != 0);

    // TODO: close the file
    fclose(file);
}

