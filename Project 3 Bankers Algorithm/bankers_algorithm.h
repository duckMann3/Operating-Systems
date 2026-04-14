
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"

#ifndef BANKERS_ALGORITHM_H
#define BANKERS_ALGORITHM_H

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

//===========================================
//              HELPER FUNCTIONS:
//===========================================
void print_vector(int* arr);                // Print row vector (array)
bool comparison(int* a, int* b, int i);     // Compare row vector vs. matrix
bool vector_comparison(int* a, int* b);     // Compare two row vectors
void arr_add(int* a, int* b);               // Add two row vectors
void arr_sub(int* a, int* b);               // Subtract two row vectors
bool Check_In(bool* Finish);                // Check if Finish vector is true for all i (for Safety Algorithm)
int* sum_instances(int* resource_sum, int* allocation); // Sum up all instances (including avaialble) (for Safety Algorithm)
//===========================================
//        SAFETY ALGORITHM FUNCTIONS:
//===========================================
int* safety_algorithm(int* available, int* allocation, int* need, bool* Finish); // Safety Algorithm
bool safety_check(int* result, int* safety_output);                              // Check if output of safety algorithm matches sum of resources
//===========================================
//        RESOURCE ALGORITHM FUNCTIONS:
//===========================================
void resource_request(int process, int* request, int* allocation, int* need, int* available); // Resource-Request Algorithm

#endif // BANKERS_ALGORITHM_H   