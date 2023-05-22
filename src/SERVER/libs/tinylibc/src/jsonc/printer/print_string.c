/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** print string json
*/

#include <stddef.h>
#include "tlcjson.h"
#include "tlcstdios.h"

int do_print_string(int fd, any_t *any, __attribute__((unused)) int indent)
{
    if (any == NULL || any->type != STR) {
        return 0;
    }
    return x_dprintf(fd, "\"%s\"", any->value.str);
}
