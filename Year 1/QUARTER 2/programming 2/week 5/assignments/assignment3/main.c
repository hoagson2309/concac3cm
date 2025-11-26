#include <stdio.h>
#include "functions.h"

/// @brief A structure representing a user with a username and password.
typedef struct {
    char *username;
    char *password;
} user_t;

/// @brief Checks if a username is valid.
/// @param username The username to check.
/// @return `true` if the username is valid, `false` otherwise.
bool is_valid_username(const char *username);

/// @brief Extracts the username and password from a line of text.
/// @param line The line of text to extract the username and password from.
/// @param user The user to store the username and password in.
/// @return `true` if a valid username and password were extracted successfully, `false` otherwise.
bool extract_user(const char *line, user_t *user);

int main(void) {
    // NOTE: this program can only be built on Linux or Mac OS X because it is linked with an address sanitizer

    // TODO:
    //   - open the file "users.txt" and read it line by line
    //   - convert each line to a user_t structure, if it is valid
    //   - if it is not valid, print an error message and stop
    //   - Ask the user for a username and password
    //   - Check if the username and password match any of the users in the file
    //   - If it does, print "Welcome, <usernme>"
    //   - If it does not, ask the user to try again
    //   - Free any memory that was allocated
}

