/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** int to string
*/

#include <stddef.h>
#include "tlcstdlibs.h"

char *x_itoa(int x)
{
    char *new = NULL;

    new = itoa_base(x, "0123456789");
    return (new);
}
