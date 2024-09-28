#include <ncurses.h>
#include <string.h>
#include "todo_list.h"
#include "utils.h"

#define MAX_TASKS 100
#define TASK_LENGTH 100

typedef struct {
    char description[TASK_LENGTH];
    int completed;
} Task;

static Task tasks[MAX_TASKS];
static int task_count = 0;

void init_todo_list() {
    // Initialize todo list data structures
}

void render_todo_list() {
    WINDOW *todo_win = newwin(15, 30, 1, 32);
    box(todo_win, 0, 0);
    mvwprintw(todo_win, 0, 1, " Todo List ");
    mvwprintw(todo_win, 7, 10, "Test Todo List");
    wrefresh(todo_win);
}

void add_task(const char *task) {
    if (task_count < MAX_TASKS) {
        strncpy(tasks[task_count].description, task, TASK_LENGTH - 1);
        tasks[task_count].completed = 0;
        task_count++;
    }
}

void mark_task_complete(int task_id) {
    if (task_id >= 0 && task_id < task_count) {
        tasks[task_id].completed = 1;
    }
}

int get_progress() {
    int completed = 0;
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].completed) {
            completed++;
        }
    }
    return task_count > 0 ? (completed * 100) / task_count : 0;
}

