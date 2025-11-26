#include "persons.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int get_age(const person_t *p) {
    int parts[3];
    get_current_date(parts);
    int year = parts[0];
    int month = parts[1];
    int day = parts[2];

    int age = year - p->birthdate.year;
    if (month < p->birthdate.month || (month == p->birthdate.month && day < p->birthdate.day)) {
        age--;
    }
    return age;
}

bool read_person(const char *person_string, person_t *p) {
    char name[100];
    int read = sscanf(person_string, "%[^,],%d-%d-%d", name, &p->birthdate.day, &p->birthdate.month, &p->birthdate.year);
    if (read != 4) {
        return false;
    }
    p->name = (char*) malloc(strlen(name) + 1);
    strcpy(p->name, name);

    return true;
}

person_t *read_persons(FILE *file, size_t *count) {
    person_t *persons = NULL;
    *count = 0;
    size_t capacity = 0;

    char line[100];
    while (fgets(line, 100, file) != NULL) {
        if (*count == capacity) {
            capacity = capacity * 2 + 1;
            person_t *ptr = (person_t*) realloc(persons, capacity * sizeof(person_t));
            if (ptr == NULL) return persons;    // return the old array if realloc fails
            persons = ptr;
        }
        if (read_person(line, &persons[*count])) (*count)++;
    }
    return persons;
}

void print_persons(const person_t ps[], size_t count) {
    for (size_t i = 0; i < count; i++) {
        int age = get_age(&ps[i]);
        printf("%02d-%02d-%d  %s (age: %d)\n", ps[i].birthdate.day, ps[i].birthdate.month, ps[i].birthdate.year, ps[i].name, age);
    }
}

void free_persons(person_t *persons, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(persons[i].name);
    }
    free(persons);
}