/**
 * FCFS scheduling
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "schedulers.h"
#include "task.h"
#include "CPU.h"

struct node* fcfs = NULL;
// add a task to the list 
void add(char *name, int priority, int burst) {
    Task* input=malloc(sizeof(Task)); 
    input->name = strdup(name);
    input->tid=1;
    input->priority=priority;
    input->burst=burst;
    insert(&fcfs, input);
}

// invoke the scheduler
void schedule() {
    printf("========First-Come First-Serve:=======\n");
    traverse(fcfs);
    struct node* temp;
    temp = fcfs;
    double runningAverg = 0.0;
    double sum = 0.0;
    int size = 0;

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
}

// determine next task for execution
void pickNextTask() {

}