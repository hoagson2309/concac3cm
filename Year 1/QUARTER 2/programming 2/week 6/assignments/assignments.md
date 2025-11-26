# Assignments - Week 6

You must complete two out of the three assignments, but you are encouraged to complete all three.
Below you will find, per assignment, instructions on what you need to include in this markdown file.

## Assignment 1 - Generic reversal

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
#include <stdio.h>
#include <string.h>
#include "utils.h"

/// @brief Reverse an array.
/// @param array The array to reverse.
/// @param count The number of elements in the array.
/// @param size The size of each element in bytes.
void reverse(void *array, size_t count, size_t size);

int main(void) {
    int integers[10];
    float floats[12];
    char characters[20];

    fill_random(integers, sizeof(integers) / sizeof(integers[0]), sizeof(int), 0, 255);
    fill_random(floats, sizeof(floats) / sizeof(floats[0]), sizeof(float), 0, 255);
    fill_random(characters, sizeof(characters) / sizeof(characters[0]), sizeof(char), 'a', 'z');

    printf("Original arrays:\n");
    print_ints(integers, sizeof(integers) / sizeof(integers[0]));
    print_floats(floats, sizeof(floats) / sizeof(floats[0]));
    print_chars(characters, sizeof(characters) / sizeof(characters[0]));

    reverse(integers, sizeof(integers) / sizeof(integers[0]), sizeof(int));
    reverse(floats, sizeof(floats) / sizeof(floats[0]), sizeof(float));
    reverse(characters, sizeof(characters) / sizeof(characters[0]), sizeof(char));

    printf("\n\nAfter reversing:\n");
    print_ints(integers, sizeof(integers) / sizeof(integers[0]));
    print_floats(floats, sizeof(floats) / sizeof(floats[0]));
    print_chars(characters, sizeof(characters) / sizeof(characters[0]));
}


void reverse(void *array, size_t count, size_t size) {
    // TODO: implement this function!
    char *array_ptr = (char *)array;
    for(size_t i = 0; i < count / 2; i++){
        char *front = array_ptr + i * size;
        char *back = array_ptr + (count - 1 - i) * size;

        //swap element front and back
        for(size_t j = 0; j < size; j++){
            char temp = front[j];
            front[j] = back[j];
            back[j] = temp;
        }
    }
}

```

## Assignment 2 - Sorting by birthday

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
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

```

## Assignment 3 - Finding the "maximum"

Include the contents of your `main.c` file here:

```c
// TODO: Include the contents of your `main.c` file here
```

