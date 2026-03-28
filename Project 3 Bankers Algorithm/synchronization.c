#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define PHILOSOPHER_NUM 5

// ===========================================
//    INITIALIZE PHILOSOPHERS, LOCKS, & CV 
// ===========================================
enum { THINKING, HUNGRY, EATING } state[PHILOSOPHER_NUM];
pthread_mutex_t monitor_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond[PHILOSOPHER_NUM];
// ===========================
//        HELPER FUNCTION
// ===========================
int Wait_Time(void);
// ===========================
//      MONITOR FUNCTIONS 
// ===========================
void* Philosopher_Status(void* i);
void pickup_forks(int philosopher_id);
void return_forks(int philosopher_id);
void test(int philosopher_id);

int main(void) {
  srand(time(NULL));
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

int Wait_Time(void) {
  return (rand() % 3) + 1; // Generate a random number from [1,3]
}

void* Philosopher_Status(void* i) {
  int philosopher_id = *(int*)i;
  while(1) {
    int thinking_time = Wait_Time(), eating_time = Wait_Time();
    printf("Philosopher %d is thinking for %d sec.\n", philosopher_id, thinking_time);
    sleep(thinking_time);
    printf("Philosopher %d is HUNGRY.\n", philosopher_id);
    pickup_forks(philosopher_id);
    printf("Philosopher %d is EATING for %d sec.\n", philosopher_id, eating_time);
    sleep(eating_time);
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
