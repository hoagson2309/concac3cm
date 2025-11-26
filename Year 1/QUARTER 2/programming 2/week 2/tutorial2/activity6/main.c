#include <ncurses.h>
#include <string.h>
#include "functions.h"

#ifndef MIN_LENGTH
#define MIN_LENGTH 20
#endif

#define MAX_LENGTH 200

#define TIMEOUT 80

/// @brief Sets a random character in a string.
/// @param string The string to modify.
/// @param size The size of the string.
/// @param value The character to overwrite the string with.
void set_random(char *string, int size, char value);

/// @brief Checks if a string contains only a specific character.
/// @param string The string to check.
/// @param value The character to check for.
/// @return True if the string contains only the character, false otherwise.
bool contains_only(const char *string, char value);

/// @brief Reads a string with a minimum size from the user.
/// @param string The string to store the input.
/// @param minsize The minimum size of the string.
/// @param bufsize The size of the string buffer.
void read_input_string(char *string, size_t minsize, int bufsize);

int main(void) {
    char string[MAX_LENGTH];
    read_input_string(string, MIN_LENGTH, sizeof(string));
    int length = strlen(string);

    // initialize ncurses
    initscr();
    
    // get the screen size
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    // hide the cursor
    curs_set(0);

    // disable echo
    noecho();

    // set the timeout for getch
    timeout(TIMEOUT);

    while (getch() == ERR && !contains_only(string, '*')) {
        set_random(string, length, '*');
        // print the string in the middle of the screen
        mvprintw(rows / 2, (cols - length) / 2, "%s", string);
        refresh();
    }

    // wait for a key press 10 more times to let some time elapse
    for (int i = 0; i < 10; i++) getch();

    // end ncurses
    endwin();
    return 0;
}

void set_random(char *string, int size, char value) {
    string[random_int(0, size - 1)] = value;
}

bool contains_only(const char *string, char value) {
    while (*string != '\0') {
        if (*string != value) {
            return false;
        }
        string++;
    }
    return true;
}

void read_input_string(char *string, size_t minsize, int bufsize) {
    printf("Enter a string of at least %zu characters: ", minsize);
    read_string(string, bufsize);
    while (strlen(string) < minsize) {
        printf("The string must be at least %zu characters long, yours is %zu.\n", minsize, strlen(string));
        printf("Enter a string of at least %zu characters: ", minsize);
        read_string(string, bufsize);
    }
}

