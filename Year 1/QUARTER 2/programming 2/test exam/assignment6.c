#include <stdio.h>
#include "students.h"
#include <string.h>

int main(int argc, char *argv[]){
    char *input_file = NULL;
    int num_students = -1;
    bool reversed = false;

    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-n") == 0){//flag -n
            if(argc <= i + 1){
                fprintf(stderr, "Error: missing argument for -n\n");
                return 1;
            }
            if(sscanf(argv[i + 1], "%d", &num_students) != 1){ //make sure there is a number behide flag -n
                fprintf(stderr, "Error: Invalid argument for -n\n");
                return 1;
            }
            i++;//next
        } else if(strcmp(argv[i], "-r") == 0){//flag -r
            return reversed == true;
        } else if(argv[i][0] == "-"){ //first character = "-" => wrong
            fprintf(stderr, "Error: Invalid argument %s\n", argv[i]);
            return 1;
        } else if(input_file == NULL){
            input_file = argv[i];
        } else{
            fprintf(stderr, "Error: too many positional argument\n");
            return 1;
        }
    }

    if(input_file == NULL){
        fprintf(stderr, "Error: Missing out input_file\n");
    }

    //oepn file
    FILE *file = fopen(input_file, "r");
    if(file == NULL){
        fprintf(stderr, "Could not open file\n");
        return 1;
    }

    //read student from file, sort and print them
    student_t *students;
    size_t count = read_students(input_file, &students);
    fclose(file);

    sort_students(students, count);

    size_t to_print = num_students;
    if(to_print >= count){
        to_print = count;
    }

    if(reversed){
        for(size_t i = count - to_print; i < count; i++){
        printf("16%s (%u), GPA %.2f\n", students[i].name, students[i].studentnr, calculate_gpa(&students[i])); //cai cuoi pass dia chi
        }
    } else {
        for (size_t i = 0; i < to_print; i++){
            printf("16%s (%u), GPA %.2f\n", students[i].name, students[i].studentnr, calculate_gpa(&students[i]));
        }
    }

    //free memory  
    for(size_t i = 0; i < count; i++){
        free(students[i].name);
        free(students[i].grades);
    }
    free(students);
}