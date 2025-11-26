#include <stdio.h>
#include <stdlib.h>
#include "students.h"

int main(void) {
    // Use this code to test your create_student function
    student_t s = create_student("Bob Smith", 123456);
    printf("Student: %s\n", s.name);
    printf("Student number: %u\n", s.studentnr);
    printf("Number of grades: %u\n", s.num_grades);

    // Free the dynamically allocated memory for the student's name
    free(s.name);

    return 0;
}