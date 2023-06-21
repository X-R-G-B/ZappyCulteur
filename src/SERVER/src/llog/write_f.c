/*
** EPITECH PROJECT, 2023
** zappy log
** File description:
** write file
*/

#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include "llog.h"
#include "internal.h"

static const mode_t mode_file = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
    S_IROTH;

int llog_write_f(const char *file, enum llog_level level, const char *fmt, ...)
{
    int ret = 0;
    int fd = 0;
    va_list ap;

    fd = open(file, O_WRONLY | O_APPEND | O_CREAT, mode_file);
    if (fd < 0) {
        return -1;
    }
    va_start(ap, fmt);
    ret = llog_write_vfd(fd, level, fmt, ap);
    va_end(ap);
    close(fd);
    return ret;
}
