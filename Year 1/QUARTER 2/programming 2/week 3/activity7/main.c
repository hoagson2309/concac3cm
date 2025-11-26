#include <stdio.h>
#include "functions.h"

typedef struct {
    int day;
    int month;
    int year;
} date_t;

typedef struct {
    char name[100];         // the person's name
    date_t birth_date;  // the person's birth date
} person_t;

/// @brief Reads a person's information from the user.
/// @return The person's information. If the name is an empty string, the function returns a person with a NULL name.
person_t read_person(void);

int main(void) {
    person_t persons[10];
    const int max_persons = sizeof(persons) / sizeof(persons[0]);

    printf("Enter at most %d persons' information.\n", max_persons);
    int num_persons = 0;
    while (num_persons < max_persons) {
        persons[num_persons] = read_person();
        if (persons[num_persons].name[0] == '\0') {
            break;
        }

        num_persons++;
    }

    printf("You've entered the following %d persons:\n", num_persons);
    for (int i = 0; i < num_persons; i++) {
        printf("Person %d: %s, born on %d/%d/%d\n", i + 1, persons[i].name, persons[i].birth_date.day, persons[i].birth_date.month, persons[i].birth_date.year);
    }
}

person_t read_person(void) {
    person_t person;

    printf("Enter the name of the person (Empty line to abort): ");

    read_string(person.name, sizeof(person.name));
    if (person.name[0] == '\0') {
        return (person_t) { .name = "", .birth_date = {0, 0, 0} }; //Return an empty person
    }

    printf("Enter the birth date of the person:\n");
    printf(" Day: ");
    person.birth_date.day = read_int();
    printf(" Month: ");
    person.birth_date.month = read_int();
    printf(" Year: ");
    person.birth_date.year = read_int();

    return person;
}