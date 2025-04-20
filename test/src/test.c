#include "test_linear_arena.h"
#include "test_logger.h"
#include <stdio.h>
#include <string.h>

#define DIVIDER_LINE_LENGTH 40

void test_divider(void) {
	char line[DIVIDER_LINE_LENGTH + 1];
	memset(line, '=', DIVIDER_LINE_LENGTH);
	line[DIVIDER_LINE_LENGTH] = '\0';
	printf("%s\n", line);
}

static int total_tests = 0, failed_tests = 0;

int main(void) {
	total_tests++;
	failed_tests += test_linear_arena();

	total_tests++;
	failed_tests += test_logger();

	test_divider();
	printf("%d tests failed out of total %d tests\n", failed_tests,
	       total_tests);
	return 0;
}
