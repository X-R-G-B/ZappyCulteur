/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** string (in custom base) to int
*/

#include <stddef.h>
#include <stdbool.h>
#include "tlcstrings.h"

static const char end_char[] = "\n \v\f\t";

int atoi_base(const char *nb, const char *base)
{
    int result = 0;
    bool is_neg = false;
    char *index = NULL;
    int i = 0;

    if (nb == NULL || x_strlen(base) <= 1) {
        return (0);
    }
    is_neg = (nb[0] == '-') ? 1 : 0;
    for (i = is_neg; nb[i] != '\0' && x_strchr(end_char, nb[i]) == NULL; i++) {
        result = result * x_strlen(base);
        index = x_strchr(base, nb[i]);
        if (index == NULL) {
            return (0);
        }
        result = result - (int) (index - base);
    }
    result = (is_neg == true) ? result : result * -1;
    return (result);
}
