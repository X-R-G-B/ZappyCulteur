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
#include <time.h>
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

static const char *get_asciitime(void)
{
    time_t t = time(NULL);
    struct tm *timeinfo;
    char *buf = NULL;

    timeinfo = localtime(&t);
    buf = asctime(timeinfo);
    if (buf == NULL || x_strlen(buf) == 0) {
        return buf;
    }
    if (buf[x_strlen(buf) - 1] == '\n') {
        buf[x_strlen(buf) - 1] = '\0';
    }
    return buf;
}

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
    final = x_sprintf("%s [%s] %s\n", get_asciitime(), level_values[level],
        buf);
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
