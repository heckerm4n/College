#include <ncurses.h>
#include "progress_bar.h"

void init_progress_bar() {
    // Initialize progress bar settings
}

void render_progress_bar(int progress) {
    WINDOW *bar_win = newwin(3, 62, 17, 1);
    box(bar_win, 0, 0);
    mvwprintw(bar_win, 0, 1, " Progress ");

    int bar_width = 58;
    int filled_width = (progress * bar_width) / 100;

    for (int i = 0; i < bar_width; i++) {
        if (i < filled_width) {
            wattron(bar_win, COLOR_PAIR(progress < 50 ? 1 : (progress < 80 ? 2 : 3)));
            mvwaddch(bar_win, 1, i + 2, '|');
            wattroff(bar_win, COLOR_PAIR(progress < 50 ? 1 : (progress < 80 ? 2 : 3)));
        } else {
            mvwaddch(bar_win, 1, i + 2, ' ');
        }
    }

    mvwprintw(bar_win, 1, bar_width + 3, "%3d%%", progress);
    wrefresh(bar_win);
}

