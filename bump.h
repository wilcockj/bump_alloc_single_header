#pragma once

#include <stddef.h>
#include <stdint.h>

void *ba_alloc_mem(size_t n_bytes);
int ba_free_mem(size_t n_bytes);
uint32_t ba_byte_capacity();

#ifdef BUMP_ALLOC_IMPLEMENTATION

// bump allocator
#ifndef MEM_SIZE
#define MEM_SIZE 10000
#pragma message                                                                \
    "Setting mem size to #MEM_SIZE #define MEM_SIZE above BUMP_ALLOC_IMPLEMENTATION to change"
#endif

typedef struct {
  uint8_t mem[MEM_SIZE];
  void *mem_pointer;
} Bump_Mem;

Bump_Mem mem;

void *ba_alloc_mem(size_t n_bytes) {
  if (mem.mem_pointer == NULL) {
    mem.mem_pointer = &mem.mem[0];
  }

  if ((mem.mem_pointer + n_bytes) - (void *)&mem.mem[0] > MEM_SIZE) {
    // too much mem
    return NULL;
  }
  mem.mem_pointer += n_bytes;
  return mem.mem_pointer - n_bytes;
}

int ba_free_mem(size_t n_bytes) {
  if ((mem.mem_pointer - n_bytes) < (void *)&mem.mem[0]) {
    // freed too far
    return -1;
  }
  mem.mem_pointer -= n_bytes;
  return 0;
}

uint32_t ba_byte_capacity() {
  if (mem.mem_pointer == NULL) {
    mem.mem_pointer = &mem.mem[0];
  }
  return MEM_SIZE - (mem.mem_pointer - (void *)&mem.mem[0]);
}

#endif
