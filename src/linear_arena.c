#include "linear_arena.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinearMemoryArena {
	uint8_t *buffer;
	size_t size;
	size_t offset;
} LinearMemoryArena;

/// @brief Initialize a memory arena
/// @param arena The memory arena to initialize
/// @param size  The size of the memory arena in bytes
LinearMemoryArena *linear_arena_init(size_t size) {
	LinearMemoryArena *arena =
	    (LinearMemoryArena *)calloc(1, sizeof(LinearMemoryArena));
	arena->buffer = (uint8_t *)calloc(1, size);
	if (arena->buffer == NULL) {
		perror("Failed to allocate memory for arena");
		fprintf(stderr, "errno: %d, strerror: %s\n", errno,
			strerror(errno));
		exit(EXIT_FAILURE);
	}
	arena->size = size;
	arena->offset = 0;
	return arena;
}

/// @brief Allocate memory from the arena
/// @param arena The memory arena to allocate from
/// @param size  The size of the memory to allocate
/// @return A pointer to the allocated memory
void *linear_arena_alloc(LinearMemoryArena *arena, size_t size) {
	if (arena->offset + size > arena->size) {
		fprintf(stderr, "Out of memory in arena\n");
		exit(EXIT_FAILURE);
	}
	void *ptr = &arena->buffer[arena->offset];
	arena->offset += size;
	memset(ptr, 0, size);
	return ptr;
}

/// @brief  Reset the memory arena
/// @param arena The memory arena to reset to the beginning of the buffer
void linear_arena_reset(LinearMemoryArena *arena) {
	memset(arena->buffer, 0, arena->offset);
	arena->offset = 0;
}

/// @brief Free the memory allocated for the arena
/// @param arena The memory arena to free
void linear_arena_free(LinearMemoryArena *arena) {
	free(arena->buffer);
	arena->buffer = NULL;
	arena->size = 0;
	arena->offset = 0;
	free(arena);
}
