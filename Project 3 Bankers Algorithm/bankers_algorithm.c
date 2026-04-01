#include "bankers_algorithm.h"

bool Check_In(bool* Finish) {
    for(int i = 0; i < NUM_PROCESSES; i++) {
        if(*(Finish + i) == false) {
            return false;
        }
    }
    return true;
}

int* arr_add(int* a, int*b) {
    int* add;
    // print_test(a, 3, 0);
    // print_test(b, 3, 0);
    for(int i = 0; i < NUM_RESOURCES; i++) {
        *(add + i) = (*(a + i)) + (*(b + i));
    }
    // printf("\n");
    return add;
}

bool comparison(int* a, int* b, int i) {
    int a_i = 0, b_j = 0;
    for(int j = 0; j < NUM_RESOURCES; j++) {
        a_i = *(a + i * NUM_RESOURCES + j); 
        b_j = *(b + j); 
        if(a_i > b_j) {
            // printf("Resource %d is greater than %d.\n", a_i, b_j);
            return false;
        }
    }
    return true;
}

void print_test(int* arr, int row, int col) {
    printf("Output: ");
    for(int i = 0; i < row; i++) {
        printf("%d, ", *(arr + i));
    }
    printf("\n");
}

int* safety_algorithm(int* available, int* allocation, int* need, bool* Finish) {
    int* work = available;
    Queue q = { .front = -1, .rear = 0 };
    int index = -1;
    bool found = false;
    int i = 0;
    for(; i < 4; i++) {
        print_test(work, 3, 0); 
        if(*(Finish + i) == false) {
            if(comparison((int*)need, (int*)work, i)) {
                printf("P%d is safe.\n", i);
                work = arr_add(work, (allocation + i * NUM_RESOURCES)); 
                *(Finish + i) = true;
                found = true;
            } else {
                printf("P%d is not safe.\n", i);
                if(!contains(&q, i)) {
                    index++;
                    push(&q, i);
                } else {
                    found = false;
                }
            }
        } else {
            found = false;
        }
        if(found && index >= 0) {
            i = peek(&q);
            pop(&q);
        }
        if(Check_In(Finish)) {
            return work;
        }
        for(int j = 0; j < NUM_PROCESSES; j++) {
            printf("%d ", Finish[j]);
        }
        printf("\n");
        printf("=============================\n");
    }
    return work;
}

bool safety_check(int* result, int* safety_output) {
    for(int i = 0; i < NUM_RESOURCES; i++) {
        printf("%d == %d, ", *(result + i), *(safety_output + i));
        if(*(result + i) != *(safety_output + i))
            return false;
    }
    return true;
}