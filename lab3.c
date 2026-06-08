#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5

// Function Declaration
void freeHistory(char *inputHist[], int count);
void printHistory(char *inputHist[], int count, int next);
void storeHistory(char *inputHist[], int *count, int *next, const char *userInput);

int main() {
  char *inputHist[HISTORY_SIZE] = {NULL}; // Array of ptrs to each line input
  int count = 0;                          // Count of user inputs
  int next = 0;                           // Index for next line
  char *userInput = NULL;
  size_t size = 0;
  ssize_t line;

  printf("Enter input: ");

  // Read from standard input for user Input
  while ((line = getline(&userInput, &size, stdin)) != -1) {

    // Remove newline character
    if (userInput[line - 1] == '\n') {
      userInput[line - 1] = '\0';
    }

    // Call function to copy userInput to inputHist array
    // Pass in address of count and next to update their values
    storeHistory(inputHist, &count, &next, userInput);

    // Call function to print input history
    if (strcmp(userInput, "print") == 0) {
      printHistory(inputHist, count, next);
    }

    printf("Enter input: ");
  }

  // Free allocated memory
  // For ternary op check if need to free only up to count or the whole size of history
  free(userInput);
  freeHistory(inputHist, (count < HISTORY_SIZE) ? count : HISTORY_SIZE);

  return 0;
}

// Free function to free memory for array used to store pointers
void freeHistory(char *inputHist[], int count) {
  for (int i = 0; i < count; i++) {
    free(inputHist[i]);
  }
}

// Function that prints out the last HISTORY_SIZE inputs
void printHistory(char *inputHist[], int count, int next) {

  // Checks where the start of user input is
  // index 0 if HISTORY_SIZE hasnt been reached
  // or index next if wrapped around
  int head = (count < HISTORY_SIZE) ? 0 : next;

  // Print out user input starting from oldest input
  for (int i = 0; i < count; i++) {
    int index = (head + i) % HISTORY_SIZE;
    printf("%s\n", inputHist[index]);
  }
}

// Function that stores pointers to user inputs in an array
void storeHistory(char *inputHist[], int *count, int *next, const char *userInput) {
  // Use strdup to duplicate line into inputHist[]
  inputHist[*next] = strdup(userInput);

  // Increment index to store next line
  // Since only 5 inputs are needed for history
  // Wrap around to start when count of user inputs > 5
  *next = (*next + 1) % HISTORY_SIZE;
  if (*count < HISTORY_SIZE) {
    (*count)++;
  }
}
