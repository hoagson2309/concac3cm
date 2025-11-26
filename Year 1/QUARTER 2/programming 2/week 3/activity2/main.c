#include <stdio.h>
#include "functions.h"

struct date{
    int day;
    int month;
    int year;
};

/// @brief Computes the age of a person given their birth year, month, and day.
/// @param birth_date
/// @return the age in years, or -1 if the current date could not be retrieved.
int compute_age(struct date birth_date);

int main(void) {
    struct date birth_date;
    
    printf("Please enter your birth year: ");
    birth_date.year = read_int(); // FIXME: remove this variable & store day in a structure variable

    printf("Please enter your birth month: ");
    birth_date.month = read_int(); // FIXME: remove this variable & store day in a structure variable

    printf("Please enter your birth day: ");
    birth_date.day = read_int(); // FIXME: remove this variable & store day in a structure variable

    // compute age and print it
    int age = compute_age(birth_date);
    if (age == -1) {
        printf("Failed to retrieve the current date.\n");
    } else {
        printf("You are %d years old.\n", age);
    }
}

int compute_age(struct date birth_date) {
    struct date current_date;
    int current_date_array[3];
    if (get_current_date(current_date_array)) {
        current_date.year = current_date_array[0];
        current_date.month = current_date_array[1];
        current_date.day = current_date_array[2];

        int age = current_date.year - birth_date.year;
        if (current_date.month < birth_date.month || (current_date.month == birth_date.month && current_date.day < birth_date.day)) {
            age--;
        }

        return age;
    } else {
        return -1;
    }
}

