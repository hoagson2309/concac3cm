#include <stdio.h>
#include <string.h>
#include "functions.h"

#define MAX_NAME_LENGTH 200
#define MAX_PERSONS_IN_CALENDAR 100

typedef struct {
    char name[MAX_NAME_LENGTH]; // Name of the person, fixed length
    date_t birth_date;          // Birth date of the person
} person_t;

typedef struct {
    person_t persons[MAX_PERSONS_IN_CALENDAR];  // Array of a fixed size
    size_t count;              // Number of persons stored in the calendar
} calendar_t;

/// @brief Reads a person from the user.
/// @param person address at which the data of the person will be stored
/// @return True if a person was successfully read, and false otherwise.
bool read_person(person_t *person);

/// @brief Prints the calendar.
/// @param calendar The calendar to print.
void print_calendar(const calendar_t *calendar);

int main(void) {
    calendar_t calendar = { .count = 0 };
    printf("NOTE: The calendar occupies %zu bytes of memory\n", sizeof(calendar));

    while (read_person(&calendar.persons[calendar.count])) {
        calendar.count++;
    }

    printf("\nThere are %zu persons in the calendar:\n", calendar.count);
    // Print the calendar, passing the calendar_t struct as an argument by value
    print_calendar(&calendar); // pass a pointer instead of by value
}

bool read_person(person_t *person) {
    printf("Enter the name of the person: ");
    read_string(person->name, sizeof(person->name));

    // if the name consists of only whitespace characters, return false
    if (strspn(person->name, " \t\r") == strlen(person->name)) return false;

    printf("Enter the birth date of the person (dd-mm-yyyy): ");
    person->birth_date = read_date();
    return true;
}

void print_calendar(const calendar_t *calendar) {
    for (size_t i = 0; i < calendar->count; i++) {
        printf("%s was born on %02d-%02d-%d\n", calendar->persons[i].name,
               calendar->persons[i].birth_date.day,
               calendar->persons[i].birth_date.month,
               calendar->persons[i].birth_date.year);
    }
}
