/*
** EPITECH PROJECT, 2023
** zappy log
** File description:
** internal header
*/

#ifndef INTERNAL_H_
    #define INTERNAL_H_

    #include <stdarg.h>
    #include "llog.h"

int llog_write_vfd(const int fd, enum llog_level level,
    const char *fmt, va_list ap);

#endif
