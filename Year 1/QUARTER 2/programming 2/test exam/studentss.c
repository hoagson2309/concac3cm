#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "students.h"

student_t create_student(const char *name, unsigned int studentnr){
    student_t student = { .name = (char*) malloc(strlen(name) + 1), .studentnr = studentnr};
    if(student.name != NULL){
        strcpy(student.name, name);
    }
    return student;
}

double calculate_gpa(const student_t *student) {
    if(student->grades == 0){
        return 0.0;
    }

    double sum = 0.0;
    unsigned int total_ects;

    for(size_t i = 0; i < student->num_grades; i++){
        sum += student->grades[i].score * student->grades[i].ects;
        total_ects += student->grades[i].ects;
    }
    double total = sum / total_ects;
    return total;
}

bool parse_student(const char *line, student_t *student){
    char name[100];
    unsigned int student_number;
    unsigned int num_grades;
    int char_read;
    int result = sscanf(line, "%[^,], %u, %u%n", name, &student_number, &num_grades, &char_read);

    if(result != 3){
        return false;
    }
    *student = create_student(name, student_number);

    student->num_grades = num_grades;
    student->num_grades = (grade_t*) malloc(num_grades * sizeof(grade_t));
    if(student->num_grades == NULL){
        free(student->grades);
        return false;
    }

    line += char_read;

    unsigned int exam_code;
    unsigned int num_ects;
    double score;

    for(int i = 0; i < num_grades; i++){
        if(sscanf(line, " ,%u:%u:%lf%n", exam_code, num_ects, score) != 3){
            free(student->name);
            free(student->grades);
            return false;
        }
       line += char_read;
        
       student->grades[i].exam_code = exam_code;
       student->grades[i].ects = num_ects;
       student->grades[i].score = score;
    }
    return true;
}

size_t read_students(FILE *file, student_t **ptr) {
    *ptr = NULL;
    size_t count = 0, capacity = 0;

    char line[100];
    while(fgets(line, sizeof(line), file) != NULL){
        if(count == capacity){
            size_t new_capacity = capacity * 2 + 1;

            student_t *new_student = (student_t *) realloc(*ptr, new_capacity * sizeof(student_t));

            if(new_capacity == NULL){
                return count;
            }
            *ptr = new_student;
            capacity = new_capacity;
        }
        if(!parse_student(line, &((*ptr)[count]))){
            return count;
        }
        count++;
    }
    return count;

}

int compare(const void *a, const void *b){
    const student_t *pa = (const student_t*)a;
    const student_t *pb = (const student_t*)b;

    double gpa_a = calculate_gpa(pa);
    double gpa_b = calculate_gpa(pb);

    if(pa > pb) return -1;
    else if (pa == pb) return 0;
    else return 1;
}

void sort_students(student_t *students, size_t num_students) {
    qsort(students, num_students, sizeof(student_t), compare);
}

