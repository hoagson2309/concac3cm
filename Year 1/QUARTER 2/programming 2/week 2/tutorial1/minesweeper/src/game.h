#ifndef GAME_H
#define GAME_H

#define WIDTH 30
#define HEIGHT 16
#define NUM_BOMBS 60

/// @brief Counts the number of bombs in adjacent (including diagonal) positions
/// @param bombs array with bombs
/// @param nrows number of rows
/// @param ncols number of columns
/// @param row
/// @param column 
/// @return number of bombs
int adjacent_bomb_count(const bool *bombs, int nrows, int ncols, int row, int column);

void init_game(bool *bombs, int nrows, int ncols, int num_bombs);

bool has_bomb(const bool *bombs, int nrows, int ncols, int row, int col);

void get_pos_from_index(int pos, int ncols, int *row, int *col);

int reveal(const bool *bombs, const bool *flags, bool *revealed, int nrows, int ncols, int row, int col);

void toggle_flag(bool *flags, int nrows, int ncols, int row, int col);

char get_character(const bool *bombs, const bool *flags, const bool *revealed, int nrows, int ncols, int row, int col);

void init_info(WINDOW *win, int height, int width, int revealed, int num_bombs);

int count_true(const bool *bools, int size);

void set_true(bool *bools, int size);

bool matches(const bool* xs, const bool *ys, int size);

void print_game(WINDOW *win, const bool *bombs, const bool *flags, const bool* revealed, int height, int width);


#endif