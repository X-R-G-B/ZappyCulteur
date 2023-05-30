/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** like printf but output string in string
*/

#include <stddef.h>
#include <stdarg.h>
#include "tlcllists.h"
#include "tlcstdlibs.h"
#include "tlcstrings.h"
#include "tlcutils.h"
#include "utils/utils.h"

static const char key[][5] = {
    "%%",
    "%d",
    "%i",
    "%x",
    "%X",
    "%s",
    "%c",
    "%p",
    "",
};

static char *(*fptrs[])(va_list ap, const char *rest, int *index) = {
    mod_specifier,
    i_specifier,
    i_specifier,
    x_low_specifier,
    x_up_specifier,
    s_specifier,
    c_specifier,
    ptr_specifier
};

static char *convert_list(list_t *list)
{
    int len = 0;
    char *str = NULL;
    int index = 0;

    for (L_EACH(node, list)) {
        len += x_strlen(L_DATA(node));
    }
    str = x_calloc(len + 1);
    for (L_EACH(node, list)) {
        for (int i = 0; ((char *) L_DATA(node))[i] != '\0'; i++) {
            str[index++] = ((char *) L_DATA(node))[i];
        }
    }
    return (str);
}

static char *transform_index_to_str(va_list ap, const char *format, int *index)
{
    char tab[2] = {0, 0};
    char *str = NULL;

    for (int i = 0; key[i][0] != '\0'; i++) {
        if (x_strstr(format + *index, key[i]) == format + *index) {
            str = fptrs[i](ap, format + *index, index);
            *index += x_strlen(key[i]) - 1;
            return (str);
        }
    }
    tab[0] = format[*index];
    str = x_strdup(tab);
    return (str);
}

char *x_vsprintf(const char *format, va_list ap)
{
    list_t *list = NULL;
    char *str = NULL;

    if (format == NULL) {
        return (NULL);
    }
    list = list_create();
    if (list == NULL) {
        return (NULL);
    }
    for (int i = 0; (size_t) i < x_strlen(format); i++) {
        list_append(list, transform_index_to_str(ap, format, &i),
            free_ifnotnull, NULL);
    }
    str = convert_list(list);
    list_delete(list);
    return (str);
}

char *x_sprintf(const char *format, ...)
{
    va_list ap;
    char *str = NULL;

    if (format == NULL) {
        return (NULL);
    }
    va_start(ap, format);
    str = x_vsprintf(format, ap);
    va_end(ap);
    return (str);
}
