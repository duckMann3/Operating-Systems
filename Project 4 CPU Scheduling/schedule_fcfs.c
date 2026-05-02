/**
 * FCFS scheduling
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
static Task* pickNextTask(void); // Function Determines the next task (static because it is implementation specific)
struct node* fcfs = NULL;        // FCFS Linked List 
static int next_tid = 1;         // Next Task ID Tracker

// add a task to the list 
void add(char *name, int priority, int burst) {
    Task* input=malloc(sizeof(Task));   // Allocate temporary task
    if(input == NULL) {                 // Track for allocation error
        fprintf(stderr, "Failed to allocate task.\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialize input task:
    input -> name = strdup(name);
    input -> tid = next_tid++;
    input -> priority = priority;
    input -> burst = burst;

    insert(&fcfs, input); // Inser to FCFS Linked List
}

// invoke the scheduler
void schedule() {
    Task* task;  // Temporary task
    while((task = pickNextTask()) != NULL) { // Iterate through chosen tasks until end of Linked List
        run(task, task -> burst);            // Run Task
        free(task -> name);                  // Free Memory Elements
        free(task);
    }
}

// FCFS implementation of choosing a next task:
// Picks next task sequentailly 
static Task* pickNextTask(void) {
    struct node* curr = fcfs;   // Set temporary node
    struct node* prev = NULL;   // Keep track of previous position

    if(curr == NULL) return NULL; // If empty, return

    while(curr -> next != NULL) { // Iterate
        prev = curr;
        curr = curr -> next;
    }

    if(prev == NULL) {
        fcfs = NULL;
    } else {
        prev -> next = NULL;
    }
    
    return curr -> task;          // Return immediate, no particular order
}