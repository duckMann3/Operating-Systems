#include <stdio.h>
#include <time.h>
#include "bankers_algorithm.h"
#include "unit_testing.h"

bool Finish[NUM_PROCESSES] = {false, false, false, false, false};

int main(int argc, char* argv[]) {
    int* resource_sum = available_2;
    for(int i = 0; i < NUM_PROCESSES; i++) {
        resource_sum = arr_add(resource_sum, *(alloc_2 + i));
    }
    print_test(resource_sum, 3, 0);
    printf("=================\n");
    // int* safety_out = safety_algorithm((int*)available, (int*)allocation, (int*)need, (bool*)Finish);
    int* safety_out = safety_algorithm((int*)available_2, (int*)alloc_2, (int*)need_2, (bool*)Finish);
    print_test(safety_out, 3, 0);

    bool flag = safety_check(resource_sum, safety_out);
    printf("\n");
    printf("%d\n", flag);
    printf(flag ? "Is Safe\n" : "Is NOT Safe\n");

    return 0;
}

