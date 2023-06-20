/*
** EPITECH PROJECT, 2023
** zappy log
** File description:
** internal vfd
*/

#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include "tlcstrings.h"
#include "tlcstdios.h"
#include "llog.h"

static const char level_values[MAX_LLOG_LEVEL][MAX_CHAR_VALUES] = {
    "FATAL",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
    "TRACE",
    "\033[31mFATAL\033[0m",
    "\033[33mERROR\033[0m",
    "\033[34mWARNING\033[0m",
    "\033[32mINFO\033[0m",
    "\033[38mDEBUG\033[0m",
    "\033[30mTRACE\033[0m"
};

static int write_format(int fd, const char *fmt, va_list ap,
    enum llog_level level)
{
    int ret;
    char *buf = NULL;
    char *final = NULL;

    buf = x_vsprintf(fmt, ap);
    if (buf == NULL) {
        return -1;
    }
    final = x_sprintf("[%s] %s\n", level_values[level], buf);
    free(buf);
    if (final == NULL) {
        return -1;
    }
    ret = write(fd, final, x_strlen(final));
    free(final);
    return ret;
}

int llog_write_vfd(const int fd, enum llog_level level,
    const char *fmt, va_list ap)
{
    int ret = 0;

    if (fmt == NULL || level >= MAX_LLOG_LEVEL || level < LLOG_FATAL) {
        return -1;
    }
    if (isatty(fd) == 1 && level < LLOG_FATAL_COLOR) {
        level = level + LLOG_FATAL_COLOR;
    }
    ret = write_format(fd, fmt, ap, level);
    return ret;
}
