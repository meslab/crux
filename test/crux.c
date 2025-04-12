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
	printf("linear_arena: %p\n", (void *)linear_arena);
	LinearMemoryArenaStatus status = {0};
	linear_arena_status(linear_arena, &status);
	assert(status.size == MegaByte);
	assert(status.offset == 0);
	printf("Arena size: %ld, offset: %ld\n", status.size, status.offset);

	Logger *logger = logger_init(NULL, NULL, "INFO");
	printf("logger: %p\n", (void *)logger);
	Logger *logger1 = logger_init(NULL, NULL, "INFO");
	assert(logger1);
	printf("logger1: %p\n", (void *)logger1);

	int *p_int = (int *)linear_arena_alloc(linear_arena, sizeof(int));
	assert(p_int);
	printf("p_int: %p\n", (void *)p_int);
	linear_arena_status(linear_arena, &status);
	printf("Arena size: %ld, offset: %ld\n", status.size, status.offset);

	linear_arena_reset(linear_arena);
	assert(linear_arena);

	logger_close(logger);
	linear_arena_free(linear_arena);

	return 0;
}
