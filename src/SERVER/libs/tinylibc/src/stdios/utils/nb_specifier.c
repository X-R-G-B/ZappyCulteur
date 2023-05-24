/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** get string from number
*/

#include <stddef.h>
#include <stdarg.h>
#include "tlcstdlibs.h"
#include "tlcstrings.h"
#include "tlcutils.h"

char *i_specifier(va_list ap, UNUSED const char *rest, UNUSED int *index)
{
    int nb = 0;
    char *str = NULL;

    nb = va_arg(ap, int);
    str = x_itoa(nb);
    return (str);
}

char *x_up_specifier(va_list ap, UNUSED const char *rest, UNUSED int *index)
{
    int nb = 0;
    char *tmp = NULL;
    char *str = NULL;

    nb = va_arg(ap, int);
    tmp = itoa_base(nb, "0123456789ABCDEF");
    if (tmp == NULL) {
        return (NULL);
    }
    str = x_calloc(x_strlen(tmp) + 3);
    if (str == NULL) {
        free_ifnotnull(tmp);
        return (NULL);
    }
    x_strcpy(str, "0X");
    x_strcpy(str + 2, tmp);
    free_ifnotnull(tmp);
    return (str);
}

char *x_low_specifier(va_list ap, UNUSED const char *rest, UNUSED int *index)
{
    int nb = 0;
    char *tmp = NULL;
    char *str = NULL;

    nb = va_arg(ap, int);
    tmp = itoa_base(nb, "0123456789abcdef");
    if (tmp == NULL) {
        return (NULL);
    }
    str = x_calloc(x_strlen(tmp) + 3);
    if (str == NULL) {
        free_ifnotnull(tmp);
        return (NULL);
    }
    x_strcpy(str, "0x");
    x_strcpy(str + 2, tmp);
    free_ifnotnull(tmp);
    return (str);
}
