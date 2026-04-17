/**
 * FCFS scheduling
 */
 
#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

// add a task to the list 
void add(char *name, int priority, int burst) {
    struct node fcfs;
    insert(&fcfs, name);
}

// invoke the scheduler
void schedule() {

}