# Week 3 - Tutorial: Working with structures and enumerations

Name: SON CAO

Group: ETI1V.IA

Date: 29/11/2024

## Introduction

The C programming language provides only a limited set of built-in data types, such as integers, floating-point numbers, and characters.
Sometimes this is not enough, and you need to create your own data types.
This can be done using structures and enumerations.

Enumerations are the simplest of the two, and they are used to define a set of named (integer) constants.
This allows you to avoid the use of "magic numbers" in your code.

Structures are used to group variables of different types together.
They are used to create more complex data types that can be used to store data in a structured way.
Where functions allow you to group code together, structures allow you to group data together.
Structures are an important concept in C programming, and understanding them is crucial before moving to more advanced languages like C++.

## Enumerations

An enumeration is a user-defined data type that consists of a set of named constants.
You could use an enumeration, for example, to refer to the days of the week:

```c
enum day {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};
```

This would work better than using integers (say 0 through 6) to represent the days of the week, as that would mean you would have to remember which number corresponds to which day.

The code snippet above does not create any variables, but only defines a new *type* called `enum day`.
After you've defined an enumeration, you can create variables of that type and assign one of the values to it:

```c
enum day today = TUESDAY;
```

Here, the variable's name is `today`, and its type is `enum day`.

The values in an enumeration are assigned automatically, starting from 0 by default.
If you want to assign specific values to the constants, you can do so.
For example, to assign the values 1 through 12 to the months of the year, you could write:

```c
enum month {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};
```

Note that you only need to specify the value for the first constant, and the rest will be assigned automatically.

### Activity 1 - Using enums

The program in `activity1` contains the well-known rock-paper-scissors game.
It uses magic numbers to represent the choices of the player and the computer, which makes the code less readable and harder to maintain.
Replace all the magic numbers with an enumeration type called `choice` that has three values: `ROCK`, `PAPER`, and `SCISSORS`.
The program must not contain any numbers after this change.

When you're done, compile and run the program to test that it still works correctly.
If it does and your program contains no magic numbers, paste the contents of the modified `main.c` file below:

```c
// TODO: Paste your modified main.c file here
#include <stdio.h>
#include <string.h>
#include "functions.h"

enum item_type{
    ROCK,
    PAPER,
    SCISSOR
};

int read_choice(void) {
    printf("What is your choice? ('R' for Rock, 'P' for Paper, 'S' for Scissors): ");
    char choice = read_char();
    while (strchr("RrPpSs", choice) == NULL) {
        printf("Invalid choice. Please enter 'R', 'P', or 'S': ");
        choice = read_char();
    }
    if (choice == 'R' || choice == 'r') {
        return ROCK;   // FIXME: remove magic number
    } else if (choice == 'P' || choice == 'p') {
        return PAPER;   // FIXME: remove magic number
    } else {
        return SCISSOR;   // FIXME: remove magic number
    }
}

int main(void) {
    printf("** Rock, Paper, Scissors **\n");
    int user_choice = read_choice();
    if (user_choice == ROCK) printf("You chose Rock.\n");  // FIXME: remove magic number
    else if (user_choice == PAPER) printf("You chose Paper.\n");    // FIXME: remove magic number
    else printf("You chose Scissors.\n");

    int cpu_choice = random_int(ROCK, SCISSOR);  // FIXME: remove magic number
    if (cpu_choice == ROCK) printf("I chose Rock.\n"); // FIXME: remove magic number
    else if (cpu_choice == PAPER) printf("I chose Paper.\n");   // FIXME: remove magic number
    else printf("I chose Scissors.\n");

    if (user_choice == cpu_choice) printf("It's a tie!\n");

    // FIXME: remove magic number below
    else if ((user_choice == ROCK && cpu_choice == SCISSOR) || (user_choice == PAPER && cpu_choice == ROCK) || (user_choice == SCISSOR && cpu_choice == PAPER)) {
        printf("You win!\n");
    } else {
        printf("I win!\n");
    }
}

```

## Defining structures

A structure is defined using the `struct` keyword, followed by the name of the structure, and a list of variables inside curly braces.
Each variable inside the structure is called a member.

```c
struct point {
    int x;
    int y;
};
```

