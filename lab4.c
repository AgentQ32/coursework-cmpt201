#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {

  void *current_break;
  void *next_break;
  size_t allocate_size = 256;            // Allocate 256 bytes
  size_t block_size = allocate_size / 2; // Header + data

  // Check if block size can store at least size of header
  if (block_size < sizeof(struct header)) {
    perror("Not enough memory for struct header");
    return NULL;
  }

  // Calculate remaining size for data
  size_t data_block_size = block_size - sizeof(struct header);

  // Current program break
  current_break = sbrk(0);
  if (current_break == (void *)-1) {
    perror("sbrk(0) failed");
    return 1;
  }

  // Increase size of heap
  next_break = sbrk(allocate_size);

  if (next_break == (void *)-1) {
    perror("sbrk() failed");
    return 1;
  }

  struct header *first_blk = (struct header *)current_break;
  first_blk->size = data_block_size;
  first_blk->next = NULL;

  struct header *second_blk = (struct header *)((char *)first_blk + block_size);
  second_blk->size = data_block_size;
  second_blk->next = first_blk;

  print_out("Struct first block size: %p\n", &first_blk, sizeof(&first_blk));
}
