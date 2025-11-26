#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

/// A structure to represent a date.
typedef struct date {
    int day, month, year;
} date_t;

/// Reads a date from the user.
/// @return The date entered by the user.
date_t read_date(void);

/// Case-insensitive equality test of two strings.
/// @param string1 The first string to compare.
/// @param string2 The second string to compare.
/// @return true if the two strings are equal, and false otherwise.
bool equal_strings_ci(const char *string1, const char *string2);

/// Reads an integer from the user.
/// @return The integer entered by the user.
int read_int(void);

/// Reads a float from the user.
/// @return The float entered by the user.
float read_float(void);

/// Reads a double from the user.
/// @return The double entered by the user.
double read_double(void);

/// Reads a character from the user.
/// @return The character entered by the user.
char read_char(void);

/// Generates a random integer between min and max (inclusive).
/// @param min The minimum value of the random number.
/// @param max The maximum value of the random number.
int random_int(int min, int max);

/// Generates a random float between min and max (inclusive).
/// @param min The minimum value of the random number.
/// @param max The maximum value of the random number.
float random_float(float min, float max);

/// Returns the maximum of two integers.
/// @param a The first integer.
/// @param b The second integer.
/// @return The maximum of a and b.
int max_int(int a, int b);

/// Returns the minimum of two integers.
/// @param a The first integer.
/// @param b The second integer.
/// @return The minimum of a and b.
int min_int(int a, int b);

/// Returns the current date by filling an array
/// with the current year, month, and day.
/// @param date_parts An array of at least 3 integers.
/// @return True if the date was successfully retrieved,
///         false otherwise.
bool get_current_date(int date_parts[static 3]);

/// Returns the current time by filling an array
/// with the current hour, minute, and second.
/// @param time_parts An array of at least 3 integers.
/// @return True if the time was successfully retrieved,
///         false otherwise.
bool get_current_time(int time_parts[static 3]);

/// Reads a string from the user.
/// @param storage The array to store the string.
/// @param size The size of the storage array.
/// @return The string entered by the user. At most size - 1 characters are read, and the string is null-terminated.
void read_string(char storage[], int size);

#endif //FUNCTIONS_H