In the example above, we defined a structure called `point` that has two members: `x` and `y`.
Note that the semicolon `;` is required at the end of the structure definition!

Similar to the definition of the `enum` type in the previous activity, the code snippet above does not create any variables, but defines a new *type* called `struct point`.
This type can be used to create variables of type `struct point`, in which we can store values for `x` and `y`:

```c
struct point p1;
p1.x = 10;
p1.y = 20;
```

The dot `.` operator is used to access the members of a structure.

### Activity 2 - Defining a structure

The folder `activity2` contains a program that asks the user to enter the current date (day, month, and year).
It uses three variables to store the day, month, and year.

Define a structure called `date` that has three members: `day`, `month`, and `year`.
Remove the three variables `day`, `month`, and `year` and replace them with a single variable of type `struct date`.
You must also change the function call to `compute_age` to pass the three members of the structure instead of the three variables.

When you're done, compile and run the program to test your changes.
Paste the contents of the modified `main.c` file below:

```c
// TODO: Paste your modified main.c file here
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


```

## Passing structures to functions

Structures, like other variables, can be passed to functions as arguments.
When passing a structure to a function, it is passed by value - a copy of the structure is made and passed to the function.
This means that changes made to the structure inside the function do not affect the original structure.
Also, copying a structure can be expensive if the structure is large.
Instead, you can pass a pointer to the structure, which is more efficient.

This means that inside the function, in order to access the members of the structure, you need to use the `->` operator instead of the `.` operator.

### Activity 3 - Passing a structure to a function

The program listed in folder `activity3` contains a structure called `coordinate` that has two members: `x` and `y`.
The program asks the user to enter two coordinates and stores them in two variables of type `coordinate`.
It then calls the function `distance` to compute the distance between the two coordinates.

The function `distance` is not implemented yet, and simply returns 0.0 for now.
Implement the function so that it computes the distance between the two coordinates passed to it.
Use the formula for the Euclidean distance between two points in a two-dimensional plane:

```
distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))
```

Use the `sqrtf` function from the `math.h` library to compute the square root of a `float`.

When you're done, compile and run the program and verify that it works correctly.
For example, the distance between the points (0, 0) and (3, 4) should be 5.0.

If your program works correctly, paste your `distance` function below:

```c
// TODO: Paste your distance function here
#include <stdio.h>
#include <math.h>
#include "functions.h"

struct coordinate {
    float x;
    float y;
};

/// @brief Computes the distance between two coordinates.
/// @param a Address of the first coordinate.
/// @param b Address of the second coordinate.
/// @return The (Euclidean) distance between the two coordinates.
float distance(const struct coordinate *a, const struct coordinate *b);

int main(void) {
    printf("Enter the first coordinate:\n");
    printf(" x-coordinate: ");
    float x1 = read_float();
    printf(" y-coordinate: ");
    float y1 = read_float();

    printf("Enter the second coordinate:\n");
    printf(" x-coordinate: ");
    float x2 = read_float();
    printf(" y-coordinate: ");
    float y2 = read_float();

    struct coordinate a = {x1, y1};
    struct coordinate b = {x2, y2};

    float dist = distance(&a, &b);

    printf("The distance between (%.2f, %.2f) and (%.2f, %.2f) is %.2f.\n", x1, y1, x2, y2, dist);
}

float distance(const struct coordinate *a, const struct coordinate *b) {
    // TODO: implement this function
    float distance = sqrt((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
    return distance;
}
```

### Activity 4 - Returning structures from functions

The program listed in folder `activity4` contains the same structure `point` as in the previous activity.
A difference with the previous program is that this program uses a function called `read_point` to read a point from the user.

Implement the function `read_point` so that it reads a point from the user and returns it.
Reuse your `distance` function of the previous activity to compute the distance between the two points.

If your program works as expected, paste the contents of the `read_point` function below:

