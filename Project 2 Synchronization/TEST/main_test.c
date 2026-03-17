#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

#define PHILOSOPHER_ID 5

typedef enum {
    THINKING,
    EATING
} action_t;

typedef struct {
    pthread_t thread;
    int id;
    action_t action;
} philosopher_t;

void* foo(void* arg);
void* print_message_function(void* ptr);

// Main Code Functions:
void Create_Philosopher_Threads(void);
void pickup_forks(int philosopher_id);
void return_forks(int philosopher_id);

philosopher_t philosophers[PHILOSOPHER_ID];
int main(void) {
  Create_Philosopher_Threads();
  return 0;
}

void* foo(void* arg) {

}

void* print_message_function(void* ptr) {
  char* message;
  message = (char*) ptr;
  printf("%s \n", message);
}

void Create_Philosopher_Threads(void) {
  char* message[PHILOSOPHER_ID] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4", "Thread 5"};
  int iret[PHILOSOPHER_ID];
  for(int i = 0; i < PHILOSOPHER_ID; i++) {
    iret[i] = pthread_create(&(philosophers[i].thread), NULL, print_message_function, (void*) message[i]);
    pthread_join(philosophers[i].thread, NULL);
    printf("Thread %d returns: %d\n", i, iret[i]);
  }
}
