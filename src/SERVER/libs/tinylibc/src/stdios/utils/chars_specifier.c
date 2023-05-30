/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** char.s to string
*/

#include <stddef.h>
#include <stdarg.h>
#include "tlcstrings.h"
#include "tlcutils.h"

char *c_specifier(va_list ap, UNUSED const char *rest, UNUSED int *index)
{
    char c = '\0';
    char tab[2] = {0, 0};
    char *str = NULL;

    c = va_arg(ap, int);
    tab[0] = c;
    str = x_strdup(tab);
    return (str);
}

char *s_specifier(va_list ap, UNUSED const char *rest, UNUSED int *index)
{
    char *s = NULL;
    char *str = NULL;

    s = va_arg(ap, char *);
    str = x_strdup(s);
    return (str);
}

char *mod_specifier(UNUSED va_list ap, UNUSED const char *rest,
    UNUSED int *index)
{
    char *str = NULL;

    str = x_strdup("%");
    return (str);
}
