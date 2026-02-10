#include <stdio.h>
#include <unistd.h>

// ===================================
//          EXAMPLE PROGRAM
// ===================================

/* Step 1 - Create a pipe
 * Step 2 - Send a message to the pipe.
 * Step 3 - Retrieve the message from the pipe & write it the standard output.
 * Step 4 - Send another message to the pipe.
 * Step 5 - Retrieve the message from the pipe & write it to the standard output.
 */

int main(void) {
    int pipefds[2];
    int returnstatus;
    char writemessages[2][20] = {"Hi", "Hello"};
    char readmessage[20];
    returnstatus = pipe(pipefds);

    if (returnstatus == -1) {
        printf("Unable to create pipe\n");
        return 1;
    }

    printf("Writing to pipe - Message 1 is %s\n", writemessages[0]);
    write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
    read(pipefds[0], readmessage, sizeof(readmessage));

    printf("Reading from pipe Message 1 is %s\n", readmessage);
    printf("Writing to pipe - Message 2 is %s\n", writemessages[0]);
    write(pipefds[1], writemessages[1], sizeof(writemessages[1]));
    read(pipefds[1], writemessages[1], sizeof(readmessage));

    printf("Reading from pipe Message 2 is %s\n", readmessage);

    return 0;
}

