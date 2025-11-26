#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "student.h"
#include "functions.h"

const char *grade_to_text(result_t grade) {
    switch (grade) {
        case INSUFFICIENT:
            return "Insufficient";
        case SUFFICIENT:
            return "Sufficient";
        case GOOD:
            return "Good";
        case OUTSTANDING:
            return "Outstanding";
    }
    return "Unknown";
}

student_t read_student(const char *prompt){
    student_t student;
    char grade_char;    

    printf("%s", prompt);
    if (scanf("%s", student.name) != 1 || strlen(student.name) == 0){
        student.grade = -1; //invalid grade => stop signal
        return student;
    }


    printf("Enter the grade for %s (i, s, g, o): ", student.name);
    scanf(" %c", &grade_char);

    switch(tolower(grade_char)){
        case 'i': student.grade = INSUFFICIENT; break;
        case 's': student.grade = SUFFICIENT; break;
        case 'g': student.grade = GOOD; break;
        case 'o': student.grade = OUTSTANDING; break;
        default:
            printf("Invalid grade entered. Defaulting to 'insufficient'.\n");
            student.grade = INSUFFICIENT;
        }
    return student;
}

void print_student(const student_t *student){
    printf("%s: %s\n", student->name, grade_to_text(student->grade)); //to access the members of a structure through a pointer to the structure ( (*p).name or p->name )

}

int count_students_with_grade(const student_t students[static 1], int count, result_t grade){
    int total = 0;
    for(int i = 0; i < count; i++){
        if(students[i].grade == grade){
            total++;
        }
    }
    return total;
}