```c
// TODO: Paste your read_point function here
#include <stdio.h>
#include <math.h>
#include "functions.h"

struct coordinate {
    float x;
    float y;
};

/// @brief Computes the distance between two coordinates.
/// @param a Address of the first coordinate.
/// @param b Address of the second coordinate.
/// @return The (Euclidean) distance between the two coordinates.
float distance(const struct coordinate *a, const struct coordinate *b);

/// @brief Reads a coordinate   from the user and returns it.
/// @return The coordinate entered by the user.
struct coordinate read_coordinate(void);    

int main(void) {
    printf("Enter the first coordinate:\n");
    struct coordinate a = read_coordinate();

    printf("Enter the second coordinate:\n");
    struct coordinate b = read_coordinate();

    float dist = distance(&a, &b);

    printf("The distance between (%.2f, %.2f) and (%.2f, %.2f) is %.2f.\n", a.x, a.y, b.x, b.y, dist);
}

float distance(const struct coordinate *a, const struct coordinate *b) {
    // TODO: implement this function
    float distance = sqrt((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
    return distance;
}

struct coordinate read_coordinate(void) {
    printf(" x-coordinate: ");
    float x = read_float();
    printf(" y-coordinate: ");
    float y = read_float();

    struct coordinate result = {x, y};
    return result;
}

```

## Arrays of structures

Just like any other variable, structures can be stored in arrays.
To create an array of structures, you simply add square brackets `[]` after the structure variable's name:

```c
struct point points[10];    // an array of 10 points
```

To access a member of a specific structure in the array, you need to combine the `[]` operator with the `.` operator:

```c
points[0].x = 10;
points[0].y = 20;
```

### Activity 5 - Using arrays of structures

The program listed in `activity5/main.c` contains a structure called `colour` that has three members, one for each of the primary colours: `red`, `green`, and `blue`.
The program asks the user to enter CSS colour codes (a six-digit hexadecimal number prefixed with a '#' character) for the three primary colours.
If the user enters a colour code of '#000000', the program stops asking for more colours.

Modify the program so that all the colour codes are stored in an array of `colour` structures.
Also, modify the program so that it prints all colour codes entered by the user using the `print_colour` function.

When you're done, compile and run the program to test your changes.
If the program works correctly and prints all the colour codes entered by the user, paste the contents of the modified `main` function below:

```c
// TODO: Paste the main function of the modified main function here
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

struct colour {
    int red;
    int green;
    int blue;
};

/// @brief Reads a colour from the user.
/// @return The colour entered by the user.
struct colour read_colour(void);

/// @brief Checks if a colour is black.
/// @param c The colour to check.
/// @return True if the colour is black, false otherwise.
bool is_black(const struct colour *c);

/// @brief Prints a colour
/// @param c The colour to print.
void print_colour(const struct colour *c);

/// @brief Parses a CSS colour string into its components.
/// @param colour 
/// @param x address of the red component
/// @param y address of the green component
/// @param z address of the blue component
/// @return True if the colour was successfully parsed, false otherwise.
bool parse_css_colour(const char *colour, int *x, int *y, int *z);

int main(void) {
    const int max_count = 10;

    struct colour colours[max_count]; //initialize an array to store color

    printf("Enter at most %d colours (#rrggbb in hex), #000000 to stop\n", max_count);

    int count = 0;
    while (count < max_count) {
        struct colour c = read_colour();
        if (is_black(&c)) break;
        colours[count] = c;
        count++;
    }

    // TODO: print all colours that were entered using print_colour
    //       you'll need to store them in an array
    printf("You've entered the following %d colours:\n", count);
    for(int i = 0; i < count; i++){
        print_colour(&colours[i]); //print each stored color
    }
    return 0;
}

int hex_to_int(char c) {
    if (isdigit(c)) return c - '0';
    return tolower(c) - 'a' + 10;
}

int hex_to_byte(const char *hex) {
    return hex_to_int(hex[0]) * 16 + hex_to_int(hex[1]);
}

bool parse_css_colour(const char *colour, int *x, int *y, int *z) {
    if (colour[0] != '#') return false;
    if (strlen(colour + 1) != 6) return false;
    for (int i = 1; i < 7; i++) if (!isxdigit(colour[i])) return false;
    *x = hex_to_byte(colour + 1);
    *y = hex_to_byte(colour + 3);
    *z = hex_to_byte(colour + 5);
    return true;
}

struct colour read_colour(void) {
    printf("Enter a valid colour (e.g., #ff00ff): ");
    char colour[9];
    struct colour result = {0, 0, 0};
    read_string(colour, sizeof(colour));
    if (!parse_css_colour(colour, &result.red, &result.green, &result.blue)) {
        printf("Invalid input!\nEnter a valid colour (e.g., #ff00ff): ");
        read_string(colour, sizeof(colour));
    }
    return result;
}

bool is_black(const struct colour *c) {
    return c->red == 0 && c->green == 0 && c->blue == 0;
}

void print_colour(const struct colour *c) {
    printf("Colour: #%02x%02x%02x (red: %.1f%%, green: %.1f%%, blue: %.1f%%)\n", c->red, c->green, c->blue, c->red / 2.55f, c->green / 2.55f, c->blue / 2.55f);
}

```

