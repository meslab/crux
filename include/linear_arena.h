#ifndef LINEAR_ARENA_H
#define LINEAR_ARENA_H

#include <stddef.h>
#include <stdint.h>

#define ARENA_STATUS_LENGTH 64

typedef struct LinearMemoryArena {
  char status[ARENA_STATUS_LENGTH];
  uint8_t *buffer;
  size_t size;
  size_t offset;
} LinearMemoryArena;

void linear_arena_init(LinearMemoryArena *arena, size_t size);
void *linear_arena_alloc(LinearMemoryArena *arena, size_t size);
void linear_arena_reset(LinearMemoryArena *arena);
void linear_arena_free(LinearMemoryArena *arena);
void linear_arena_status_update(LinearMemoryArena *arena);

#endif // LINEAR_ARENA_H
