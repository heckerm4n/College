#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>

void clear_screen();  // Utility function to clear the screen
void center_print(WINDOW *win, int start_y, int start_x, int width, const char *str);  // Center text in a window
void init_color_pairs();  // Add this line

#endif

