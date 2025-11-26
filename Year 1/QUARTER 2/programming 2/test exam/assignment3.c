#include <stdio.h>
#include "students.h"

int main(void) {
    // Use this program to test your implementation of the parse_student function.

    const char *line = "Eve Garcia,3785907,6,112:5:8.4,103:5:7.7,112:5:3.4,120:1:9.2,103:1:9.5,106:3:6.0";

    student_t student;

    bool result = parse_student(line, &student);
    if (result) {
        printf("Name: %s\n", student.name);
        printf("Student number: %u\n", student.studentnr);
        printf("Number of grades: %u\n", student.num_grades);
        for (size_t i = 0; i < student.num_grades; i++) {
            printf("Exam code: %u, ECTS: %u, Score: %.1f\n", student.grades[i].exam_code, student.grades[i].ects, student.grades[i].score);
        }
    }
    else {
        printf("Failed to parse student\n");
    }
 
    return 0;
}