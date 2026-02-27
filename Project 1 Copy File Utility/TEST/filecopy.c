#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdbool.h>

#define READ_END  0
#define WRITE_END 1

#define EXIT      1
#define SUCCESS  0

bool FILE_EXISTS_fOPEN(char* input_file);
bool ERROR_HANDLER_UTILITY_CALL(int argc, char** argv);

char* READ_ENTIRE_FILE(char* file, int file_size);
int   GET_FILE_SIZE(char* file); 


int main(int argc, char* argv[]) {
  printf("You have entered %d arguments:\n", argc);

  for(int i = 0; i < argc; i++) {
    printf("%d %s\n", i, argv[i]);
  }
  if(!ERROR_HANDLER_UTILITY_CALL(argc, argv)) {
    /* ERROR HANDLER:
     * Cases:
     *  1. Missing an Operand (No Input After 'my-copy-file' is used).
     *  2. Too many inputs
     *  3. Source file for copying does NOT exist
     */
    return EXIT;
  }
  
  // if(arg[1] == '--help') {

  // }

  printf("Passed\n");

  int pipefds[2];
  int return_status;
  int pid;

  char* source_file = argv[1];
  int file_size = GET_FILE_SIZE(argv[1]);
  char* read_source_file;   
  char* write_destination_file = malloc(file_size + 1);
  read_source_file = READ_ENTIRE_FILE(source_file, file_size);

  printf("file size: %d\n", file_size);

  return_status = pipe(pipefds);

  if(return_status == -1) {
    printf("Unable to create pipe\n");
    return EXIT;
  }
  
  pid = fork();

  // Child Process
  if(pid == 0) {
    read(pipefds[0], write_destination_file, sizeof(write_destination_file));
    printf("Child Process Output: %s\n", write_destination_file);
  } else {
    write(pipefds[1], read_source_file, sizeof(read_source_file)); // Write "read_source_file" into pipe
    printf("Parent Process Output: %s\n", read_source_file);
  }

  // free(read_source_file);
  free(write_destination_file);
  read_source_file = NULL;
  write_destination_file = NULL;
  return SUCCESS;
}

char* READ_ENTIRE_FILE(char* file, int file_size) {
  FILE* source_file = fopen(file, "r"); 
  if(source_file == NULL) {
    perror("Error opening file");
    return NULL;
  }


  char* buffer = (char*)malloc(sizeof(char) * (file_size + 1));
  if(buffer == NULL) {
    fclose(source_file);
    fputs("Error allocating memory", stderr);
    return NULL;
  }

  fgets(buffer, file_size, source_file);

  fclose(source_file);

  buffer[file_size] = '\0';

  printf("Output buffer: %s\n\n", buffer);
  return buffer;
}

int GET_FILE_SIZE(char* file) {
  FILE* source_file = fopen(file, "r");
  long file_size = -1;
 
  if(fseek(source_file, 0L, SEEK_END) == 0) { 
    file_size = ftell(source_file);
    if(file_size == -1) { 
      perror("Error getting file size\n");
    }
  } else {
      perror("Error seeking end of file\n");
  }
  rewind(source_file);
  fclose(source_file);
  return file_size;
}


bool ERROR_HANDLER_UTILITY_CALL(int argc, char** argv) {
  if(argc == 1) {
    printf("my-copy-file: missing file operand\n Try 'my-copy-file --help' for more information.\n");
  }

  else if(argc == 2) {
    printf("missing destination file operand after %s\n 'my-copy-file --help' for more information.\n", argv[1]);
  }

  else if(argc > 4) {
    printf("my-copy-file: '%s' is NOT a directory\n", argv[1]);
  }

  else if(!FILE_EXISTS_fOPEN(argv[1])) {
      printf("my-copy-file: cannot start '%s': No such file or directory\n", argv[1]);
  } 
  return EXIT;
}

bool FILE_EXISTS_fOPEN(char* input_file) {
  FILE* file;
  file = fopen(input_file, "r");

  // Try to open the file in read mode
  if(file != NULL) {
    fclose(file);
    // If successful, close the file and return true
    return true;
  } else {
    // If fopen returns NULL, the file does NOT exist (cannot open)
    return false;
  }
}
