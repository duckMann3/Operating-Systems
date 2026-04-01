#ifndef QUEUE_H
#define QUEUE_H

#include "bankers_algorithm.h"

typedef struct {
    int items[NUM_PROCESSES];
    int front;
    int rear;
} Queue;

void queue_init(Queue* q);

bool is_empty(Queue* q);

bool is_full(Queue* q);

void push(Queue* q, int value);

void pop(Queue* q);

int peek(Queue* q);

bool contains(Queue* q, int find);

#endif