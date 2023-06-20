/*
** EPITECH PROJECT, 2023
** zappy log
** File description:
** header
*/

#ifndef LLOG_H
    #define LLOG_H

    #include <stdarg.h>

    #define MAX_CHAR_VALUES 20

    #define LOG_FILE_NETWORK ".network.log"
    #define LOG_FILE_AIC ".ai_client.log"
    #define LOG_FILE_GUIC ".gui_client.log"
    #define LOG_FILE_SERVER ".server.log"

enum llog_level {
    LLOG_FATAL = 0,
    LLOG_ERROR = 1,
    LLOG_WARNING = 2,
    LLOG_INFO = 3,
    LLOG_DEBUG = 4,
    LLOG_TRACE = 5,
    LLOG_FATAL_COLOR = 6,
    LLOG_ERROR_COLOR = 7,
    LLOG_WARNING_COLOR = 8,
    LLOG_INFO_COLOR = 9,
    LLOG_DEBUG_COLOR = 10,
    LLOG_TRACE_COLOR = 11,
    MAX_LLOG_LEVEL = 12
};

/**
** @brief llog_write to a file
**
** @param file file to write to
** @param level level of log
** @param fmt format string (like printf)
** @param ... arguments
**
** @return number of bytes written
**/
int llog_write_f(const char *file, enum llog_level level, const char *fmt,
    ...);

/**
** @brief llog_write to file descriptor
**
** @param file file to write to
** @param level level of log
** @param fmt format string (like printf)
** @param ... arguments
**
** @return number of bytes written
**/
int llog_write_fd(const int fd, enum llog_level level, const char *fmt,
    ...);

#endif
