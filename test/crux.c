#include "../include/logger.h"
#include "../include/linear_arena.h"

int main() {   
	LinearMemoryArena linear_arena;
	linear_arena_init(&linear_arena, 1024 * 1024);

	LoggerOptions logger_options = {
                .verbose = 0,
                .log_level = "DEBUG",
                .err_log = NULL,
                .out_log = NULL  
        };

	Logger *logger = (Logger *)linear_arena_alloc(&linear_arena, sizeof(Logger));
	logger_init(logger, &logger_options);

	linear_arena_free(&linear_arena);
	return 0;
}

