#include "linear_arena.h"
#include "logger.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const size_t MegaByte = (size_t)(1024 * 1024);

int main(void) {
	LinearMemoryArena linear_arena = {0};
	linear_arena_init(&linear_arena, MegaByte);

	Logger *logger =
	    (Logger *)linear_arena_alloc(&linear_arena, sizeof(Logger));
	Logger *logger1 = (Logger *)malloc(sizeof(Logger));
	if (!logger1) {
		perror("Cannot allocate logger!");
		return -1;
	}
	logger_init(logger, NULL, NULL, "INFO");
	logger_init(logger1, NULL, NULL, "INFO");

	Logger logger2 = {.err_log = NULL, .out_log = NULL, .level = LOG_ERROR};
	logger_init(&logger2, NULL, NULL, "INFO");

	linear_arena_status_update(&linear_arena);
	info_log(logger, linear_arena.status);
	info_log(logger1, linear_arena.status);
	info_log(&logger2, linear_arena.status);

	linear_arena_reset(&linear_arena);
	linear_arena_status_update(&linear_arena);

	// Cleanup
	logger_close(logger);

	info_log(logger1, linear_arena.status);
	info_log(&logger2, linear_arena.status);

	logger_close(logger1);
	logger_close(&logger2);

	free(logger1);
	linear_arena_free(&linear_arena);

	return 0;
}
