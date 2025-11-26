#ifndef PERSONS_H
#define PERSONS_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int day, month, year;
} date_t;

typedef struct {
    char *name;
    date_t birthdate;
} person_t;

/// @brief Computes the age of a person.
/// @param p The person.
/// @return The age of the person.
int get_age(const person_t *p);

/// Reads a person (including birthdate) from a string
/// in the format "name,day-month-year".
/// @param person_string The string to parse.
/// @param person The person to fill.
/// @return True if the person was successfully read,
///         false otherwise.
bool read_person(const char *person_string, person_t *p);

/// @brief Reads an array of persons from a file, stores them in a dynamically allocated array,
/// @param file The file to read from.
/// @param count Address of a variable to store the number of persons read.
/// @return Pointer to the dynamically allocated array of persons.
person_t *read_persons(FILE *file, size_t *count);

/// @brief Prints an array of persons.
/// @param ps The array of persons.
/// @param count The number of persons in the array.
void print_persons(const person_t ps[], size_t count);

/// @brief Frees the memory allocated for the persons.
/// @param persons The array of persons.
/// @param count The number of persons in the array.
void free_persons(person_t *persons, size_t count);

#endif // PERSONS_H