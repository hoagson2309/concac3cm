#ifndef REVERSE_H
#define REVERSE_H

/// @brief Advances a char-pointer by skipping all the white spaces in the string
/// @param str the string to apply this function to
/// @return a pointer to the first non-whitespace character in the string (could be the null terminator)
char *skip_whitespace(char *str);

/// @brief Finds the first whitespace character in the string
/// @param str the string to apply this function to
/// @return a pointer to the first whitespace character in the string (could be the null terminator)
char *end_of_word(char *str);

/// @brief Reverses the characters in the range [start, end)
/// @param start points to the first character in the range
/// @param end points to the first character after the end of the range
void reverse(char *start, char *end);

/// @brief Reverses all the words in a sentence.
///      A word is defined as a sequence of non-whitespace characters.
/// @param sentence the sentence to reverse
void reverse_words(char *sentence);

#endif // REVERSE_H