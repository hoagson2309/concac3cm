# Assignments - Week 4

You must complete two out of the three assignments, but you are encouraged to complete all three.
Below you will find, per assignment, instructions on what you need to include in this markdown file.

## Assignment 1 - Resistor values

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <math.h>
#include <ctype.h>

// TODO: define an enum type colour_t
typedef enum {
    BLACK, 
    BROWN,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    VIOLET,
    GREY,
    WHITE,
    GOLD,
    SILVER
} colour_t;

// TODO: define a structure type resistor_t
typedef struct{
    colour_t band1;
    colour_t band2;
    colour_t multiplier;
} resistor_t;

const char *color_names[] = {"black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "grey", "white", "gold", "silver"};
// TODO: define & implement functions get_value and read_colour

/// Checks if a colour is valid for the first two bands.
/// @param colour The colour to check.
/// @return True if the colour is valid, false otherwise.
bool is_valid_digit_band(colour_t colour) {
    return colour >= BLACK && colour <= WHITE; // Valid colours for digit bands
}

/// Returns the value of the resistor, or NaN if the given colour is not a valid colour for the first two bands.
/// @return The value of the given colour.
double get_value(const resistor_t *resistor);
double get_value(const resistor_t *resistor){
    if(!is_valid_digit_band(resistor->band1) || !is_valid_digit_band(resistor->band2)){
        return NAN; // return "not a number(NAN) (0.0/0.0)" if invalid
    }

    //compute the base value of the first 2 band 
    int base_value = (resistor->band1 * 10) + resistor->band2; //displays 2 numbers next to each other

    if ( resistor->multiplier == GOLD ){ // gold => x10^-1
        return base_value * 0.1;
    }
    if ( resistor->multiplier == SILVER ){ // silver => x10^-2
        return base_value * 0.01;
    }
    if ( resistor->multiplier >= BLACK && resistor->multiplier <= WHITE ){
        return base_value * pow(10, resistor->multiplier); // x10^n (n depends on each color)
    }
    return NAN;
}

/// Reads a colour from the user. Repeat until the user enters a valid colour.
/// @param prompt The prompt to display to the user. (question)
/// @return The colour entered by the user.
colour_t read_colour(const char *prompt);
colour_t read_colour(const char *prompt){
    char input[20]; // separate buffer to hold user input
    while (true){
        printf("%s", prompt);
        scanf("%19s", input); 
        for(size_t i = 0; i < sizeof(color_names) / sizeof(color_names[0]); i++){
            if (equal_strings_ci(input, color_names[i])){
                return (colour_t)i; //return the matching color
            }
        }
        // if no match, prompt again
        printf("Invalid color. Please try again.\n");
    }
}

int main(void) {
    resistor_t resistor;
    printf("Enter the colors of the resistor: ");
    
    // TODO: ask user to enter three colours, store these in a resistor_t variable
    resistor.band1 = read_colour("Enter the first color band: ");
    resistor.band2 = read_colour("Enter the second color band: ");
    resistor.multiplier = read_colour("Enter the third color band: ");
    
    // TODO: use the function get_value to calculate the value of the
    // TODO: print the value of the resistor 
    double value = get_value(&resistor);
    if(isnan(value)){
        printf("Invalid colours were specified\n");
    } else{
    printf("The value of the resistor is %.2lf ohms\n", value);
    }
    return 0;
}

```

## Assignment 2 - Colours and brightness

In this assignment you will work with three files: `main.c`, `colours.h`, and `colours.c`.

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
```

Include the prototypes for the functions you wrote in `colours.h` here:

```c
// TODO: Include the prototypes for the functions you wrote in `colours.h` here
```

Include the definitions for the functions you wrote in `colours.c` here:

```c
// TODO: Include the definitions for the functions you wrote in `colours.c` here
```

## Assignment 3 - Grade administration

In this assignment you will work with three files: `main.c`, `student.h`, and `student.c`.

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
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

```

Include the contents of your `student.h` file here:

```c
// TODO: Include the contents of your `student.h` file here
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

```

Include the contents of your `student.c` file here:

```c
// TODO: Include the contents of your `student.c` file here
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


```

