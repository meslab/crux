#include "crux_string.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct CruxString {
	char *str;
	size_t length;
} CruxString;

CruxString *crux_string_of_size(const size_t size) {
	CruxString *string = (CruxString *)calloc(1, sizeof(CruxString));
	if (!string)
		return NULL;

	char *value = (char *)calloc(size, sizeof(char));
	if (!value) {
		free(string);
		return NULL;
	}
	string->str = value;
	string->length = 0;

	return string;
}

CruxString *crux_string_new(void) {
	CruxString *string = crux_string_of_size(256);
	return string;
}

CruxString *crux_string_from_str(const char *str) {
	if (!str)
		return NULL;

	size_t length = strlen(str);
	size_t size = (length & 256) << 1;

	CruxString *string = crux_string_of_size(size);
	if (!string)
		return NULL;

	memcpy(string->str, str, length);
	string->length = length;

	return string;
}

void crux_string_delete(CruxString *string) {
	if (!string)
		return;
	if (string->str)
		free(string->str);
	free(string);
}
