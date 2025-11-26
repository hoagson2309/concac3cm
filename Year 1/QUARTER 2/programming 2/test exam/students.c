#include <stdlib.h>
#include <string.h>
#include "students.h"


student_t create_student(const char *name, unsigned int studentnr) {
    student_t student = { .name = (char*) malloc(strlen(name) + 1), .studentnr = studentnr };
    if(student.name != NULL){
    strcpy(student.name, name);
    }
    return student;
}

double calculate_gpa(const student_t *student) {
    if(student->num_grades == 0){
        return 0.0;
    }
    double sum = 0.0;
    unsigned int total_ects;

    for(size_t i = 0; i < student->num_grades; i++){
        sum += student->grades[i].score * student->grades[i].ects;
        total_ects += student->grades[i].ects;
    }

    return sum / total_ects;
}

bool parse_student(const char *line, student_t *student) {
    char name[100];
    unsigned int student_number;
    unsigned int num_grades;
    int chars_read;
    int result = sscanf(line, "%[^,],%u,%u%n", name, &student_number, &num_grades, &chars_read);
    
    if(result != 3){
        // result should be 3 if all format specifiers are matched (%n is not included in the count)
        return false;
    }

    //Uses create_student (assumed to dynamically allocate memory for the student's name) to initialize the student_t structure.
    *student = create_student(name, student_number);

    //allocate memory for the grades
    student->num_grades = num_grades;
    student->grades = (grade_t*) malloc(num_grades * sizeof(grade_t)); //num_grade la so lg cac grade trong array grades giong capacity arr co the chua
    if(student->grades == NULL){
        free(student->name); //deallocate the name
        return false;
    }

    line += chars_read;//continue parsing from where we left off

    unsigned int exam_id;
    unsigned int ects;
    double grade;

    //parse the grades
    for(size_t i = 0; i < num_grades; i++){
        if(sscanf(line, ",%u:%u:%lf%n", &exam_id, &ects, &grade,  &chars_read) != 3){
            //we should have 3 values, so this is an error
            free(student->name);
            free(student->grades);
            return false;
        }
        line += chars_read; //continues parsing what we left off
        student->grades[i].exam_code = exam_id;
        student->grades[i].ects = ects;
        student->grades[i].score = grade;
    }
    return true;
}

size_t read_students(FILE *file, student_t **ptr) {
    *ptr = NULL; //Initially, this array is NULL, as we don’t know how many students there are
    size_t count = 0, capacity = 0;

    char line[1000];
    while(fgets(line, sizeof(line), file) != NULL){ //fgets to read line by line from file then store buffer (line[])
        if(count == capacity){
            size_t new_capacity = capacity * 2 + 1; //doubling the size,(or starts with 1 if the capacity was 0).
            
            student_t *new_student = (student_t*) realloc(*ptr, capacity * sizeof(student_t));

            if(new_student == NULL){
                //failed to allocate
                return count;
            }

            *ptr = new_student;
            capacity = new_capacity;
        } 
        if(!parse_student(line, &((*ptr)[count]))){
            //error handling
            return count;
        }
        count ++;
    }

    return count;//increment the count
}

int compare(const void *a, const void *b){
    const student_t *student_a = (const student_t *)a;
    const student_t *student_b = (const student_t *)b;

    double gpa_a = calculate_gpa(student_a);
    double gpa_b = calculate_gpa(student_b);

    if(gpa_a > gpa_b){
        return 1;
    } else if(gpa_a < gpa_b){
        return -1;
    } else{
        return 0;
    }
}

void sort_students(student_t *students, size_t num_students) {
    qsort(students, num_students, sizeof(student_t), compare);
}
