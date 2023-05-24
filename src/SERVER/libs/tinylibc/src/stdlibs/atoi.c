/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** string (int base 10) to int
*/

#include "tlcstdlibs.h"

int x_atoi(const char *x)
{
    int res = 0;

    res = atoi_base(x, "0123456789");
    return (res);
}
