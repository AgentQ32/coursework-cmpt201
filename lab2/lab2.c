#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {

  char *buff = NULL;
  size_t size = 0;
  ssize_t num_char;
  char *saveptr;

  printf("Enter programs to run. \n");
  num_char = getline(&buff, &size, stdin);
  printf("\n");

  // Error Handling
  if (num_char == -1) {
    perror("getline failed.");
    exit(EXIT_FAILURE);
  }

  char *token = strtok_r(buff, "/", &saveptr);

  char *lastToken;

  while (token != NULL) {
    printf("%s\n", token);
    lastToken = strtok_r(NULL, "/", &saveptr);
  }

  int command = execl("%s", "%s", NULL, token, lastToken);

  // Error Handling
  if (command == -1) {
    perror("execl failed.");
    exit(EXIT_FAILURE);
  }

  free(buff);
  exit(EXIT_SUCCESS);
}
