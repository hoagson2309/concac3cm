#include <ncurses.h>
#include "functions.h"
#include "game.h"

int adjacent_bomb_count(const bool *bombs, int nrows, int ncols, int row, int column) {
    int count = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            int adj_row = row + dr, adj_col = column + dc;
            if (adj_row < 0 || adj_row >= nrows || adj_col < 0 || adj_col >= ncols) continue;
            if (bombs[adj_row * ncols + adj_col]) {
                count++;
            }
        }
    }
    return count;
}

void init_game(bool *bombs, int nrows, int ncols, int num_bombs) {
    for (int i = 0; i < num_bombs; i++) bombs[i] = true; // place bomb

    // shuffle the array to distribute the bombs randomly
    shuffle(bombs, nrows * ncols, sizeof(bool));
}

bool has_bomb(const bool *bombs, int nrows, int ncols, int row, int col) {
    return bombs[row * ncols + col];
}

void get_pos_from_index(int pos, int ncols, int *row, int *col) {
    *row = pos / ncols;
    *col = pos % ncols;
}

int reveal(const bool *bombs, const bool *flags, bool *revealed, int nrows, int ncols, int row, int col) {
    if (has_bomb(bombs, nrows, ncols, row, col)) {
        // game over
        return -1;
    }
    else {
        // reveal all adjacent cells that have no adjacent bombs
        int queue[WIDTH * HEIGHT] = {row * ncols + col};
        int num_queued = 1;
        int num_revealed = 0;
        while (num_queued > 0) {
            int r, c;
            get_pos_from_index(queue[num_queued - 1], ncols, &r, &c);
            revealed[r * ncols + c] = true;
            num_revealed++;
            if (adjacent_bomb_count(bombs, nrows, ncols, r, c) == 0) {
                // cell was revealed, try to reveal adjacent cells as well
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        if (dr != 0 && dc != 0) continue;
                        int adj_row = r + dr, adj_col = c + dc;
                        if (adj_row < 0 || adj_row >= nrows || adj_col < 0 || adj_col >= ncols) continue;

                        int adj_pos = adj_row * ncols + adj_col;
                        if (!revealed[adj_pos] && !bombs[adj_pos] && !flags[adj_pos]) {
                            queue[num_queued++] = adj_pos;   // add to queue
                            goto outer;
                        }
                    }
                }
                num_queued--;   // pop the current position
                outer:
            }
            else {
                num_queued--;
            }
        }
        return num_revealed;
    }
}

void toggle_flag(bool *flags, int nrows, int ncols, int row, int col) {
    flags[row * ncols + col] = !flags[row * ncols + col];
}

char get_character(const bool *bombs, const bool *flags, const bool *revealed, int nrows, int ncols, int row, int col) {
    if (flags[row * ncols + col]) {
        return 'F';
    }
    else if (revealed[row * ncols + col]) {
        if (bombs[row * ncols + col]) {
            return '@';
        }
        else {
            int count = adjacent_bomb_count(bombs, nrows, ncols, row, col);
            if (count == 0) return ' ';
            else return '0' + count;
        }
    }
    else {
        return '.';
    }
}

void init_info(WINDOW *win, int height, int width, int revealed, int num_bombs) {
    mvwprintw(win, 0, 2, "Minesweeper!");
    mvwprintw(win, 2, 2, "Find all bombs by flagging them!");
    mvwprintw(win, 3, 2, "Press F to flag, space to explore, q to quit");
    mvwprintw(win, 4, 2, "Numbers (max 8) indicate nr. of adjacent bombs");
    mvwprintw(win, 6, 2, "Revealed cells: %d, %d to go", revealed, width * height - revealed - num_bombs);
    wrefresh(win);
}

int count_true(const bool *bools, int size) {
    int result = 0;
    for (int i = 0; i < size; ++i) if (bools[i]) result++;
    return result;
}

void set_true(bool *bools, int size) {
    for (int i = 0; i < size; ++i) bools[i] = true;
}

void print_game(WINDOW *win, const bool *bombs, const bool *flags, const bool* revealed, int height, int width) {
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            mvwaddch(win, r + 1, c + 1, get_character(bombs, flags, revealed, height, width, r, c));
        }
    }
}

bool matches(const bool* xs, const bool *ys, int size) {
    for (int i = 0; i < size; ++i) {
        if (xs[i] != ys[i]) return false;
    }
    return true;
}
