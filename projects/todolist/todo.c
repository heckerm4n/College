#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define ROWS 6
#define COLS 7

int month[ROWS][COLS]; 
int events[31];       
int day, monthIndex, year; 

int getDaysInMonth(int month, int year) {
    switch (month) {
        case 4: case 6: case 9: case 11: return 30;  // April, June, September, November
        case 2:  // February (leap year check)
            return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        default: return 31;  // All other months
    }
}

// Disable canonical mode and echo for reading single characters
void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Restore terminal settings
void disableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void printBorder(int width) {
    for (int i = 0; i < width; i++) {
        printf("-");
    }
    printf("\n");
}

// Function to print the calendar 
void printCalendar(int day, int monthIndex, int year) {
    int daysInMonth = getDaysInMonth(monthIndex + 1, year);
    int dayOfWeek = 0; 
    printf("\033[H\033[J");

    printf(" Calendar for %d/%d\n", monthIndex + 1, year);
    printBorder(37);
    
    printf("| %-3s | %-2s | %-2s | %-2s | %-2s | %-2s | %-2s |\n", 
           "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa");
    printBorder(37);

    int date = 1;
    for (int row = 0; row < ROWS; row++) {
        printf("| ");
        for (int col = 0; col < COLS; col++) {
            if (date <= daysInMonth && (row > 0 || col >= dayOfWeek)) {
                if (row % 2 == 1) {
                    printf("\033[38;5;157m");
                }

                if (date == day) {
                    printf("\033[7m %2d \033[0m|", date);  // Inverse color for the selected day
                } else if (events[date - 1]) {
                    printf("*%2d |", date);  // Marked event
                } else {
                    printf(" %2d |", date);  // Regular day
                }
                printf("\033[0m");
                date++;
            } else {
                printf("    |"); 
            }
        }
        printf("\n");
    }
    printBorder(37);
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
            case 'm':  // Mark/unmark event
                events[day - 1] = !events[day - 1];
                break;
            case 'q':  
                disableRawMode();  // Restore terminal settings
                return;
            default:
                break;
        }
    }
}

// Get the current system date
void initializeWithCurrentDate() {
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);

    day = currentTime->tm_mday;           // Get current day
    monthIndex = currentTime->tm_mon;     // Get current month (0-11)
    year = currentTime->tm_year + 1900;   // Get current year (since 1900)
}

int main() {

    // Initialize the event array to 0 (no events)
    for (int i = 0; i < 31; i++) {
        events[i] = 0;
    }

    initializeWithCurrentDate();

    navigateCalendar();

    return 0;
}
