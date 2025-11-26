#include <stdio.h>
#include "students.h"

int main(void) {
    // Use this program to test your read_students function.
    // Run the program by redirecting a file to its standard input, e.g. ./assignment3 < students.txt
    student_t *students = NULL;
    size_t count = read_students(stdin, &students);

    printf("Read %zu students\n", count);

    for (size_t i = 0; i < count; i++) {
        printf("Name: %s (%u) GPA: %.2f\n", students[i].name, students[i].studentnr, calculate_gpa(&students[i]));
    }

    return 0;
}