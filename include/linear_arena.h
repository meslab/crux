#ifndef LINEAR_ARENA_H
#define LINEAR_ARENA_H

#include <stddef.h>
#include <stdint.h>

typedef struct LinearMemoryArena LinearMemoryArena;

LinearMemoryArena *linear_arena_init(size_t size);
void *linear_arena_alloc(LinearMemoryArena *arena, size_t size);
void linear_arena_reset(LinearMemoryArena *arena);
void linear_arena_free(LinearMemoryArena *arena);

#endif // LINEAR_ARENA_H
