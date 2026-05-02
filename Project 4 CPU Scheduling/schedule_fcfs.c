/**
 * FCFS scheduling
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "schedulers.h"
#include "task.h"
#include "CPU.h"

static Task* pickNextTask(void);
struct node* fcfs = NULL;
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

    insert(&fcfs, input);
}

// invoke the scheduler
void schedule() {
    Task* task;
    while((task = pickNextTask()) != NULL) {
        run(task, task -> burst);
        free(task -> name);
        free(task);
    }
    /*
    double runningAverg = 0.0, sum = 0.0;
    int size = 0;

    printf("========First-Come First-Serve:=======\n");
    traverse(fcfs);
    struct node* temp;
    temp = fcfs;

    while(temp != NULL) {
        if(temp -> next != NULL) {
            runningAverg += temp -> task -> burst;
            sum += runningAverg;
        } 
        size++;
        temp = temp -> next;
    }
    printf("Average Waiting Time: %.2f\n", sum/size);
    printf("======================================\n");
    */
}

static Task* pickNextTask(void) {
    struct node* curr = fcfs;
    struct node* prev = NULL;

    if(curr == NULL) return NULL;

    while(curr -> next != NULL) {
        prev = curr;
        curr = curr -> next;
    }

    if(prev == NULL) {
        fcfs = NULL;
    } else {
        prev -> next = NULL;
    }
    
    return curr -> task;
}