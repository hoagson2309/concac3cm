#include <stdlib.h>
#include <string.h>
#include "word.h"

//Assignment 1
const char *find(const char *word, const words_t *words){
    for(size_t i = 0; i < words->size; i++){
        if(strcmp(word, words->data[i]) == 0){
            return words->data[i];
        }
    }
    return NULL;
}

//Assignment 2
bool set_capacity(words_t *words, size_t desire_capacity){
    string_t *new_data = (string_t*) realloc(words->data, desire_capacity * sizeof(string_t));
    if(new_data != NULL){
        words->data = new_data;
        words->capacity = desire_capacity;
        return true;
    } else {
        fprintf(stderr, "Failed to allocate memory\n");
        return false;
    }
}

//Assignment 3
bool add_unique_word(words_t *words, const char* word){
    const char *result = find(word, words);
    if(result == NULL){
        if(words->size == words->capacity){
            size_t new_capacity = words->capacity * 2 + 1;
            if(set_capacity(words, new_capacity)){
                words->capacity = new_capacity;
            }
        }
        char *ptr = malloc(strlen(word) + 1); // + null terminator
        strcpy(ptr, word);

        words->data[words->size] = ptr;
        words->size++;
        return true;
    }
    return false; 
}

//Assigment 4
words_t read_words(FILE *file){
    char buffer[100];
    words_t words = {NULL, 0, 0};
    while(fscanf(file, "%s", buffer) == 1){
        add_unique_word(&words, buffer);
    }
    return words;
}

//Assignment 5
typedef struct { 
    char **files;
    size_t count, capacity;
} cmdline_argument_t;

int main(int argc, char* argv[]){
    cmdline_argument_t args = {NULL, 0, 0};

    int i = 1;
    while(i < argc){
        if(args.count == args.capacity){
            size_t new_capacity = args.capacity * 2 + 1;
            char* file = (char*) realloc(args.files, new_capacity * sizeof(char)); //allocate new memory
            if(file != NULL){
                args.files = file; //update file with new memory
                args.capacity = new_capacity; //update new capacity
            } else {
                fprintf(stderr, "Failed to allocate memory\n");
                exit(1); 
            }
        }
        strcpy(args.files + i, argv[i]); //pass (content) argument at i to arg.files at i 
        args.count++;
        i++;
    }
    
    for(size_t i = 0; i < args.count; i++){
        FILE *file = fopen(args.files[i], "r");
        if(file == NULL){
            fprintf(stderr, "Could not open file %s\n", file);
            exit(1);
        }
        words_t words = read_words(file);

        qsort(words.data, words.size, sizeof(string_t), compare_words);

        printf("%zu unique word found in the file", words.size);
        fclose(file);
        free(words.data);
    }
    return 0;
}

int compare_words(const void *a, const void *b){
    const char* pa = (const char*) a;
    const char* pb = (const char*) b;
    size_t len_a = strlen(pa);
    size_t len_b = strlen(pb);

    if(len_a > len_b) return -1;
    else if(len_a = len_b) return 0;
    else return 1;
}