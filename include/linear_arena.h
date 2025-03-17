#ifndef LINEAR_ARENA_H
#define LINEAR_ARENA_H

#include "../include/logger.h"
#include <stddef.h>
#include <stdint.h>

typedef struct LinearMemoryArena {
  uint8_t *buffer;
  size_t size;
  size_t offset;
} LinearMemoryArena;

void linear_arena_init(LinearMemoryArena *arena, size_t size);
void *linear_arena_alloc(LinearMemoryArena *arena, size_t size);
void linear_arena_reset(LinearMemoryArena *arena);
void linear_arena_free(LinearMemoryArena *arena);
void linear_arena_info(Logger *logger, LinearMemoryArena *arena);

#endif // LINEAR_ARENA_H
