/* POSIX Condition Variables:
 * pthread_cond_t data type: initialized using the pthread_cond_init()
 * function. Example code creates and initializes a condition Variable
 * as well as its associated mutex lock:
 * pthread_mutex_t mutex;
 * pthread_cond_t cond_var;
 * pthread_mutex_init(&mutex, NULL);
 * pthread_cond_init(&cond_var, NULL);
 * */
#include <stdio.h>
#include <pthread.h>

// Each thread will count TIMES_TO_COUNT times
#define TIMES_TO_COUNT 21000

#define NC       "\e[0m"
#define YELLOW   "\e[33m"
#define BYELLOW  "\e[1;33m"
#define RED      "\e[1;33m"
#define GREEN    "\e[32m"

// This structure contains the count as well as the mutex
// that will protect the access to the variable.
typedef struct s_counter {
  pthread_mutex_t count_mutex;
  unsigned int count;
} t_counter;

void* thread_routine(void* data);

int main(void) {
  pthread_t tid1, tid2;
  t_counter counter;

  counter.count = 0;

  pthread_mutex_init(&counter.count_mutex, NULL);

  printf("Main: Expected count is %s%u%s\n", GREEN, 2*TIMES_TO_COUNT, NC);

  pthread_create(&tid1, NULL, thread_routine, &counter);
  printf("Main: Created 1st thread [%ld]\n", tid1);
  pthread_create(&tid2, NULL, thread_routine, &counter);
  printf("Main: Created 2nd thread [%ld]\n", tid2);

  pthread_join(tid1, NULL);
  printf("Main: Joined 1st thread [%ld]\n", tid1);
  pthread_join(tid2, NULL);
  printf("Main: Joined 2nd thread [%ld]\n", tid2);

  if(counter.count != (2*TIMES_TO_COUNT)) {
    printf("%sMain: ERROR ! Total count is %u%s\n", RED, counter.count, NC);
  } else {
    printf("%sMain: OK. Total count is %u%s\n", GREEN, counter.count, NC);
  }
  pthread_mutex_destroy(&counter.count_mutex);

  return (0);
}

void* thread_routine(void* data) {
  pthread_t tid;        // Thread ID
  t_counter* counter;   // Pointer to the struct in main
  unsigned int i;       // Index, ID Counter

  tid = pthread_self();       // Get the calling thread ID
  counter = (t_counter*)data; // Pointer to data & type cast from void pointer
                              // to t_counter pointer.
  pthread_mutex_lock(&counter->count_mutex);
  printf("%sThread [%ld]: Count as thread starts = %u.%s\n", YELLOW, tid, counter->count, NC);
  pthread_mutex_lock(&counter->count_mutex);
  i = 0;
  while(i < TIMES_TO_COUNT) {
    pthread_mutex_lock(&counter->count_mutex);
    counter->count++;
    pthread_mutex_lock(&counter->count_mutex);
    i++;
  }

  pthread_mutex_lock(&counter->count_mutex);
  printf("%sThread [%ld]: Final Count = %u.%s\n", BYELLOW, tid, counter->count, NC);
  pthread_mutex_lock(&counter->count_mutex);
  return (NULL);
}