## Nested structures

Structures can contain other structures as members, either directly or indirectly (i.e. a structure can have a member that is itself an array of other structures).
Such structures are called nested structures.
For example, we could have a student structure that contains a date of birth structure:

```c
struct date {
    int day;
    int month;
    int year;
};

struct student {
    const char* name;
    struct date birthdate;
};
```

To access the members of a nested structure, you use the `.` operator (or the `->` operator) multiple times.
For example, to access the day of birth of a student, you would write:

```c
struct student s;
s.birthdate.day = 1;
```

### Activity 6 - Using nested structures

Folder `activity6` contains a program that uses a structure called `card` to represents a playing card.
It has two members: `rank` and `suit`.
It also has a structure called `deck` that represents a deck of cards and has an array of `card` structures, as well as a member `size` that stores the number of cards in the deck (typically 52, but can be less if cards are drawn from the deck).

The program shuffles a deck of cards, and asks you to draw cards until the deck is empty.
It (of course...) does not fully work, though: the drawing of the cards and the printing of the drawn cards is not implemented yet.

Implement the functions `print_deck` and `draw_cards` so that the program works as expected.

In the `print_deck` function, you should make use of the existing function `print_card` - it can be used to print a single card, which it takes as a `const` pointer argument.

To test your implementation, compile and run the program.
When you're done, paste the contents of the `print_deck` and `draw_cards` functions below:

```c
// TODO: Paste your modified print_deck function here
void print_deck(const deck_t *deck) {
    // TODO: print all cards in the deck using print_card
    for(size_t i = 0; i < deck->count; i++){
        print_card(&deck->cards[i]);
    }
}
    
```

```c
// TODO: Paste your modified draw_cards function here
int draw_cards(deck_t *target_deck, deck_t *source_deck, size_t count) {
    if (source_deck->count < count) {
        // if the source_deck doesn't have enough cards, draw all of them
        count = source_deck->count;
    }

    // TODO: remove count cards from source_deck and add them to target_deck
    //       make sure to update the count of both decks
    for(size_t i = 0; i < count; i++) {
        target_deck->cards[target_deck->count] = source_deck->cards[source_deck->count - 1 - i];
        target_deck->count++;
    }

    // Update source_deck count
    source_deck->count -= count;

    // return the number of cards actually drawn
    return count;
}
```

### Activity 7 - Strings in structures

The program listed in `activity7` contains a structure called `person` that has two members: `name` and `birthdate`.
The `name` member is a pointer to a string, which gives some issues.
Run the program and enter the name(s) of one or two persons to see what these issues are.

Solve the issues by changing the `name` member to an array of characters.
This will require you to make some changes to the program in order to make it work correctly.

When the program correctly prints the names for the persons that were entered, paste the contents of the modified `main.c` file below:

```c
// TODO: Paste your modified main.c file here
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
```

## Sign offw3e45

To sign off this tutorial, you will need to have done the following:

* You have answered all questions in the markdown file, and all programs you've created compile and run without errors.
* You converted the markdown file to HTML, and submitted it at the correct submit point in Brightspace.

Your lab teacher will mark the tutorial as completed in Brightspace.
In case there are issues with your programs or answers, your lab teacher will mark it with 0 points in Brightspace.
If you receive 0 points, make sure to check the feedback, make the necessary changes, and resubmit the tutorial.
Do this before the end of week 2.9, as this is the deadline for having submitted all tutorials and assignments.

