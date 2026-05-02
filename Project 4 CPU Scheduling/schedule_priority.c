/*
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "schedulers.h"
#include "task.h"
#include "CPU.h"

//==============================
//      Init Helper Values 
//==============================
static Task* pickNextTask(void); // Choose next task
struct node* pri_list = NULL;    // Keep track of priority tasks
static int next_tid = 1;         // Keep Task ID Tracker

// add a task to the list 
void add(char *name, int priority, int burst) {
    Task* input=malloc(sizeof(Task));   // Allocate temporary task
    if(input == NULL) {
        fprintf(stderr, "Failed to allocate task.\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialize input task
    input -> name = strdup(name);
    input -> tid = next_tid++;
    input -> priority = priority;
    input -> burst = burst;

    insert(&pri_list, input);
}

// determine next task for execution
static Task* pickNextTask(void) {
    // Helper temp variables::w
    struct node *curr = pri_list;   // Temp for current list
    struct node *best_prev = NULL;  // Keep track of prev (best/highest pri)
    struct node *best = pri_list;   // Keep track of best/highest pri
    struct node *prev = NULL;       // Keep track of previous head

    if (pri_list == NULL) return NULL; // Return if empty

    while (curr != NULL) {          // Iterate
        if (curr->task->priority >= best->task->priority) { // If highest pri was found, then set to highest
            best = curr;
            best_prev = prev;
        }
        prev = curr;
        curr = curr->next;
    }

    if (best_prev == NULL) {    // Priority at end of list
        pri_list = best->next;
    } else {
        best_prev->next = best->next;
    }

    return best->task;              // Return highest priority
}

// invoke the scheduler
void schedule() {
    Task *task; // Temporary task
    while ((task = pickNextTask()) != NULL) { // Iterate through chosen tasks until end of list 
        run(task, task->burst);   // Run tasks
        free(task->name);         // Free alloc memory
        free(task);
    }
}