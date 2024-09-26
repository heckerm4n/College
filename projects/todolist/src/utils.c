#include <ncurses.h>
#include <string.h>  // Add this line
#include "utils.h"

void clear_screen() {
    clear();
}

void center_print(WINDOW *win, int start_y, int start_x, int width, const char *str) {
    int length = strlen(str);
    int x = start_x + (width - length) / 2;
    mvwprintw(win, start_y, x, "%s", str);
}

void init_color_pairs() {
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
}

