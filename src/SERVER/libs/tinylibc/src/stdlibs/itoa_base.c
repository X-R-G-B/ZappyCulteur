/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** int to string in custom base
*/

#include <stdlib.h>
#include "tlcstdlibs.h"
#include "tlcstrings.h"

static char *dup_and_cat(char *dest, char c, int *cap)
{
    int len = x_strlen(dest);
    char *new = NULL;

    if (len + 2 >= *cap) {
        *cap = *cap + 12;
        new = x_calloc(*cap);
        if (!new)
            return (NULL);
        for (int i = 0; i < len; i++)
            new[i] = dest[i];
        free(dest);
        dest = new;
    }
    dest[len] = c;
    return (dest);
}

static void do_zero_special_case(int nb, char *result, const char *base)
{
    if (nb == 0 && result != NULL) {
        result[0] = base[0];
    }
}

char *itoa_base(int nb, char const *base)
{
    int i = 0;
    int max_cap = 12;
    int is_neg = nb < 0;
    char *result = x_calloc(max_cap);

    if (x_strlen(base) <= 1) {
        return (NULL);
    }
    nb = (nb < 0) ? nb * -1 : nb;
    do_zero_special_case(nb, result, base);
    for (; nb != 0 && base != NULL && result != NULL; i++) {
        result = dup_and_cat(result, base[nb % x_strlen(base)], &max_cap);
        nb /= x_strlen(base);
    }
    if (is_neg && result != NULL && base != NULL) {
        result[i] = '-';
    }
    return (x_strrev(result));
}
