#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define MAX_TASKS 100
#define TASK_LENGTH 256

// Colors and screen control
#define COLOR_BG "\033[48;2;50;169;131m"  // Background color #32a983
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

void save_to_file() {
    FILE *file = fopen("todolist.txt", "w");
    if (!file) {
        perror("Could not open file");
        return;
    }
    
    for (int i = 0; i < task_count; i++) {
        fprintf(file, "[%c] %s\n", tasks[i].completed ? 'x' : ' ', tasks[i].task);
    }
    
    fclose(file);
    printf("Tasks saved to 'todolist.txt'.\n");
}

void load_from_file() {
    FILE *file = fopen("todolist.txt", "r");
    if (!file) {
        printf("No existing todo list found.\n");
        return;
    }

    char line[TASK_LENGTH + 5];
    while (fgets(line, sizeof(line), file)) {
        char status;
        sscanf(line, "[%c] %[^\n]", &status, tasks[task_count].task);
        tasks[task_count].completed = (status == 'x') ? 1 : 0;
        task_count++;
    }
    
    fclose(file);
}

void render_screen() {
    printf("\033[H\033[J"); // Clear the screen

    int width = get_terminal_width();  // Get terminal width
    width = (width < 50) ? 50 : width; // Ensure minimum width

    printf(COLOR_BG "╭%.*s╮\n", width - 2, "──────────────────────────────────────────────");
    printf(COLOR_BG "│%*s│\n", width - 2, "                                              ");
    printf(COLOR_BG "│%*s│\n", (width - 2) / 2 + 10, "      Todo List      ");
    printf(COLOR_BG "│%*s│\n", width - 2, "                                              ");
    printf(COLOR_BG "╰%.*s╯\n" COLOR_RESET, width - 2, "──────────────────────────────────────────────");

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

void add_task() {
    if (task_count >= MAX_TASKS) {
        printf("Max tasks reached!\n");
        return;
    }
    printf("Enter new task: ");
    fgets(tasks[task_count].task, TASK_LENGTH, stdin);
    tasks[task_count].task[strcspn(tasks[task_count].task, "\n")] = '\0'; // Remove newline
    tasks[task_count].completed = 0;
    task_count++;
}

void edit_task() {
    printf("Editing task: ");
    fgets(tasks[cursor].task, TASK_LENGTH, stdin);
    tasks[cursor].task[strcspn(tasks[cursor].task, "\n")] = '\0'; // Remove newline
}

void mark_task_complete() {
    tasks[cursor].completed = !tasks[cursor].completed;
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

int handle_vim_commands() {
    char cmd[10];
    int index = 0;
    char ch;

    while ((ch = getchar()) != '\n') {
        cmd[index++] = ch;
    }
    cmd[index] = '\0';

    if (strcmp(cmd, ":q") == 0) {
        return 1;  // Quit
    } else if (strcmp(cmd, ":w") == 0) {
        save_to_file();
    }

    return 0;
}

void handle_input() {
    char ch = getchar();

    if (ch == ':') {
        if (handle_vim_commands()) {
            disable_raw_mode();
            exit(0);  // Quit program
        }
    }

    if (editing) {
        if (ch == 27) {  // Esc to exit edit mode
            editing = 0;
        }
    } else {
        switch (ch) {
            case 'i':  // Enter edit mode
                editing = 1;
                edit_task();
                break;
            case 'o':  // Add new task
                add_task();
                break;
            case '\t':  // Tab to mark task complete
                mark_task_complete();
                break;
            case 27:  // Esc to exit
                editing = 0;
                break;
            case 'j':  // Move down
                if (cursor < task_count - 1) cursor++;
                break;
            case 'k':  // Move up
                if (cursor > 0) cursor--;
                break;
        }
    }
}

int main() {
    load_from_file();  // Load existing tasks

    enable_raw_mode();  // Enter raw mode for key handling

    while (1) {
        render_screen();
        handle_input();
    }

    disable_raw_mode();  // Exit raw mode when done

    return 0;
}

