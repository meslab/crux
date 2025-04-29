#ifndef CRUX_UTILS_H
#define CRUX_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

int hex_to_uint32(const char *hex_str, uint32_t *arr, int *count,
		  const size_t max_count);

int to_upper_case(char *str);

#ifdef __cplusplus
}
#endif

#endif // CRUX_UTILS_H
