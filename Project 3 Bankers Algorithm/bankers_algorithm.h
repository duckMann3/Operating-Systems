
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"

#ifndef BANKERS_ALGORITHM_H
#define BANKERS_ALGORITHM_H

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

void print_test(int* arr, int row, int col);

int* arr_add(int* a, int*b);

int* safety_algorithm(int* available, int* allocation, int* need, bool* Finish);

bool safety_check(int* result, int* safety_output);

bool comparison(int* a, int* b, int i);

bool Check_In(bool* Finish);

void resource_request_check(int request, int need, int available);

#endif // BANKERS_ALGORITHM_H   