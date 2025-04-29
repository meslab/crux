#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "crux_linear_arena.h"

const size_t MegaByte = (size_t)(1024 * 1024);
static char *error_template = "Error in file %s, function %s, line %d\n";

int test_linear_arena(void) {
	LinearMemoryArena *linear_arena = linear_arena_init(MegaByte);
	if (!linear_arena) {
		printf(error_template, __FILE__, __func__, __LINE__);
		return 1;
	}
	LinearMemoryArenaStatus status = {0};
	linear_arena_status(linear_arena, &status);
	if (!(status.size == MegaByte)) {
		printf(error_template, __FILE__, __func__, __LINE__);
		linear_arena_free(linear_arena);
		return 1;
	}
	if (!(status.offset == 0)) {
		printf(error_template, __FILE__, __func__, __LINE__);
		linear_arena_free(linear_arena);
		return 1;
	}

	int *p_int = (int *)linear_arena_alloc(linear_arena, sizeof(int));
	if (!p_int) {
		printf(error_template, __FILE__, __func__, __LINE__);
		linear_arena_free(linear_arena);
		return 1;
	}
	linear_arena_status(linear_arena, &status);
	if (!(status.offset == 4)) {
		printf(error_template, __FILE__, __func__, __LINE__);
		return 1;
	}

	linear_arena_reset(linear_arena);
	linear_arena_status(linear_arena, &status);
	if (!(status.offset == 0)) {
		printf(error_template, __FILE__, __func__, __LINE__);
		return 1;
	}

	linear_arena_free(linear_arena);

	return 0;
}
