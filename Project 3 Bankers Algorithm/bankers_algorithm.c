#include "bankers_algorithm.h"
//==============================================
//                 PRINT VECTOR  
//==============================================
void print_vector(int* arr) {
    printf("[");
    for(int i = 0; i < NUM_RESOURCES; i++) {
        if(i == NUM_RESOURCES - 1) {       // This extra condition just prevents the output from looking like this: [1, 2, 3, ]
            printf("%d", *(arr + i));
        } else {
            printf("%d, ", *(arr + i));
        }
    }
    printf("]\n");
}
//==============================================
//          VECTOR & MATRIX COMPARISONS 
//==============================================
// Check if row vector a is greater than matrix b
bool comparison(int* a, int* b, int i) {
    int a_i = 0, b_j = 0;                       // Temp Values (to store a & b)
    for(int j = 0; j < NUM_RESOURCES; j++) { 
        a_i = *(a + i * NUM_RESOURCES + j);     // To index in 
        b_j = *(b + j); 
        if(a_i > b_j) {
            return false;
        }
    }
    return true;
}
// Check if row vector a is greater than row vector b:
bool vector_comparison(int* a, int* b) {
    for(int i = 0; i < NUM_RESOURCES; i++) {
        if(*(a + i) > *(b + i)) {
            return false;
        }
    }
    return true;
}
//===========================================
//              VECTOR OPERATIONS
//===========================================
// Add arr a + arr b
void arr_add(int* a, int*b) {
    for(int i = 0; i < NUM_RESOURCES; i++) {
        *(a + i) = (*(a + i)) + (*(b + i));
    }
}
// Subtract arr a + arr b
void arr_sub(int* a, int* b) {
    for(int i = 0; i < NUM_RESOURCES; i++) {
        *(a + i) = (*(a + i)) - (*(b + i));
    }
}

// Used to Check if the Finish vector contains all TRUE:
bool Check_In(bool* Finish) {
    for(int i = 0; i < NUM_PROCESSES; i++) {
        if(*(Finish + i) == false) {  // NOT all true, return False & keep checking for avaialble processes
            return false;
        }
    }
    return true;                      // All true, return True & print safety sequence & safety out
}
// Sum Instances (for resource_sum in main, used to check
// safety later)
int* sum_instances(int* resource_sum, int* allocation) {
    for(int i = 0; i < NUM_PROCESSES; i++) {
        arr_add(resource_sum, (allocation + i * NUM_RESOURCES)); // Add all resources together
    }
    return resource_sum;
}

//===========================================
//              SAFETY ALGORITHM 
//===========================================
// NOTE: Really janky code below :O
int* safety_algorithm(int* available, int* allocation, int* need, bool* Finish) {
    /* Safety Algorithm:
     1. Initialize Work & Finish,
     2. Find an index such that both Finish == False & Need <= Work
     3. Work += Allocation, Finish = True 
     4. If Finish == True for all i, then the system is in a safe state, else not.
    */
    // Algorithm Initialization:
    int* work = available;                    // Set work equal available 
    Queue q = { .front = -1, .rear = 0 };     // To Be Checked Later Queue: For storing process i that satisfies Step 2 of the algorithm.
    Queue safe = { .front = -1, .rear = 0 };  // Safety Sequence Queue: For storing process i that completes Step 3 (returns as the Safety Sequence) 
    bool found = false;                       // Flag: Flag for when Step 2 (one safe process) is found.

    int i = 0;                                // Incrementer for for-loop (initialized outside of loop so I can reset)
    for(; i < NUM_PROCESSES; i++) {
        if(*(Finish + i) == false) {          // Check first condition of Safety Algorithm: If process is finished
            if(comparison((int*)need, (int*)work, i)) {   // Check if process i's resource need is sufficient for available
                arr_add(work, (allocation + i * NUM_RESOURCES)); 
                *(Finish + i) = true;          // Set index for process i to be true (Finished)
                found = true;                  // Set flag to true since a process to be added into the Safe Sequence was found
                push(&safe, i);                // Push to Safety Sequence
            } else {
                if(!contains(&q, i)) {         // If process i's resource need is too large, add it to the queue to be checked later
                    push(&q, i);
                } else {
                    found = false;             // Set flag to false since a process to be added into the Safe Sequence was not found
                }
            }
        } else {
            found = false;                     // Default, nothing found = false
        }
        if(found) {                            // If something was found during the check:
            i = peek(&q);                      // Assign that value to the for loop iteration to see if the resource need can now be requested
            pop(&q);                           // Then, pop
        }
        if(Check_In(Finish)) {                 // Check if Finish is true for all i
            printf("Safety Sequence: \n");     // Print Safety Sequence from safe queue
            while(!is_empty(&safe)) {
                printf("%d, ", peek(&safe));
                pop(&safe);
            }
            printf("\n");
            return work;                       // Return sum of resource (safety_out in main) 
        }
    }
    return work;
}
// Compare Safety Out to Resource Sum:
bool safety_check(int* result, int* safety_output) {
    for(int i = 0; i < NUM_RESOURCES; i++) {        // Iterate through resources
        if(*(result + i) != *(safety_output + i))   // If NOT the same, return false & print NOT safe in main
            return false;
    }
    return true;                                    // Else, is the same, returne true & print IS safe in main
}
//===========================================
//             RESOURCE REQUEST 
//===========================================
void resource_request(int process, int* request, int* allocation, int* need, int* available) {
    /* Resource-Request Algorithm:
        1. If request <= need: next, else: raise error (exceed max claim).
        2. If request <= available: next, else: raise error (not enough resources).
        3. Allocate:
            Available -= Request,
            Allocation += Request,
            Need -= Request
        Safe -> the resources are allocated to process i
        Unsafe -> process i must wait & restore the old resource-allocation
    */
    // Print request vector from process i:
    printf("Process %d requests resources ", process);
    print_vector(request);
    // Resource-Request Algorithm:
    if(!vector_comparison(request, need)) { // Step 1
        printf("Error: Not enough resources available for P%d", process);
        return;
    } else if (!vector_comparison(request, available)) { // Step 2
        printf("P%d must wait, since resources are not available\n", process);
        return;
    }
    // Step 3:
    printf("=============System is in a Safe State================\n");
    arr_sub(available, request);
    arr_add(allocation, request);
    arr_sub(need, request);
    printf("Resources allocated to process %d\n", process);
}