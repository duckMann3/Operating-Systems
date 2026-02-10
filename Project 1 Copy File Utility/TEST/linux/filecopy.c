#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdbool.h>

#define READ_END  0
#define WRITE_END 1

#define EXIT      1

bool FILE_EXISTS_fOPEN(const char* input_file);

int main(int argc, char* argv[]) {
  
  if(argc > 3) {
    printf("my-copy-file: '%s' is NOT a directory", argv[3]);
    return EXIT;
  }

  for(int i = 1; i < argc; i++) {
    if(!FILE_EXISTS_fOPEN(argv[1])) {
      printf("my-copy-file: cannot stat '%s': No such file or directory", argv[1]);
      return 1;
    } else { // Open the source file in read() & open destination file in write mode 
      FILE* file;
      fptr = fopen(argv[1], "r");
      fptr = fopen(argv[1], "r");

    }

    printf("%s\n", argv[i]);
  }
  return 0;
}

bool FILE_EXISTS_fOPEN(const char* input_file) {
  FILE* file;

  // Try to open the file in read mode
  if((file = fopen(input_file, "r")) != NULL) {
    fclose(file);
    // If successful, close the file and return true
    return true;
  } else {
    // If fopen returns NULL, the file does NOT exist (cannot open)
    return false;
  }
}
