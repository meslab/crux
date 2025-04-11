#include "linear_arena.h"
#include "logger.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const size_t MegaByte = (size_t)(1024 * 1024);

int main(void) {
	LinearMemoryArena *linear_arena = linear_arena_init(MegaByte);

	Logger *logger = logger_init(NULL, NULL, "INFO");
	if (!logger) {
		perror("Cannot allocate logger!");
		return -1;
	}

	linear_arena_reset(linear_arena);

	logger_close(logger);
	linear_arena_free(linear_arena);

	return 0;
}
