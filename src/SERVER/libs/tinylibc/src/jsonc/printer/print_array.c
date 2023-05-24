/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** print array json
*/

#include "tlcstdios.h"
#include "tlcjson.h"

int prety_print_rec(int fd, any_t *any, int indent);

int do_print_array(int fd, any_t *any, int indent)
{
    int nb = 0;
    int i = 0;

    nb += x_putcd(fd, '[', false);
    for (L_EACH(elem, any->value.array)) {
        nb += prety_print_rec(fd, L_DATA(elem), indent);
        if (i != any->value.array->len - 1) {
            nb += x_putsd(fd, ", ", false);
        }
        i++;
    }
    nb += x_putsd(fd, "]", false);
    return (nb);
}
