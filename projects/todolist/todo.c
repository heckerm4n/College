#include <ncurses.h>
#include <string.h>

void print_menu(WINDOW *menu_win, int highlight, const char *choices[], int n_choices);

int main() {
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    const char *choices[] = {
        "Say Hello to Everyone",
        "Send Weekly Report to Kalle",
        "Ask Daniel about the interview last Friday",
        "Try Max Plantbeef Burger"
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    // Initialize ncurses
    initscr();
    clear();
    noecho();
    cbreak();
    start_color();

    // Create window for menu
    int height = 10, width = 40;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;
    menu_win = newwin(height, width, start_y, start_x);
    keypad(menu_win, TRUE);

    // Print instructions
    mvprintw(0, 0, "Use arrow keys to move, Enter to select a task:");
    refresh();

    // Loop to handle user input
    while (1) {
        print_menu(menu_win, highlight, choices, n_choices);
        c = wgetch(menu_win);

        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:  // Enter key
                choice = highlight;
                break;
            default:
                mvprintw(24, 0, "Invalid key: %d", c);
                refresh();
                break;
        }
        if (choice != 0)  // If Enter is pressed, break out
            break;
    }

    // Print the selected choice
    mvprintw(23, 0, "You selected: %s", choices[choice - 1]);
    clrtoeol();
    refresh();

    getch();
    endwin();
    return 0;
}

void print_menu(WINDOW *menu_win, int highlight, const char *choices[], int n_choices) {
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {  // Highlight current item
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(menu_win);
}

