#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit DONE
  struct header *curr = free_list_ptr;

  // Iterate through free_blocks
  while (curr != NULL) {

    // Return free_blocks id that can fit the data
    if (curr->size >= size) {
      return curr->id;
    }

    // Otherwise move to next free_block
    curr = curr->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  // TODO: Implement best fit
  struct header *curr = free_list_ptr;
  uint64_t best_fit = UINT64_MAX; // Max value that should change with each comparison

  // Iterate through free_blcoks
  while (curr != NULL) {

    // Check if free_block can fit data
    if (curr->size >= size) {

      // Check if it is smaller than current best fit size
      if (curr->size < best_fit) {
        // Update best_fit and best_fit_id
        best_fit = curr->size;
        best_fit_id = curr->id;
      }
    }

    // Move to next free_block
    curr = curr->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  // TODO: Implement worst fit
  struct header *curr = free_list_ptr;
  uint64_t worst_fit = 0; // Min possible value that should change with each comparison

  // Iterate through free_blcoks
  while (curr != NULL) {

    // Check if free_block can fit data
    if (curr->size >= size) {

      // Check if it is greater than current worst fit size
      if (curr->size > worst_fit) {
        // Update worst_fit and worst_fit_id
        worst_fit = curr->size;
        worst_fit_id = curr->id;
      }
    }
    // Move to next free_block
    curr = curr->next;
  }
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  // Free the allocated memory from malloc
  struct header *free_ptr;
  while (free_list_ptr != NULL) {
    free_ptr = free_list_ptr;
    free_list_ptr = free_list_ptr->next;
    free(free_ptr);
  }
  return 0;
}
