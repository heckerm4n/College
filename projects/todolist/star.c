#include <stdio.h>
#include <string.h>

#define MAX_TASKS 5      // Maximum number of tasks per day
#define MAX_DAYS 10      // Maximum number of days in the hashmap

// Structure for representing a day
typedef struct {
    int day;
    int month;
    int year;
} Day;

// Structure for holding tasks for a day
typedef struct {
    Day date;
    char tasks[MAX_TASKS][100];  // List of tasks (max 5 tasks of max 100 characters)
    int task_count;
} DayTasks;

// Hashmap-like array to store tasks for different days
DayTasks hashmap[MAX_DAYS];
int day_count = 0;  // Number of days in the hashmap

// Function to compare two days
int compare_days(Day d1, Day d2) {
    return (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year);
}

// Function to add a task for a given day
void add_task(Day d, const char *task) {
    // Check if the day already exists
    for (int i = 0; i < day_count; i++) {
        if (compare_days(hashmap[i].date, d)) {
            if (hashmap[i].task_count < MAX_TASKS) {
                strcpy(hashmap[i].tasks[hashmap[i].task_count], task);
                hashmap[i].task_count++;
            } else {
                printf("Task list is full for %d/%d/%d\n", d.day, d.month, d.year);
            }
            return;
        }
    }
    
    // If day not found, add a new day
    if (day_count < MAX_DAYS) {
        hashmap[day_count].date = d;
        strcpy(hashmap[day_count].tasks[0], task);
        hashmap[day_count].task_count = 1;
        day_count++;
    } else {
        printf("Hashmap is full, cannot add new day\n");
    }
}

// Function to print tasks for a given day
void print_tasks(Day d) {
    for (int i = 0; i < day_count; i++) {
        if (compare_days(hashmap[i].date, d)) {
            printf("Tasks for %d/%d/%d:\n", d.day, d.month, d.year);
            for (int j = 0; j < hashmap[i].task_count; j++) {
                printf("- %s\n", hashmap[i].tasks[j]);
            }
            return;
        }
    }
    printf("No tasks found for %d/%d/%d\n", d.day, d.month, d.year);
}

int main() {
    Day day1 = {16, 10, 2024};
    Day day2 = {17, 10, 2024};

    add_task(day1, "Complete C project");
    add_task(day1, "Prepare for exam");
    add_task(day2, "Team meeting");

    print_tasks(day1);
    print_tasks(day2);

    return 0;
}

