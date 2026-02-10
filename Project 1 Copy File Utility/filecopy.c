#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END  0
#define WRITE_END 1

int main(int argc, char* argv[]) {
  if(argc > 3) {
    printf("my-copy-file: '%s' is NOT a directory", argv[3]);
    return 1;
  }
  for(int i = 0; i < argc; i++) {

  }
  return 0;
}
