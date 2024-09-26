#ifndef TODO_LIST_H
#define TODO_LIST_H

void init_todo_list();
void render_todo_list();
void add_task(const char *task);
void mark_task_complete(int task_id);
int get_progress();  // Add this line

#endif

