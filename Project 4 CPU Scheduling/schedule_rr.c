/*
 * Round-robin scheduling
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
static Task* pickNextTask(void); // Function Determines the next task
static struct node *rr = NULL;   // RR Linked
static struct node *tail = NULL; // Keep track of end
static int next_tid = 1;         // Next Task ID Tracker

void add(char *name, int priority, int burst)
{
    Task *task = malloc(sizeof(Task)); // Allocate temporary task
    struct node *new_node;             // Temp node

    if (task == NULL) {                // Throw error if task failed to alloc  
        fprintf(stderr, "Failed to allocate task.\n");
        exit(EXIT_FAILURE);
    }

    new_node = malloc(sizeof(struct node)); // Allocate for temp node
    if (new_node == NULL) {            // Throw error if temp node failed to alloc
        fprintf(stderr, "Failed to allocate list node.\n");
        free(task->name);
        free(task);
        exit(EXIT_FAILURE);
    }

    // Initialize input task
    task->name = strdup(name);
    task->tid = next_tid++;
    task->priority = priority;
    task->burst = burst;
    // Set temp node to task
    new_node->task = task;
    new_node->next = NULL;

    // "Insert" to list
    if (tail == NULL) {     // Check if empty, then set rr & tail
        rr = new_node;
        tail = new_node;
    } else {                // Otherwise, create new node & tail 
        tail->next = new_node;
        tail = new_node;
    }
}

// determine next task for exection
static Task *pickNextTask(void)
{
    // Simply chooses the next task (more logic in schedule function)
    if(rr == NULL) return NULL;
    return rr -> task;
}

void schedule(void)
{
    // Temp helper variables
    Task *task;             // Keeps track of tasks
    struct node *old_head;  // Keeps track of prev head
    int slice;              // Keeps track of time quantum left

    while ((task = pickNextTask()) != NULL) { // While list is not empty
        slice = (task->burst > QUANTUM) ? QUANTUM : task->burst; // Gets time slice based on burst & quantum
        // Run task, then decrement after quantum ends/interrupts 
        run(task, slice);
        task->burst -= slice;

        old_head = rr; // Set prev
        rr = rr->next; // move down schedule tasks

        if(rr == NULL) tail = NULL; // If rr empty

        if(task->burst > 0) { // If task is NOT complete
            old_head->next = NULL;
            if (tail == NULL) { // Set end of tail
                rr = old_head;
                tail = old_head;
            } else {            // Set next
                tail->next = old_head;
                tail = old_head;
            }
        } else {            // Otherwise, delete
            free(task->name);
            free(task);
            free(old_head);
        }
    }
}