#include <ncurses.h>
#include <stdio.h>  // Add this line
#include "calendar.h"
#include "todo_list.h"
#include "progress_bar.h"
#include "navigation.h"
#include "utils.h"

int main() {
    printf("Starting program...\n");  // Add this line
    initscr();  // Initialize ncurses
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        return 1;
    }
    start_color();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    // Initialize windows and data structures
    init_calendar();
    init_todo_list();
    init_progress_bar();

    // Initialize color pairs
    init_color_pairs();

    printf("Entering main loop...\n");  // Add this line
    // Main loop
    while (1) {
        clear_screen();
        render_calendar();
        render_todo_list();
        render_progress_bar(get_progress());
        handle_navigation();
        refresh();
        // Add a small delay to reduce CPU usage
        napms(50);
    }

    endwin(); // Close ncurses
    return 0;
}

