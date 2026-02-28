#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <stdio.h>
#include <time.h>

#define READ_END  0
#define WRITE_END 1

#define EXIT      1
#define SUCCESS   0

clock_t start, end;
double cpu_time_used;

clock_t t;

bool ERROR_HANDLER_UTILITY_CALL(int argc, char** argv);            // Input Error Handling
char* READ_ENTIRE_FILE(char* source_file, int size);               // Parent Process reads Source File
int GET_FILE_SIZE(char* source_file);                              // Reads file size to store for memory allocation
void  WRITE_TO_FILE(char* desintation_file, char* write_content);  // Child Process writes to Destination File
void GET_RUNTIME(void);

int main(int argc, char* argv[]) {
  start = clock();

  if(!ERROR_HANDLER_UTILITY_CALL(argc, argv)) { // Command-Line Argument Errors
    GET_RUNTIME();
    return EXIT;
  }
  
  // File Variables:
  char* source_file = argv[1];                  // Store Source Argument
  char* destination_file = argv[2];             // Store Destination Argument

  char* read_source_file;   
  char* write_destination_file; 

  int file_size = GET_FILE_SIZE(source_file);   // Get File Size

  if(file_size == -1) {                  // Failed to read Source File
    GET_RUNTIME();
    return EXIT;
  }

  write_destination_file= malloc(file_size + 1); // Memory Allocate to store read file from exit pipe
  read_source_file = READ_ENTIRE_FILE(source_file, file_size);

  if(read_source_file == NULL) {                  // Failed to read Source File
    printf("Unable to read file contents (file too large)\n");
    GET_RUNTIME();
    return EXIT;
  }

  // Pipes Variables & Check: 
  int pipefds[2];                   // Represents read entry and write exit for pip
  int return_status;                // Variable to check pipe creation
  return_status = pipe(pipefds);

  if(return_status == -1) {         // Failed to Create a pipe()
    printf("Unable to create pipe\n");
    GET_RUNTIME();
    return EXIT;
  }
  
  // Process ID
  int pid; 
  pid = fork();

  if(pid == 0) {  // Execute Child Process
    // Child process reads from pipe, then writes to Destination File: 
    read(pipefds[0], write_destination_file, sizeof(write_destination_file));
    WRITE_TO_FILE(destination_file, write_destination_file);
    free(write_destination_file);
    write_destination_file = NULL;
    GET_RUNTIME();
    printf("File successfully copied from '%s' to '%s'\n", source_file, destination_file);

  } else {        // Execute Parent Process
    // Parent process writes into pipe:
    write(pipefds[1], read_source_file, sizeof(read_source_file)); // Write "read_source_file" into pipe
  }
  return SUCCESS;
}

char* READ_ENTIRE_FILE(char* source_file, int size) {
  /* This function reads the entire information from the input Source File.
   * Input: Source File & source file's size
   * Output: buffer that stores the contents of the source file
  */

  FILE* open_file = fopen(source_file, "rb");  // Read as binary to reduce overhead
  
  if(open_file == NULL) { // Error Accessing file or does not exist
    printf("mycp: cannot start: No such file '%s'\n", source_file);
    perror("Error opening file. EXIT.\n");
    return NULL;
  }

  // Memory Allocate to store content & Error Check:
  char* buffer = (char*)malloc(sizeof(char) * (size + 1));
  if(buffer == NULL) {
    fclose(open_file);
    fputs("Error allocating memory. EXIT.\n", stderr);
    return NULL;
  }

  // Store Content into Buffer:
  fgets(buffer, size, open_file);
  //
  // Write NULL Byte at the end of string
  buffer[size] = '\0';
  fclose(open_file);

  return buffer;
}

int GET_FILE_SIZE(char* source_file) {
  /* This function gets the size of the input Source File.
   * Input: Source File
   * Output: size of Source File
  */

  FILE* file = fopen(source_file, "rb");  // Read as binary to reduce overhead
  
  if(file == NULL) { // Error Accessing file or does not exist
    printf("mycp: cannot start: No such file '%s'\n", source_file);
    perror("Error opening file. EXIT.\n");
    return -1;
  }

  long file_size = -1;  // Set to -1 for error handling
 
  // Send cursor to the end of the file & Check:
  if(fseek(file, 0L, SEEK_END) == READ_END) {
    file_size = ftell(file); // Get File Size
    if(file_size == -1) {    // Error Check
      perror("Error getting file size\n");
    }
  } else {                   // If File Size is Garbage or Unknown
      perror("Error seeking end of file\n");
  }
  rewind(file); // Reset cursor position
  fclose(file);

  return file_size;
}

void WRITE_TO_FILE(char* destination_file, char* write_content) {
  /* This function writes to the destination file.
   * Input: Destination File, content to write (extracted from Source File)
   * Output: None
  */

  FILE* file = fopen(destination_file, "wb"); // Write aas binary to reduce overhead

  if(file == NULL) {
    printf("Error opening file. EXIT.\n");
    return;
  } else {
    fputs(write_content, file);
  }

  fclose(file);
}

bool ERROR_HANDLER_UTILITY_CALL(int argc, char** argv) {
  /* Checking Cases:
    *  1. Missing an Operand (No Input After 'my-copy-file' is used).
    *  2. Too many inputs
    *  3. Source inputs are NOT being copied to a directory 
  */
  if(argc == 1) { // No input
    printf("mycp: missing file operand\n Try 'mycp --help' for more information.\n");
    return false;
  }

  else if(argc == 2) {
    if(strcmp(argv[1], "--help") == 0) { // Help Tag for copy file tool:
      printf("Usage: mycp [SOURCE FILE]... [SOURCE FILE]\n");
      printf("Copy SOURCE to DESTINATION\n");
    } else { // Only one argument. Error
      printf("argv: %s\n", argv[1]);
      printf("missing destination file operand after %s\n 'mycp --help' for more information.\n", argv[1]);
    }
    return false;
  }

  else if(argc > 3) {  // Too mnay inputs or directory
    printf("mycp: '%s' is NOT a directory\n", argv[1]);
    return false;
  }

  return true;
}

void GET_RUNTIME(void) {
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Execution Time: %f seconds\n", (cpu_time_used < 0) ? -1*cpu_time_used : cpu_time_used);
}
