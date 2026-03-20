#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PHILOSOPHER_NUM 5

typedef enum {
    THINKING,
    EATING
} action_t;

typedef struct {
    pthread_t thread;
    int id;
    action_t action;
    pthread_cond_t wait;
} philosopher_t;

enum { THINKING, HUNGRY, EATING } state[PHILOSOPHER_NUM];
pthread_cond_t self[PHILOSOPHER_NUM];

// ===========================
//      HELPER FUNCTIONS 
// ===========================
void* print_message_function(void* ptr);
void Wait_Time(void);
// ===========================
//          MONITOR 
// ===========================
// void test(int i);
void Create_Philosopher_Threads(void);
void test(philosopher_t* phil);
void pickup_forks(int philosopher_id);
void return_forks(int philosopher_id);

philosopher_t philosophers[PHILOSOPHER_ID];
int main(void) {

  Create_Philosopher_Threads();
  return 0;
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

void Wait_Time(void) {
  srand(time(NULL));
  // Generate a random number from [1,3]
  int random_num = (rand() % 3) + 1;
  printf("Random number: %d\n", random_num);
}

void test(philosopher_t* phil) {
  if(phil -> action == EATING && )
}

void pickup_forks(int philosopher_id) {

}

void return_forks(int philosopher_id) {

}
