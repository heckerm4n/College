#include <ncurses.h>
#include <string.h>
#include "calendar.h"
#include "utils.h"

#define MAX_EVENTS 100

typedef struct {
    int day;
    char description[100];
    int performance; // 0: bad, 1: ok, 2: good
} Event;

static Event events[MAX_EVENTS];
static int event_count = 0;
static int selected_date = 1;

void init_calendar() {
    // Initialize calendar data structures
}

void render_calendar() {
    WINDOW *cal_win = newwin(15, 30, 1, 1);
    box(cal_win, 0, 0);
    mvwprintw(cal_win, 0, 1, " Calendar ");
    mvwprintw(cal_win, 7, 10, "Test Calendar");  // Add this line
    wrefresh(cal_win);  // Make sure to refresh the window
}

void add_event(int day, const char *description, int performance) {
    if (event_count < MAX_EVENTS) {
        events[event_count].day = day;
        strncpy(events[event_count].description, description, 99);
        events[event_count].performance = performance;
        event_count++;
    }
}

void select_date(int date) {
    selected_date = date;
}

const char* get_event_description(int date) {
    for (int i = 0; i < event_count; i++) {
        if (events[i].day == date) {
            return events[i].description;
        }
    }
    return NULL;
}

