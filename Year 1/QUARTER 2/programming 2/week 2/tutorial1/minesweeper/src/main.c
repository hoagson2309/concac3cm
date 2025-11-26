#include <curses.h>
#include "functions.h"
#include "game.h"

int main(void) {
    bool bombs[WIDTH * HEIGHT] = {false};
    bool flags[WIDTH * HEIGHT] = {false};
    bool revealed[WIDTH * HEIGHT] = {false};

    const int width = WIDTH;
    const int height = HEIGHT;
    const int num_bombs = NUM_BOMBS;
    bool game_over = false;

    init_game(bombs, height, width, num_bombs);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    curs_set(0);

    WINDOW *win = newwin(height + 2, width + 2, 2, 2);
    WINDOW *info_win = newwin(8, 50, 5, 10 + width + 4);
    refresh();

    box(win, 0, 0);
    wrefresh(win);

    box(info_win, 0, 0);
    wrefresh(info_win);

    int revealed_count = 0;

    init_info(info_win, height, width, revealed_count, num_bombs);

    int row = height / 2, col = width / 2;
    wrefresh(win);

    keypad(win, true);
    curs_set(0);
    print_game(win, bombs, flags, revealed, height, width);
    mvwaddch(win, row, col, 'X');

    int c = wgetch(win);
    while (c != 'q') {
        // replace X with old character
        mvwaddch(win, row, col, get_character(bombs, flags, revealed, height, width, row - 1, col - 1));

        if (c == KEY_UP) row = max(1, row - 1);
        else if (c == KEY_DOWN) row = min(height, row + 1);
        else if (c == KEY_LEFT) col = max(1, col - 1);
        else if (c == KEY_RIGHT) col = min(width, col + 1);
        else if (c == 'f' || c == 'F' && !game_over) {
            toggle_flag(flags, height, width, row - 1, col - 1);
        }
        else if (c == ' ' && !game_over) {
            int result = reveal(bombs, flags, revealed, height, width, row - 1, col - 1);
            if (result == -1) {
                mvwprintw(win, 0, 2, "Game over!");
                set_true(revealed, width * height);
                for (int i = 0; i < width * height; ++i) revealed[i] = true;
                game_over = true;
                wrefresh(win);
                wgetch(win);
            }
            else if (matches(flags, bombs, width * height)) {
                mvwprintw(info_win, 0, 2, "YOU WON!");
            }
        }

        print_game(win, bombs, flags, revealed, height, width);
        init_info(info_win, height, width, revealed_count, num_bombs);
        mvwaddch(win, row, col, 'X');
        wrefresh(win);
        c = wgetch(win);
    }

    delwin(win);
    endwin();
    return 0;
}