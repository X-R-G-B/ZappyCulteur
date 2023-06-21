/*
** EPITECH PROJECT, 2023
** zappy log
** File description:
** write file descriptor
*/

#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include "tlcstrings.h"
#include "tlcstdios.h"
#include "llog.h"
#include "internal.h"

int llog_write_fd(const int fd, enum llog_level level, const char *fmt, ...)
{
    int ret = 0;
    va_list ap;

    va_start(ap, fmt);
    ret = llog_write_vfd(fd, level, fmt, ap);
    va_end(ap);
    return ret;
}
