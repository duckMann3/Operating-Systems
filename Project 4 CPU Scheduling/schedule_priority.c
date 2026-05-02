/*
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "schedulers.h"
#include "task.h"
#include "CPU.h"

static Task* pickNextTask(void);
struct node* pri_list = NULL;
static int next_tid = 1;

// add a task to the list 
void add(char *name, int priority, int burst) {
    Task* input=malloc(sizeof(Task));   // Allocate temporary task
    if(input == NULL) {
        fprintf(stderr, "Failed to allocate task.\n");
        exit(EXIT_FAILURE);
    }
    input -> name = strdup(name);
    input -> tid = next_tid++;
    input -> priority = priority;
    input -> burst = burst;

    insert(&pri_list, input);
}

// invoke the scheduler
void schedule() {
    Task *task;
    while ((task = pickNextTask()) != NULL) {
        run(task, task->burst);
        free(task->name);
        free(task);
    }
}

// determine next task for execution
static Task* pickNextTask(void) {
    struct node *curr = pri_list;
    struct node *best_prev = NULL;
    struct node *best = pri_list;
    struct node *prev = NULL;

    if (pri_list == NULL) return NULL;

    while (curr != NULL) {
        if (curr->task->priority >= best->task->priority) {
            best = curr;
            best_prev = prev;
        }
        prev = curr;
        curr = curr->next;
    }

    if (best_prev == NULL) {
        pri_list = best->next;
    } else {
        best_prev->next = best->next;
    }

    return best->task;    
}