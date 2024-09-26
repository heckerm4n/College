#ifndef CALENDAR_H
#define CALENDAR_H

void init_calendar();
void render_calendar();
void select_date(int date);
void add_event(int day, const char *description, int performance);  // Add this line
const char* get_event_description(int date);  // Add this line

#endif

