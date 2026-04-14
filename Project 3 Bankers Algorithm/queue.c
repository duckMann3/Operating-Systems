#include "queue.h"

void queue_init(Queue* q) { // Initialize queue, front -1, and rear = 0
    q -> front = -1;
    q -> rear = 0;
}

bool is_empty(Queue* q) { // Check if queue is empty
    return (q -> front == q -> rear - 1);
}

bool is_full(Queue* q) { // Check if queue is full
    return (q -> rear == NUM_PROCESSES);
}

void push(Queue* q, int value) { // Push to queue
    if(is_full(q)) { // Don't push if full
        return;
    }
    q -> items[q -> rear] = value; // Select queue index & store new value
    q -> rear++;                   // Increment rear index
}

void pop(Queue* q) { // Remove from queue
    if(is_empty(q)) { // If empty, don't pop
        return;
    }
    q -> front++; // Increment front index
}

int peek(Queue* q) { // Check the front of queue
    if(is_empty(q)) { // If empty, return -1 (nothing is inside the queue)
        return -1;
    }
    return q -> items[q -> front + 1]; 
}

bool contains(Queue* q, int find) { // Check what's inside of queue
    int i = q -> front;
    if(i == -1) // If empty (then it can't be inside of queue)
        return false;

    while(i != q -> rear) { // While not at the end of queue
        if(q -> items[i] == find) { // If found, then it's in there!
            return true;
        }
        i = (i + 1) % NUM_PROCESSES; // Iterate according to size of queue
    }

    if(q -> items[q -> rear] == find) { // If it's at the end
        return true;
    }
    return false;
}
