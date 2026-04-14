#ifndef QUEUE_H
#define QUEUE_H

#include "bankers_algorithm.h"

// Queue Struct:
// Queue is used for Safety Algorithm: (1) Safety Sequence &
// (2) Keeping track of process resource availability (i.e
// if a resource need for process i is greater than what's 
// available, then we come back to it later).
typedef struct {
    int items[NUM_PROCESSES]; // Max num of processes must be the number of processes (no duplicates)
    int front;
    int rear;
} Queue;

void queue_init(Queue* q);  // Initialize queue

bool is_empty(Queue* q);    // Check if queue is empty

void push(Queue* q, int value); // Push to the queue

bool is_full(Queue* q); // Check if full

void pop(Queue* q); // Pop from the queue

int peek(Queue* q); // Look at the front of the queue

bool contains(Queue* q, int find); // Check if value is in queue

#endif // QUEUE FOR BANKER'S ALGORITHM