#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define PHILOSOPHER_NUM 5

enum { THINKING, HUNGRY, EATING } state[PHILOSOPHER_NUM];

// int state[PHILOSOPHER_NUM];
pthread_mutex_t monitor_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond[PHILOSOPHER_NUM];

// ===========================
//      HELPER FUNCTIONS 
// ===========================
void* print_message_function(void* ptr);
void Wait_Time(void);

// ===========================
//      MONITOR FUNCTIONS 
// ===========================
void* Philosopher_Status(void* i);
void pickup_forks(int philosopher_id);
void return_forks(int philosopher_id);
void test(int philosopher_id);

int main(void) {
  pthread_t thread_id[PHILOSOPHER_NUM];
  int phil_IDs[PHILOSOPHER_NUM];
  
  for(int i = 0; i < PHILOSOPHER_NUM; i++) {
    pthread_cond_init(&cond[i], NULL);
    state[i] = THINKING;
    phil_IDs[i] = i;
  }

  for(int i = 0; i < PHILOSOPHER_NUM; i++) {
    pthread_create(&thread_id[i], NULL, Philosopher_Status, &phil_IDs[i]);
  }

  for(int i = 0; i < PHILOSOPHER_NUM; i++) {
    pthread_join(thread_id[i], NULL);
  }

  return 0;
}

void* Philosopher_Status(void* i) {
  int philosopher_id = *(int*)i;
  while(1) {
    printf("Philosopher %d is thinking.\n", philosopher_id);
    sleep(1);
    pickup_forks(philosopher_id);
    printf("Philosophery %d is EATING.\n", philosopher_id);
    sleep(1);
    return_forks(philosopher_id);
  } 
}

void pickup_forks(int philosopher_id) {
  pthread_mutex_lock(&monitor_lock);
  state[philosopher_id] = HUNGRY;
  test(philosopher_id);
  while(state[philosopher_id] != EATING) {
    pthread_cond_wait(&cond[philosopher_id], &monitor_lock);
  }
  pthread_mutex_unlock(&monitor_lock);
}

void return_forks(int philosopher_id) {
  pthread_mutex_lock(&monitor_lock);
  state[philosopher_id] = THINKING;

  test((philosopher_id + 4) % PHILOSOPHER_NUM); // Check Left
  test((philosopher_id + 1) % PHILOSOPHER_NUM); // Check Right
  
  pthread_mutex_unlock(&monitor_lock);
}

void test(int philosopher_id) {
  if((state[philosopher_id] == HUNGRY) && 
     (state[(philosopher_id + 4) % 5] != EATING) &&
     (state[(philosopher_id + 1) % 5] != EATING)) {
    state[philosopher_id] = EATING;
    pthread_cond_signal(&cond[philosopher_id]);  // Signal this philosopher to start eating.
  }
}


