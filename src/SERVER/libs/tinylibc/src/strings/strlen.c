/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** get length of string
*/

#include <stddef.h>
#include <stdbool.h>

size_t x_strlen(const char *s)
{
    if (s == NULL) {
        return (0);
    }
    for (int i = 0; true; i++) {
        if (s[i] == 0) {
            return (i);
        }
    }
    return (0);
}
