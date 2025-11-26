#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "student.h"
#include <ctype.h>

int main(void) {
    student_t students[20];
    int student_count = 0;
    student_t student;
    
    // TODO: read students from the user and store them in the `students` array
    //       stop reading students when the user enters an empty name
    while(student_count < 20){
        student = read_student("Enter the name of the student: ");
        if(strlen(student.name) == 0){
            break;
        }
        students[student_count++] = student;
    }
    //       Next, print all students with their grade
    printf("\nGrade:\n");
    for(int i = 0; i < student_count; i++){
        print_student(&students[i]);
    }
    //       Finally, print the number of students with each grade
    printf("Number of students per grade:\n");
    printf("insufficient: %d\n", count_students_with_grade(students, student_count, INSUFFICIENT));
    printf("sufficient: %d\n", count_students_with_grade(students, student_count, SUFFICIENT));
    printf("good: %d\n", count_students_with_grade(students, student_count, GOOD));
    printf("outstanding: %d\n", count_students_with_grade(students, student_count, OUTSTANDING));

    return 0;
}
