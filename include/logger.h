#ifndef CRUX_LOGGER_H
#define CRUX_LOGGER_H

#include <stdio.h>

typedef struct Logger Logger;

Logger *logger_init(FILE *err_log, FILE *out_log, const char *log_level);
void logger_close(Logger *Logger);

void error_log(const Logger *logger, const char *message);
void info_log(const Logger *logger, const char *message);
void warning_log(const Logger *logger, const char *message);
void debug_log(const Logger *logger, const char *message);

void error_log_formatted(const Logger *logger, const char *format, ...);
void info_log_formatted(const Logger *logger, const char *format, ...);
void warning_log_formatted(const Logger *logger, const char *format, ...);
void debug_log_formatted(const Logger *logger, const char *format, ...);

#endif // CRUX_LOGGER_H
