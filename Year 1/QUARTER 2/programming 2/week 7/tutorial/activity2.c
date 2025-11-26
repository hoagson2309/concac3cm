#include <stdio.h>
#include <string.h>

void read_string(FILE* file, char buffer[], size_t size) {
    fgets(buffer, size, file);
    char *ptr = strrchr(buffer, '\n');
    if (ptr != NULL) {
        *ptr = '\0';
    }
}

int main(int argc, char *argv[]){
    //check if filename is provided as a command-line argument
    if(argc < 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", filename);
        return 1;
    }

    int line_number = 1;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%3d: %s", line_number, buffer);
        line_number++;
    }

    fclose(file);

    return 0;
}
