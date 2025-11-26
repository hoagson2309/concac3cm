#include <stdio.h>
#include "functions.h"

float add(float a, float b) { return a + b; }
float multiply(float a, float b) { return a * b; }
float subtract(float a, float b) { return a - b; }
float divide(float a, float b) { return a / b; }

/// @brief Reads a character from the user and returns the matching function through a pointer
/// @return A function pointer that points to the function that corresponds to the user's choice, or NULL
float (*read_choice(void))(float, float);

int main(void) {
    float a, b;
    char trailing;
    printf("Enter two floating-point numbers: ");
    while (scanf("%f %f %c", &a, &b, &trailing) != 2) {
        printf("Invalid input. Please try again.\n");
        while (getchar() != '\n');  // Process input until the rest of the line
    }
    while (getchar() != '\n');  // Process input until the end of the line

    
    float (*operation)(float, float) = NULL;
    
    while (operation == NULL){
        // TODO: store the result of read_choice in a function pointer.
        operation = read_choice();
        // If the function returns NULL, keep on asking until the user made a valid choice.
        if(operation == NULL){
            printf("Invalid choice. Please try again.\n");
        }
    }
    // TODO: call the function returned by read_choice, passing a and b as arguments.
    float result = operation(a, b);
    // FIXME: print the result of the operation chosen by the user
    printf("The result is: %f\n", result);
}

float (*read_choice(void))(float, float) {
    // NOTE: you're not allowed to change this function!
    printf("Enter the operation (+, -, *, /): ");
    char choice = read_char();
    if (choice == '+') return add;
    else if (choice == '-') return subtract;
    else if (choice == '*') return multiply;
    else if (choice == '/') return divide;
    else return NULL;
}
