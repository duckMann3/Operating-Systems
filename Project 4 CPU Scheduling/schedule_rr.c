/*
 * Round-robin scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "schedulers.h"
#include "task.h"
#include "CPU.h"

static struct node *rr = NULL;
static struct node *tail = NULL;
static int next_tid = 1;

void add(char *name, int priority, int burst)
{
    Task *task = malloc(sizeof(Task));
    struct node *new_node;

    if (task == NULL) {
        fprintf(stderr, "Failed to allocate task.\n");
        exit(EXIT_FAILURE);
    }

    new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Failed to allocate list node.\n");
        free(task->name);
        free(task);
        exit(EXIT_FAILURE);
    }

    task->name = strdup(name);
    task->tid = next_tid++;
    task->priority = priority;
    task->burst = burst;

    new_node->task = task;
    new_node->next = NULL;

    if (tail == NULL) {
        rr = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

static Task *pickNextTask(void)
{
    if(rr == NULL) return NULL;
    return rr -> task;
}

void schedule(void)
{
    Task *task;
    struct node *old_head;
    int slice;

    while ((task = pickNextTask()) != NULL) {
        slice = (task->burst > QUANTUM) ? QUANTUM : task->burst;
        run(task, slice);
        task->burst -= slice;

        old_head = rr;
        rr = rr->next;
        if(rr == NULL) {
            tail = NULL;
        }

        if(task->burst > 0) {
            old_head->next = NULL;
            if (tail == NULL) {
                rr = old_head;
                tail = old_head;
            } else {
                tail->next = old_head;
                tail = old_head;
            }
        } else {
            free(task->name);
            free(task);
            free(old_head);
        }
    }
}