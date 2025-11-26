#ifndef STUDENTS_H
#define STUDENTS_H

#include <stdio.h>
#include <stdbool.h>


typedef struct grade {
    unsigned int exam_code; // exam code
    unsigned int ects;      // ECTS credits
    double score;           // score
} grade_t;

typedef struct student {
    char *name;                 // student's name
    unsigned int studentnr;     // student's student number
    grade_t *grades;            // array of grades
    unsigned int num_grades;    // number of grades in array
} student_t;

/// @brief Create a student with the given name and student number, and empty grades array.
/// @param name Name of the student.
/// @param studentnr Student number of the student.
/// @return A student with the given name and student number, and empty grades array.
student_t create_student(const char *name, unsigned int studentnr);

/// @brief Calculate the GPA of the student.
/// @param student Pointer to the student.
/// @return The GPA of the student.
double calculate_gpa(const student_t *student);

/// @brief Extract a student from a line of text.
/// @param line Line of text.
/// @param student Pointer to the student.
/// @return True if the student was extracted successfully, false otherwise.
bool parse_student(const char *line, student_t *student);

/// @brief Read students from a file into a dynamically allocated array.
/// @param file Pointer to the file.
/// @param ptr Pointer to the array of students.
/// @return Number of students read.
size_t read_students(FILE *file, student_t **ptr);

/// @brief Sorts the students in the array in descending order of GPA.
/// @param students The array of students.
/// @param num_students The number of students in the array.
void sort_students(student_t *students, size_t num_students);

#endif // STUDENTS_H