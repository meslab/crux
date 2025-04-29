#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crux_linear_arena.h"

typedef struct LinearMemoryArena {
	uint8_t *buffer;
	size_t size;
	size_t offset;
} LinearMemoryArena;

LinearMemoryArena *linear_arena_init(const size_t size) {
	LinearMemoryArena *arena =
	    (LinearMemoryArena *)calloc(1, sizeof(LinearMemoryArena));
	arena->buffer = (uint8_t *)calloc(1, size);
	if (arena->buffer == NULL) {
		perror("Failed to allocate memory for arena");
		fprintf(stderr, "errno: %d, strerror: %s\n", errno,
			strerror(errno));
		free(arena);
		exit(EXIT_FAILURE);
	}
	arena->size = size;
	arena->offset = 0;
	return arena;
}

void *linear_arena_alloc(LinearMemoryArena *arena, const size_t size) {
	if (arena->offset + size > arena->size) {
		fprintf(stderr, "Out of memory in arena\n");
		exit(EXIT_FAILURE);
	}
	void *ptr = &arena->buffer[arena->offset];
	arena->offset += size;
	memset(ptr, 0, size);
	return ptr;
}

void linear_arena_reset(LinearMemoryArena *arena) {
	memset(arena->buffer, 0, arena->offset);
	arena->offset = 0;
}

void linear_arena_free(LinearMemoryArena *arena) {
	free(arena->buffer);
	arena->buffer = NULL;
	arena->size = 0;
	arena->offset = 0;
	free(arena);
}

int linear_arena_status(const LinearMemoryArena *arena,
			LinearMemoryArenaStatus *status) {
	if (!status)
		return 0;
	status->size = arena->size;
	status->offset = arena->offset;
	return 1;
}
