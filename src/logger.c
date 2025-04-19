#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "logger.h"

#define MESSAGE_LOG_MAX_LENGTH 256

typedef enum { LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR } LogLevel;

typedef struct Logger {
	FILE *err_log;
	FILE *out_log;
	LogLevel level;
} Logger;

static Logger logger = {0};

void message_log(const Logger *logger, const LogLevel level,
		 const char *message);

const char *log_level_str(LogLevel level) {
	switch (level) {
	case LOG_DEBUG:
		return "DEBUG";
	case LOG_INFO:
		return "INFO";
	case LOG_WARNING:
		return "WARNING";
	default:
		return "ERROR";
	}
}

LogLevel parse_log_level(const char *level_str) {
	if (strcmp(level_str, "DEBUG") == 0 || strcmp(level_str, "D") == 0)
		return LOG_DEBUG;
	if (strcmp(level_str, "INFO") == 0 || strcmp(level_str, "I") == 0)
		return LOG_INFO;
	if (strcmp(level_str, "WARNING") == 0 || strcmp(level_str, "W") == 0)
		return LOG_WARNING;
	return LOG_ERROR;
}

void message_log(const Logger *logger, const LogLevel level,
		 const char *message) {
	if (level < logger->level)
		return;

	FILE *dest = (level == LOG_ERROR)
			 ? (logger->err_log ? logger->err_log : stderr)
			 : (logger->out_log ? logger->out_log : stdout);

	time_t now = time(NULL);
	struct tm tm_info = {0};
	localtime_r(&now, &tm_info);
	char time_buf[20] = {0}; // YYYY-MM-DD HH:MM:SS
	strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", &tm_info);

	fprintf(dest, "[%s] [%s] %s\n", time_buf, log_level_str(level),
		message);
	fflush(dest);
}

Logger *logger_init(FILE *err_log, FILE *out_log, const char *log_level) {
	if (!log_level)
		return NULL;
	if (logger.level)
		return &logger;

	logger.err_log = err_log;
	logger.out_log = out_log;
	logger.level = LOG_ERROR;

	// Set the log level
	logger.level = parse_log_level(log_level ? log_level : "ERROR");

	return &logger;
}

void logger_close(Logger *logger) {
	if (logger->level) {
		if (logger->err_log)
			fclose(logger->err_log);
		if (logger->out_log)
			fclose(logger->out_log);
		logger->err_log = logger->out_log = NULL;
	}
}

void error_log(const Logger *logger, const char *message) {
	message_log(logger, LOG_ERROR, message);
}

void info_log(const Logger *logger, const char *message) {
	message_log(logger, LOG_INFO, message);
}

void warning_log(const Logger *logger, const char *message) {
	message_log(logger, LOG_WARNING, message);
}

void debug_log(const Logger *logger, const char *message) {
	message_log(logger, LOG_DEBUG, message);
}

void error_log_formatted(const Logger *logger, const char *format, ...) {
	if (LOG_ERROR < logger->level)
		return;

	char log_buffer[MESSAGE_LOG_MAX_LENGTH];
	va_list args;
	va_start(args, format);
	vsnprintf(log_buffer, MESSAGE_LOG_MAX_LENGTH, format, args);
	va_end(args);

	message_log(logger, LOG_ERROR, log_buffer);
}

void info_log_formatted(const Logger *logger, const char *format, ...) {
	if (LOG_INFO < logger->level)
		return;

	char log_buffer[MESSAGE_LOG_MAX_LENGTH];
	va_list args;
	va_start(args, format);
	vsnprintf(log_buffer, MESSAGE_LOG_MAX_LENGTH, format, args);
	va_end(args);

	message_log(logger, LOG_INFO, log_buffer);
}

void warning_log_formatted(const Logger *logger, const char *format, ...) {
	if (LOG_WARNING < logger->level)
		return;

	char log_buffer[MESSAGE_LOG_MAX_LENGTH];
	va_list args;
	va_start(args, format);
	vsnprintf(log_buffer, MESSAGE_LOG_MAX_LENGTH, format, args);
	va_end(args);

	message_log(logger, LOG_WARNING, log_buffer);
}

void debug_log_formatted(const Logger *logger, const char *format, ...) {
	if (LOG_DEBUG < logger->level)
		return;

	char log_buffer[MESSAGE_LOG_MAX_LENGTH];
	va_list args;
	va_start(args, format);
	vsnprintf(log_buffer, MESSAGE_LOG_MAX_LENGTH, format, args);
	va_end(args);

	message_log(logger, LOG_DEBUG, log_buffer);
}
