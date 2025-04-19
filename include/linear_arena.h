#ifndef CRUX_LINEAR_ARENA_H
#define CRUX_LINEAR_ARENA_H

#define CRUX_LINEAR_ARENA_STATUS_LENGTH 64

#include <stddef.h>
#include <stdint.h>

typedef struct LinearMemoryArena LinearMemoryArena;
typedef struct LinearMemoryArenaStatus {
	size_t size;
	size_t offset;
} LinearMemoryArenaStatus;

LinearMemoryArena *linear_arena_init(const size_t size);
void *linear_arena_alloc(LinearMemoryArena *arena, const size_t size);
void linear_arena_reset(LinearMemoryArena *arena);
void linear_arena_free(LinearMemoryArena *arena);
int linear_arena_status(const LinearMemoryArena *arena,
			LinearMemoryArenaStatus *status);

#endif // CRUX_LINEAR_ARENA_H
