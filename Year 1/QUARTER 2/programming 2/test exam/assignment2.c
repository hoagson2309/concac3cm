#include <stdio.h>
#include "students.h"

int main(void) {
    // Use this program to test your implementation of the calculate_gpa function.

    grade_t grades[] = {
        {1, 5, 10.0},       // grade 10.0 with 5 ECTS credits
        {2, 1, 4.0}         // grade 4.0 with 1 ECTS credit
    };

    student_t student = create_student("Alice", 123456);
    student.grades = grades;
    student.num_grades = sizeof(grades) / sizeof(grades[0]);

    printf("GPA: %.2f\n", calculate_gpa(&student));

    return 0;
}