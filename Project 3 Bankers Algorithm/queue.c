#include "queue.h"

void queue_init(Queue* q) {
    q -> front = -1;
    q -> rear = 0;
}

bool is_empty(Queue* q) {
    return (q -> front == q -> rear - 1);
}

bool is_full(Queue* q) {
    return (q -> rear == NUM_PROCESSES);
}

void push(Queue* q, int value) {
    if(is_full(q)) {
        return;
    }
    q -> items[q -> rear] = value;
    q -> rear++;
}

void pop(Queue* q) {
    if(is_empty(q)) {
        return;
    }
    q -> front++;
}

int peek(Queue* q) {
    if(is_empty(q)) {
        return -1;
    }
    return q -> items[q -> front + 1];
}

bool contains(Queue* q, int find) {
    int i = q -> front;
    if(i == -1)
        return false;

    while(i != q -> rear) {
        if(q -> items[i] == find) {
            return true;
        }
        i = (i + 1) % NUM_PROCESSES;
    }

    if(q -> items[q -> rear] == find) {
        return true;
    }
    return false;
}
