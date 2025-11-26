#include <stdio.h>
#include "students.h"

int main(void) {
    student_t students[] = {
        { "Alice", 123456, (grade_t[]) { {1, 5, 8.0} }, 1 },
        { "Bob", 654321, (grade_t[]) { {1, 5, 10.0} }, 1 },
        { "Charlie", 987654, (grade_t[]) { {1, 5, 9.0} }, 1 }
    };

    sort_students(students, 3);

    for (size_t i = 0; i < 3; i++) {
        printf("Name: %s. GPA: %.2f\n", students[i].name, students[i].grades[0].score);
    }

    return 0;
}