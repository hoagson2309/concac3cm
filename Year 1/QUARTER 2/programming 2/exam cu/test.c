#include "word.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

const char *find(const char *word, const words_t *words){
    for(int i = 0; i < words->size; i++){
        if(strcmp(word, words->data[i]) == 0){
            return words->data[i];
        }
    }
    return NULL;
}

bool set_capacity(words_t *words, size_t desire_capacity){
    string_t *new_data = (string_t*) realloc(words->data, desire_capacity * sizeof(string_t));
    if(new_data != NULL){
        words->data = new_data;
        words->capacity = desire_capacity;
        return true;
    } else {
        fprintf(stderr, "Failed to allocate memory.\n");
        return false;
    }
}

bool add_unique_word(words_t *words, const char* word){
    const char* result = find(word, words);
    if(result == NULL){
        if(words->size == words->capacity){
            size_t new_capacity = words->capacity * 2 + 1;
            if(set_capacity(words, new_capacity)){
                words->capacity = new_capacity;
            }
        }
        char *ptr = malloc(strlen(word) + 1);
        strcpy(ptr, word);

        words->data[words->size] = ptr;
        words->size++;
        return true;
    }    
    return false;
}


words_t word(FILE *file){
    char buffer[100];
    words_t words = {NULL, 0, 0};
    while((fscanf, "%s", buffer) == 1){
        add_unique_word(&words, buffer);
    }
}

typedef struct {
    char **files;
    size_t size, capacity;
} cmdline_argument_t;

int main(int argc, char* argv[]){
    cmdline_argument_t args = {NULL, 0, 0};

    int i = 1;
    while(i < argc){
        if(args.size == args.capacity){
            size_t new_capacity = args.capacity * 2 + 1;
            char *file = (char*) realloc(args.files, new_capacity * sizeof(char));
            if(file != NULL){
                args.files = file;
                args.capacity = new_capacity;
            } else {
                fprintf(stderr, "Failed to allocate memory.\n");
                exit(1);
            }
        }
        strcpy(args.files + i, argv[i]);
        args.size++;
        i++;
    }
    for(int i = 0; i < args.size; i++){
        FILE *file = fopen(args.files[i], "r");
        if(file == NULL){
            fprintf(stderr, "Failed to open file.\n");
            exit(1);
        }
        words_t words = read_words(file);

        qsort(words.data, words.size, sizeof(string_t), compare_words);

        printf("%zu unique words found in file", words.size);
        fclose(file);
        free(words.data);
    }
}

int compare_words(const void *a, const void *b){
    const char *pa = (const char *) a;
    const char *pb = (const char *) b;
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);

    if(len_a > len_b) return -1;
    else if(len_a == len_b) return 0;
    else return 1;
}

