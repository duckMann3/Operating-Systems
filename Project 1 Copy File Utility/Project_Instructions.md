# Description
* Design & implement a file-copying program named **filecopy.c**.
* Utilize ordinary pipes for **Inter-Process Communication (IPC)**.
* Requirements:
    * The program will take int *two parameters*: the name of the file to be copied & the destination file.
    * It will create a pipe (look into this), write the contents of the source file to the pipe, and then have a child process read from the pipe & write to the destination file.
    * *What Are Inter-Process Comm Pipes?*

# Features:
* **Command-line Arguments:** The program will accept source file and destination file.
* **Pipe Creation:** The program will create an ordinary pipe to transfer data between the parent and child processes.
* **Error Handling:** Proper error handling will be implemented for *file operations and pipe creation*.

# Project Implementation Steps:
* **Open Source & Destination Files:** Open the source file in read mode & the destination file in write mode.
* **Create a Pipe:** Use the `pipe()` syscall to create an ordianry pipe.
