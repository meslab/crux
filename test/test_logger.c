#include "logger.h"
#include <assert.h>
#include <stdio.h>

static char *error_template = "Error in file %s, function %s, line %d\n";

int test_logger(void) {
	Logger *logger = logger_init(NULL, NULL, "INFO");
	if (!logger) {
		printf(error_template, __FILE__, __func__, __LINE__);
		return 1;
	}
	Logger *logger1 = logger_init(NULL, NULL, "INFO");
	if (!logger1) {
		printf(error_template, __FILE__, __func__, __LINE__);
		return 1;
	}

	logger_close(logger1);
	logger_close(logger);

	return 0;
}
