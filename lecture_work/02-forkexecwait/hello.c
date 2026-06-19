#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

  pid_t p;

  p = fork();

  if (p <= -1) {
    perror("error: fork failed");
    exit(EXIT_FAILURE);
  } else if (p == 0) {
    printf("Hello from child!\n");
    printf("child PID: %d\n", getpid());
    printf("parent PID: %d\n", getppid());
  } else {
    printf("Hello from parent!\n");
  }

  // printf("Hello World!\n");
  // while (true) {
  //   sleep(10);
  //   printf("still going...\n");
  // }
}
