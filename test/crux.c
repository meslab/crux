#include "linear_arena.h"
#include "logger.h"
#include "utils.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const size_t MegaByte = (size_t)(1024 * 1024);

int main(void) {
	LinearMemoryArena *linear_arena = linear_arena_init(MegaByte);
	assert(linear_arena);
	printf("linear_arena: %p\n", (void*)linear_arena);

	Logger *logger = logger_init(NULL, NULL, "INFO");
	assert(logger);
	printf("logger: %p\n", (void*)logger);

	if (!logger) {
		perror("Cannot allocate logger!");
		return -1;
	}

	int *p_int = (int*)linear_arena_alloc(linear_arena, sizeof(int));
	assert(p_int);
	printf("p_int: %p\n", (void*)p_int);

	linear_arena_reset(linear_arena);
	assert(linear_arena);

	logger_close(logger);
	assert(!logger);
	linear_arena_free(linear_arena);
	assert(!linear_arena);

	return 0;
}
