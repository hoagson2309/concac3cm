#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "persons.h"


/// @brief compare 2 people by their birthday.
/// @param a Pointer to the first person.
/// @param b Pointer to the second person.
/// @return Negative if 'a' birthday is earlier, positive if 'b' birthday is earlier, 0 if both are equal.
int compare_birthdays(const void *a, const void *b){
    const person_t *p1 = (const person_t *)a;
    const person_t *p2 = (const person_t *)b;

    //Casting the void * to const person_t * allows you to work with a and b as pointers to person_t objects.
    //const ensures you don't accidentally modify the data.
    //This pattern is necessary whenever using a generic function like qsort that works with void *.

    //compare years
    if(p1->birthdate.year != p2->birthdate.year){
        return p1->birthdate.year - p2->birthdate.year;
    }

    //compare months
    if(p1->birthdate.month != p2->birthdate.month){
        return p1->birthdate.month - p2->birthdate.month;
    }

    //compare days
    return p1->birthdate.day - p2->birthdate.day;
}

int main(void) {
    // Open file
    FILE *file = fopen("calendar.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file.\n");
        return 1;
    }

    // Read persons from file
    size_t count;   // used to store the number of persons read
    person_t *persons = read_persons(file, &count);
    fclose(file);

    // TODO: Sort persons by age using qsort (you will need to define a comparison function!)
    qsort(persons, count, sizeof(person_t), compare_birthdays);

    // Print persons
    print_persons(persons, count);

    // Free memory
    free_persons(persons, count);
    return 0; 
}
