/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** print number json
*/

#include <stddef.h>
#include "tlcjson.h"
#include "tlcstdios.h"

int my_putfloat(int fd, float val)
{
    int entire_parts = (int) val;
    int nb = 0;
    int float_parts = (val - entire_parts) * 1000000;

    nb += x_dprintf(fd, "%d", entire_parts);
    nb += x_putcd(fd, '.', false);
    nb += x_dprintf(fd, "%d", float_parts);
    return (nb);
}

int do_print_number(int fd, any_t *any, __attribute__((unused)) int indent)
{
    if (any == NULL || (any->type != INT && any->type != FLOAT)) {
        return (0);
    }
    if (any->type == INT) {
        return x_dprintf(fd, "%d", any->value.i);
    }
    return my_putfloat(fd, any->value.f);
}
