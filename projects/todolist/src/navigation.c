#include <ncurses.h>
#include "navigation.h"
#include "calendar.h"
#include "todo_list.h"

static int focus = 0; // 0: calendar, 1: todo list
static int selected_date; // Add this line

void handle_navigation() {
    int ch = getch();
    switch(ch) {
        case 'h':
            if (focus == 0) select_date(selected_date - 1);
            break;
        case 'l':
            if (focus == 0) select_date(selected_date + 1);
            break;
        case 'j':
            if (focus == 0) select_date(selected_date + 7);
            break;
        case 'k':
            if (focus == 0) select_date(selected_date - 7);
            break;
        case 9: // Tab
            focus = 1; // Switch to todo list
            break;
        case 353: // Shift+Tab
            focus = 0; // Switch to calendar
            break;
        case 'a':
            if (focus == 1) {
                // Add new task
                // You'll need to implement a way to get user input for the new task
            }
            break;
        case 'm':
            if (focus == 1) {
                // Mark task as complete
                // You'll need to implement a way to select which task to mark
            }
            break;
        case 'e':
            if (focus == 0) {
                // Add/Edit event for selected date
                // You'll need to implement a way to get user input for the event details
            }
            break;
    }
}

