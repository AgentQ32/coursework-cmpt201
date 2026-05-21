#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *buff = NULL;
  size_t size = 0;
  ssize_t num_char;
  char *saveptr;

  printf("Please enter some text: ");
  num_char = getline(&buff, &size, stdin);
  printf("\n");

  // Error Handling
  if (num_char == -1) {
    perror("getline failed");
    exit(EXIT_FAILURE);
  }

  // Test getline()
  // printf("Num_char: %ld", num_char);

  printf("Tokens: \n");

  // Removes the newline char
  // and replaces it with null terminator
  if (buff[num_char - 1] == '\n') {
    buff[num_char - 1] = '\0';
    num_char--;
  }

  char *token = strtok_r(buff, " ", &saveptr);

  while (token != NULL) {
    printf("%s\n", token);

    token = strtok_r(NULL, " ", &saveptr);
  }
  free(buff);
}
