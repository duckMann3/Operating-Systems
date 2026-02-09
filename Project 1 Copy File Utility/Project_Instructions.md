# Description
* Design & implement a file-copying program named **filecopy.c**.
* Utilize ordinary pipes for **Inter-Process Communication (IPC)**.
* Requirements:
    * The program will take int *two parameters*: the name of the file to be copied & the destination file.
    * It will create a pipe (look into this), write the contents of the source file to the pipe, and then have a child process read from the pipe & write to the destination file.
    * *What Are Inter-Process Comm Pipes?*