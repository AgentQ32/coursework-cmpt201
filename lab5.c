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

/*
 * Pseudococde for Coalescing Contiguous Free Blocks
 * Notes: Struct header must now have a flag is_free to indicate if a block is freed or not
 * Need to merge both previous and next neighbors if they are free
 * If all is freed and everything is just one block no need to do anything
 * two new functions 1. to free and check if the memory blocks can merge
 * 2. to merge memory blocks called upon by 1st function
 *
 * FUNCTION coalesce(free_list_ptr, free_blk):
 * free_blk.is_free = true
 * free_blk.next = free_list_ptr
 * free_list_ptr = free_blk
 *
 * SET prev = NULL
 * SET curr = free_list_ptr
 *
 * // Iterate through list to find free neighbors
 * WHILE curr is NOT NULL
 * // Find end points of current block and the free block
 * SET curr_end = AddressOF(curr) + sizeof(header)_ + curr.size
 * SET free_blk_end = AddressOf(free_blk) + sizeof(header) + free_blk.size
 *
 * // When current block is before the free block
 * IF curr_end == AddressOf(free_blk)
 *    // Merge free_blk to its prev neighbor current
 *    curr.size = sizeof(header) + curr.size + free_blk.size
 *
 *    // free the free_blk
 *    free_list_ptr = free_blk.next
 *    FUNCTION CALL free(free_blk)
 *
 *    // Current block now is the new free block
 *    free_blk = current
 *
 *    curr = free_list_ptr
 *    prev = NULL
 *    CONTINUE
 *
 * // When current block is after the free block
 * ELSE IF free_blk_end == AddressOf(curr)
 *    // Merge free_blk into its next neighbor current
 *    free_blk.size = sizeof(header) + free_blk.size + curr.size
 *
 *    // free current block
 *    IF prev is NOT NULL
 *      prev.next = curr.next
 *    ELSE
 *      free_list_ptr = curr.next
 *
 *    SET copy = curr
 *    curr = curr.next
 *    FUNCTION CALL free(copy)
 *
 * ENDFUNCTION*/
