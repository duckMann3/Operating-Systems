#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* foo(void* arg);

int main() {
    pthread_t thread1;

    // Create a new thread:
    pthread_create(&thread1, NULL, foo, NULL);

    pthread_join(thread1, NULL);
    return 0;
}

void* foo(void* arg) {
    printf("Created a new thread");
    return NULL;
}
