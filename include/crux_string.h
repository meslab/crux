#ifndef CRUX_STRING_H
#define CRUX_STRING_H

#include <stddef.h>
#include <string.h>

typedef struct CruxString CruxString;

CruxString *crux_string_of_size(const size_t size);
CruxString *crux_string_new(void);
CruxString *crux_string_from_str(const char *str);

void crux_string_delete(CruxString *string);

#endif // !CRUX_STRING_H
