#include <stdio.h>
#include "functions.h"

int main(void) {
    char filename[100];
    printf("Enter the name of the file: ");
    read_string(filename, sizeof(filename));

    // TODO: try opening the filename for reading
    FILE *file = fopen(filename, "r");
    //       print "File opened successfully." if the file was opened
        if(file != NULL){
            printf("File %s opened successfully.\n", filename);
            
            fclose(file);
        }
    //       print "Failed to open file." if the file was not opened
        else{
            printf("Failed to open file.\n");
        }
    return 0;  
}

