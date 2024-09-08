#define MEM_SIZE 10000
#define BUMP_ALLOC_IMPLEMENTATION
#include "bump.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void use_mem() {
  int *mem_start = ba_alloc_mem(1000);
  assert(mem_start != NULL && "allocd too much mem");
  uint32_t bytes_free = ba_byte_capacity();
  printf("Have %d bytes free\n", bytes_free);

  memset(mem_start, 0, 1000);
  for (int i = 0; i < 1000 / sizeof(int); i++) {
    mem_start[i] = i;
  }

  // now can use mem
  ba_free_mem(1000);
}

int main(int argc, char *argv[]) {

  void *mem_start;
  ba_alloc_mem(100);
  uint32_t bytes_free = ba_byte_capacity();
  printf("Have %d bytes free\n", bytes_free);

  use_mem();

  bytes_free = ba_byte_capacity();
  printf("Have %d bytes free\n", bytes_free);
  ba_free_mem(100);

  bytes_free = ba_byte_capacity();
  printf("Have %d bytes free\n", bytes_free);
  return EXIT_SUCCESS;
}
