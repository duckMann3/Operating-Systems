#include <stdio.h>
#include <string.h>
#include <time.h>
#include "bankers_algorithm.h"

//==============================================
//                  RUN TIME 
//==============================================
void GET_RUNTIME(void);

//==============================================
//   RESOURCE MATRICES FOR BANKER'S ALGORITHM
//==============================================
int maximum[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int need[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 4, 3},
    {1, 2, 2},
    {6, 0, 0},
    {0, 1, 1},
    {4, 3, 1}
};

int available[NUM_RESOURCES] = {3, 3, 2};

// Finish Vector (determines when Safety Check Should Be Done):
bool Finish[NUM_PROCESSES] = {false, false, false, false, false};

// Request from Process 1:
int request_proc1[NUM_RESOURCES] = {1,0,2};

// Request from Process 4:
int request_proc4[NUM_RESOURCES] = {3,3,1};

clock_t start, end;
double cpu_time_used;

clock_t t;

int main(void) {
    start = clock();
    // Init Helper Variables: Sum up resources, work pointer for safety algorithm,
    // num processes that are requesting resources:
    int* resource_sum, *work;
    int proc_1 = 1, proc_4 = 4; 

    // Copy over available matrix to both resource sum & work vectors
    // (this was done to prevent the program from accidentally changing
    // the actual values in the available matrix):
    memcpy(resource_sum, available, sizeof(available));
    memcpy(work, available, sizeof(available));

    // Sum Up Resources. Use this later to compare output of safety algorithm.
    // If the same, then safe. Else, NOT safe!
    resource_sum = sum_instances(resource_sum, (int*)allocation);

    // Run Safety Algorithm:
    int* safety_out = safety_algorithm(work, (int*)allocation, (int*)need, (bool*)Finish);
    // Run Safety Check (Check if Output for Safety Algorithm matches Resource Sum):
    // Then print out whether or not the system is safe.
    bool flag = safety_check(resource_sum, safety_out);
    if(flag) {
        printf("=============System is in a Safe State================\n");
        printf("Safe Sequence: ");
        print_vector(safety_out);
    } else {
        print_vector(safety_out);
        printf("Is NOT Safe\n");
    }

    // Resource Request Test Cases for Process 1 & 4:
    resource_request(proc_1, (int*)request_proc1, (int*)(allocation + proc_1), (int*)(need + proc_1), (int*)(available));
    resource_request(proc_4, (int*)request_proc4, (int*)(allocation + proc_4), (int*)(need + proc_4), (int*)(available));
    printf("======================================================\n");
    GET_RUNTIME();
    return 0;
}

void GET_RUNTIME(void) {
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Execution Time: %f seconds\n", (cpu_time_used < 0) ? -1*cpu_time_used : cpu_time_used);
}
