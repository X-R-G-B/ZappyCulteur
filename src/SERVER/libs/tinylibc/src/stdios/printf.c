/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** printf
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include "tlcstdios.h"
#include "tlcutils.h"

int x_printf(const char *format, ...)
{
    va_list ap;
    char *str = NULL;
    int len = 0;

    if (format == NULL) {
        return (0);
    }
    va_start(ap, format);
    str = x_vsprintf(format, ap);
    va_end(ap);
    if (str == NULL) {
        return (0);
    }
    len = x_puts(str, false);
    free_ifnotnull(str);
    return (len);
}

int x_dprintf(int fd, const char *format, ...)
{
    va_list ap;
    char *str = NULL;
    int len = 0;

    if (format == NULL) {
        return (0);
    }
    va_start(ap, format);
    str = x_vsprintf(format, ap);
    va_end(ap);
    if (str == NULL) {
        return (0);
    }
    len = x_putsd(fd, str, false);
    free_ifnotnull(str);
    return (len);
}
