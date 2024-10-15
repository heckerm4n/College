#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define ROWS 6
#define COLS 7
#define MAX_TASKS 10
#define TASK_SIZE 100

int month[ROWS][COLS];
int events[31];
int day, monthIndex, year;

char tasks[31][MAX_TASKS][TASK_SIZE];  // Tasks for each day

int getDaysInMonth(int month, int year) {
    switch (month) {
        case 4: case 6: case 9: case 11: return 30;
        case 2:
            return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        default: return 31;
    }
}
// raw modfe is to enable user toi navigate in calendar without pressing enter
void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
// to disable it so that we have to press enter for any thing to register in terminal
void disableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void printBorder(int width, int type) {
    if (type == 0) {
        printf("┌");
        for (int i = 0; i < width; i++) {
            printf("─");
        }
        printf("┐\n");
    } else if (type == 1) {
        printf("├");
        for (int i = 0; i < width; i++) {
            printf("─");
        }
        printf("┤\n");
    } else {
        printf("└");
        for (int i = 0; i < width; i++) {
            printf("─");
        }
        printf("┘\n");
    }
}

void printCalendar(int day, int monthIndex, int year) {
    int daysInMonth = getDaysInMonth(monthIndex + 1, year);
    int dayOfWeek = 0; 
    printf("\033[H\033[J"); // Clear screen

    printf(" Calendar for %02d/%d\n", monthIndex + 1, year);
    printBorder(34, 0); // Top border

 
    printf("\033[38;5;157m");
    printf("│ %-2s │ %-2s │ %-2s │ %-2s │ %-2s │ %-2s │ %-2s │\n",
           "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa");
    printf("\033[0m"); // Reset color

    printBorder(34, 1); // Separator border

    int date = 1;
    for (int row = 0; row < ROWS; row++) {
        printf("│");
        for (int col = 0; col < COLS; col++) {
            if (date <= daysInMonth && (row > 0 || col >= dayOfWeek)) {
                if (row % 2 == 1) {
                    printf("\033[38;5;157m");
                }

                if (date == day) {
                    printf("\033[7m %2d \033[0m│", date); // ansi character to inverse colors
                } else if (events[date - 1]) {
                    printf("*%2d │", date); 
                } else {
                    printf(" %2d │", date);
                }
                printf("\033[0m");
                date++;
            } else {
                printf("    │"); 
            }
        }
        printf("\n");
    }

    printBorder(34, 2); 

    // Display the todo list for the selected day
    printf(" Todo List for %02d/%02d/%d:\n", day, monthIndex + 1, year);
    for (int i = 0; i < MAX_TASKS && tasks[day - 1][i][0] != '\0'; i++) {
        printf("%d. %s\n", i + 1, tasks[day - 1][i]);
    }
    printf("\n");
}


void loadTasks() {
    FILE *file = fopen("todolist.txt", "r");
    if (!file) return;

    int fileDay, fileMonth, fileYear;
    char buffer[TASK_SIZE];
    while (fscanf(file, "%d/%d/%d", &fileDay, &fileMonth, &fileYear) == 3) {
        int taskIndex = 0;
        fgetc(file); 
        while (fgets(buffer, TASK_SIZE, file)) {
            if (buffer[0] == '\n') break;
            strcpy(tasks[fileDay - 1][taskIndex++], buffer);
        }
    }
    fclose(file);
}

void saveTasks() {
    FILE *file = fopen("todolist.txt", "w");
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < MAX_TASKS && tasks[i][j][0] != '\0'; j++) {
            fprintf(file, "%02d/%02d/%d\n", i + 1, monthIndex + 1, year);
            fprintf(file, "%s", tasks[i][j]);
            fprintf(file, "\n");
        }
    }
    fclose(file);
}

void editTodoList() {
    printf("\033[H\033[J");  // Clear screen ansi cha
    printf("Edit Todo List for %02d/%02d/%d:\n", day, monthIndex + 1, year);

    char newTask[TASK_SIZE];
    int taskIndex = 0;

    // Display current tasks
    for (int i = 0; i < MAX_TASKS && tasks[day - 1][i][0] != '\0'; i++) {
        printf("%d. %s", i + 1, tasks[day - 1][i]);
        taskIndex++;
    }

    // Add new tasks
    printf("\nEnter new tasks (leave empty to stop):\n");
    while (taskIndex < MAX_TASKS) {
        printf("%d: ", taskIndex + 1);
        fgets(newTask, TASK_SIZE, stdin);
        if (newTask[0] == '\n') break;
        strcpy(tasks[day - 1][taskIndex++], newTask);

    }
    saveTasks();
}

void navigateCalendar() {
    char key;
    int daysInMonth = getDaysInMonth(monthIndex + 1, year);

    enableRawMode();

    while (1) {
        printCalendar(day, monthIndex, year);

        key = getchar();

        switch (key) {
            case 'h':
                if (day > 1) day--;
                break;
            case 'l':
                if (day < daysInMonth) day++;
                break;
            case 'j':
                if (day + 7 <= daysInMonth) day += 7;
                else day = daysInMonth;
                break;
            case 'k':
                if (day - 7 > 0) day -= 7;
                else day = 1;
                break;
            case '\t': 
                events[day - 1] = !events[day - 1];
                break;
            case '\n': 
                disableRawMode();  
                editTodoList();
                enableRawMode(); 
                break;
            case 'q':
                disableRawMode();
                return;
            default:
                break;
        }
    }
}

void initializeWithCurrentDate() {
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);

    day = currentTime->tm_mday;
    monthIndex = currentTime->tm_mon;
    year = currentTime->tm_year + 1900;
}

int main() {
    memset(tasks, 0, sizeof(tasks)); 
    loadTasks();  

    initializeWithCurrentDate();
    navigateCalendar();

    return 0;
}

