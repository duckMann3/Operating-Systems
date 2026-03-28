# Description
---
# Implementation Requirements:
* Create 5 Philosophers (Indexed: 0-4)
    * **Characteristics:** Each a separate thread
    * **Actions:** Each think or eat (alternate between these two)
# Leaerning About POSIX
[Source - POSIX thread (pthread) libraries](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)
* POSIX is standard thread API for C/C++.
* It allows one to spawn new concurrent process flow.
* Threads require less overhead than "forking" or  spawning new process because the system does not initialize new system virtual memory space & environment for the process.
* Threads are also found in uniprocessor systems which exploit latency in I/O & other system functions which may halt process execution.
* Parallel Programming (i.e: MPI & PVM) are used in a distributed computing environment while threads are limited to a single computer system.
* A thread is spawned by defining a function & it's arguments which will be processed in the thread.

[Source - GeeksforGeeks: POSIX Threads in OS](https://www.geeksforgeeks.org/operating-systems/posix-threads-in-os/)

[Source - GeeksforGeeks: Thread Management Functions in C](https://www.geeksforgeeks.org/c/thread-functions-in-c-c/)

[Source - GeeksforGeeks: Generating Random Numbers in a Range in C](https://www.geeksforgeeks.org/c/generating-random-number-range-c/)