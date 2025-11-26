// These directives ensure that the contents of this file are included only once, even
// if the file is included multiple times
#ifndef GAME_H
#define GAME_H

// TODO: list your prototypes here

/// @brief shuffles an array of integers by swapping two random elements multiple times
/// @param values the array of integers to shuffle
/// @param size the number of elements in the array
/// @param how_many_times the number of times to swap two random elements
void shuffle(int values[], int size, int how_many_times);

/// @brief swaps two elements in an array
/// @param values the array of integers
/// @param index1 the index of the first element to swap
/// @param index2 the index of the second element to swap
void swap_elements(int values[], int index1, int index2);

/// @brief count how many element is false (facing down)
/// @param values the array of bools
/// @param size the number of elements in the array
/// @return the number of false elements
int count_false(const bool values[], int size);

/// @brief ask user to choose a face down card using its index
/// @param values array of bools
/// @param size size of the array
/// @return the index of the selected card
int select_face_down_card(const bool values[], int size);

/// @brief printing out the cards and its indices
/// @param cards array of intergers
/// @param face_up array of bools
/// @param size the number of elements in both arrays
void print_cards(const int cards[], const bool face_up[], int size);



#endif  // GAME_H