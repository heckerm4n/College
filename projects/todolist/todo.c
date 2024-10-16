#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define MAX_TASKS 100
#define TASK_LENGTH 256

// Colors and screen control
#define COLOR_BG "\033[38;5;157m"  // Background color #32a983
#define COLOR_FG "\033[38;2;50;169;131m"  // Foreground color #32a983
#define COLOR_RESET "\033[0m"
#define COLOR_HIGHLIGHT "\033[38;2;255;255;255m\033[48;2;0;0;0m" // White on Black highlight

// Task structure
typedef struct {
    char task[TASK_LENGTH];
    int completed;
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;
int cursor = 0;
int editing = 0;

// Function to get terminal width
int get_terminal_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;  // Return the number of columns
}



void render_screen() {
    printf("\033[H\033[J"); // Clear the screen

    int width = get_terminal_width();  // Get terminal width
    width = (width < 50) ? 50 : width; // Ensure minimum width

    const char* title = "Todo List";
    int title_len = strlen(title);
    int padding = (width - 2 - title_len) / 2;  // Calculate padding for title

    // Top border (generate the correct number of dashes based on terminal width)
    printf(COLOR_BG "╭");
    for (int i = 0; i < width - 2; i++) {
        printf("─");
    }
    printf("╮\n");

    // Empty row
    printf(COLOR_BG "│%*s│\n", width - 2, " ");

    // Centered title
    printf(COLOR_BG "│%*s%s%*s│\n", padding, " ", title, (width - 2 - padding - title_len), " "); 

    // Empty row
    printf(COLOR_BG "│%*s│\n", width - 2, " ");

    // Bottom border (generate the correct number of dashes based on terminal width)
    printf(COLOR_BG "╰");
    for (int i = 0; i < width - 2; i++) {
        printf("─");
    }
    printf("╯\n" COLOR_RESET);

    // Render tasks
    for (int i = 0; i < task_count; i++) {
        if (i == cursor) {
            printf(COLOR_HIGHLIGHT);
        }

        printf("[%c] %s\n", tasks[i].completed ? 'x' : ' ', tasks[i].task);

        if (i == cursor) {
            printf(COLOR_RESET);
        }
    }

    printf("\nPress 'i' to edit, 'o' to add new task, 'Tab' to mark as complete, 'Esc' to exit edit mode.\n");
    printf("Use ':w' to save, ':q' to quit.\n");
}

// Disable canonical mode and echo for terminal
void enable_raw_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Restore terminal to normal mode
void disable_raw_mode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}


int main() {
    //load_from_file();  // Load existing tasks

    enable_raw_mode();  // Enter raw mode for key handling

    while (1) {
        render_screen();
        //handle_input();
    }

    disable_raw_mode();  // Exit raw mode when done

    return 0;
}

