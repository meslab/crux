#include "logger.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * @brief Get the string representation of a log level
 *
 * @param level The log level
 * @return const char* The string representation of the log level
 */
const char *log_level_str(LogLevel level) {
	switch (level) {
		case DEBUG:
			return "DEBUG";
		case INFO:
			return "INFO";
		case WARNING:
			return "WARNING";
		default:
			return "ERROR";
	}
}

/**
 * @brief Parse a string to a log level
 *
 * @param level_str The string representation of the log level
 * @return LogLevel The log level
 */
LogLevel parse_log_level(const char *level_str) {
	if (strcmp(level_str, "DEBUG") == 0 || strcmp(level_str, "D") == 0)
		return DEBUG;
	if (strcmp(level_str, "INFO") == 0 || strcmp(level_str, "I") == 0)
		return INFO;
	if (strcmp(level_str, "WARNING") == 0 || strcmp(level_str, "W") == 0)
		return WARNING;
	return ERROR;
}

/**
 * @brief Log a message to the appropriate destination
 *
 * @param logger The logger
 * @param level The log level
 * @param message The message to log
 */
void message_log(Logger *logger, const LogLevel level, const char *message) {
	if (level < logger->level)
		return;

	FILE *dest = (level == ERROR) ? (logger->err_log ? logger->err_log : stderr)
		: (logger->out_log ? logger->out_log : stdout);

	time_t now = time(NULL);
	struct tm *tm_info = localtime(&now);
	char time_buf[20] = {0}; // YYYY-MM-DD HH:MM:SS
	strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);

	fprintf(dest, "[%s] [%s] %s\n", time_buf, log_level_str(level), message);
	fflush(dest);
}

/**
 * @brief Initialize the logger
 *
 * @param logger The logger
 * @param opts The options
 * @return int 0 on success, -1 on failure
 */
int logger_init(Logger *logger, FILE *err_log, FILE *out_log, const char *log_level) {
	if (!logger)
		return -1;

	logger->err_log = err_log;
	logger->out_log = out_log;
	logger->level = ERROR;

	// Set the log level
	logger->level = parse_log_level(log_level ? log_level : "ERROR");


	return 0; // Success
}

/**
 * @brief Close the logger
 *
 * @param logger The logger
 */
void logger_close(Logger *logger) {
	if (logger) {
		if (logger->err_log)
			fclose(logger->err_log);
		if (logger->out_log)
			fclose(logger->out_log);
		logger->err_log = logger->out_log = NULL;
	}
}

/// @brief Log an error message
/// @param logger  The logger
/// @param message The message to log
void error_log(Logger *logger, const char *message) {
	message_log(logger, ERROR, message);
}

/// @brief Log an info message
/// @param logger  The logger
/// @param message The message to log
void info_log(Logger *logger, const char *message) {
	message_log(logger, INFO, message);
}

/// @brief Log a warning message
/// @param logger  The logger
/// @param message The message to log
void warning_log(Logger *logger, const char *message) {
	message_log(logger, WARNING, message);
}

/// @brief Log a debug message
/// @param logger  The logger
/// @param message The message to log
void debug_log(Logger *logger, const char *message) {
	message_log(logger, DEBUG, message);
}

/// @brief Log an error message with a formatted string
/// @param logger The logger
/// @param format The format string
/// @param    ... The format arguments
void error_log_formatted(Logger *logger, const char *format, ...) {
	if (ERROR < logger->level)
		return;

	char log_buffer[MESSAGE_LOG_MAX_LENGTH];
	va_list args;
	va_start(args, format);
	vsnprintf(log_buffer, MESSAGE_LOG_MAX_LENGTH, format, args);
	va_end(args);

	message_log(logger, ERROR, log_buffer);
}

/// @brief Log an info message with a formatted string
/// @param logger The logger
/// @param format The format string
/// @param    ... The format arguments
void info_log_formatted(Logger *logger, const char *format, ...) {
	if (INFO < logger->level)
		return;

	char log_buffer[MESSAGE_LOG_MAX_LENGTH];
	va_list args;
	va_start(args, format);
	vsnprintf(log_buffer, MESSAGE_LOG_MAX_LENGTH, format, args);
	va_end(args);

	message_log(logger, INFO, log_buffer);
}

/// @brief Log an warning message with a formatted string
/// @param logger The logger
/// @param format The format string
/// @param    ... The format arguments
void warning_log_formatted(Logger *logger, const char *format, ...) {
	if (WARNING < logger->level)
		return;

	char log_buffer[MESSAGE_LOG_MAX_LENGTH];
	va_list args;
	va_start(args, format);
	vsnprintf(log_buffer, MESSAGE_LOG_MAX_LENGTH, format, args);
	va_end(args);

	message_log(logger, WARNING, log_buffer);
}

/// @brief Log a debug message with a formatted string
/// @param logger The logger
/// @param format The format string
/// @param    ... The format arguments
void debug_log_formatted(Logger *logger, const char *format, ...) {
	if (DEBUG < logger->level)
		return;

	char log_buffer[MESSAGE_LOG_MAX_LENGTH];
	va_list args;
	va_start(args, format);
	vsnprintf(log_buffer, MESSAGE_LOG_MAX_LENGTH, format, args);
	va_end(args);

	message_log(logger, DEBUG, log_buffer);
}
