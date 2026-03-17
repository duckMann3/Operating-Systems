#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PHILOSOPHER_ID 5
void* foo(void* arg);
void pickup_forks(int philosopher_id);
void return_forks(int philosopher_id);

typedef enum {
    THINKING,
    EATING
} action_t;

typedef struct {
    pthread_t thread;
    int id;
    action_t action;
} philosopher_t;

int main(void) {
    pthread_t philosophers[PHILOSOPHER_ID];

    return 0;
}

void* foo(void* arg) {

}