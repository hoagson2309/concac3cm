#ifndef STUDENT_H
#define STUDENT_H

// A type to represent the result of a student's exam
typedef enum { INSUFFICIENT, SUFFICIENT, GOOD, OUTSTANDING } result_t;

// A type to represent a student with a name and a grade
typedef struct {
    char name[100];
    result_t grade;
} student_t;

/// Uses the console to read a student from the user.
/// @param prompt The prompt to display to the user.
/// @return The student entered by the user.
student_t read_student(const char *prompt);

/// Returns the text representation of a grade.
/// @param grade The grade to convert to text.
/// @return The text representation of the grade.
const char *grade_to_text(result_t grade);

/// Prints a student (name and grade) to the console.
/// The grade is printed in text form as "insufficient", "sufficient", "good", or "outstanding".
/// @param student The student to print.
void print_student(const student_t *student);

/// Counts the number of students that have a certain grade.
/// @param students The array of students.
/// @param count The number of students in the array.
/// @param grade The grade students must have to be included in the count.
/// @return The number of students that have the specified grade.
int count_students_with_grade(const student_t students[static 1], int count, result_t grade);

#endif // STUDENT_H
