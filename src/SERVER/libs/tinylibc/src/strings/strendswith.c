/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** check if str endswith str
*/

#include <stddef.h>
#include "tlcstrings.h"

int x_strendswith(const char *str, const char *needle)
{
    int len_str = 0;
    int len_needle = 0;

    if (str == NULL || needle == NULL) {
        return 0;
    }
    len_str = x_strlen(str);
    len_needle = x_strlen(needle);
    if (len_str < len_needle) {
        return 0;
    }
    if (x_strcmp(str + len_str - len_needle, needle) == 0) {
        return 1;
    }
    return 0;
}
