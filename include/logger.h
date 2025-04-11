#ifndef LOGGER_H
#define LOGGER_H

#define MESSAGE_LOG_MAX_LENGTH 256

#include <stdint.h>
#include <stdio.h>

typedef struct Logger Logger;

Logger *logger_init(FILE *err_log, FILE *out_log, const char *log_level);
void logger_close(Logger *Logger);

void error_log(Logger *logger, const char *message);
void info_log(Logger *logger, const char *message);
void warning_log(Logger *logger, const char *message);
void debug_log(Logger *logger, const char *message);

void error_log_formatted(Logger *logger, const char *format, ...);
void info_log_formatted(Logger *logger, const char *format, ...);
void warning_log_formatted(Logger *logger, const char *format, ...);
void debug_log_formatted(Logger *logger, const char *format, ...);

#endif // LOGGER_H
