#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#define SIZE    100

void add(char *name, int priority, int burst);
void schedule(void);

struct node* fcfs = NULL;
int main(int argc, char *argv[]) {
    /*
     * Task
     * Next
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    in = fopen(argv[1],"r");
    
    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        add(name,priority,burst);

        free(temp);
    }
    fclose(in);
    */
    add("T1", 4, 20);
    add("T2", 10, 20);
    add("T3", 10, 20);

    // add("T2", 5, 20);
    schedule();
    return 0;
}

void add(char *name, int priority, int burst) {
    // Task input = {.name=name, .tid=1, .priority=priority, .burst=burst};
    Task* input=malloc(sizeof(Task)); // = {.name=name, .tid=1, .priority=priority, .burst=burst};
    input->name = strdup(name);
    input->tid=1;
    input->priority=priority;
    input->burst=burst;
    insert(&fcfs, input);

    // traverse(fcfs);
    // delete(&fcfs, &input);
}

void schedule(void) {
    
    traverse(fcfs);
    // traverse(fcfs);
}