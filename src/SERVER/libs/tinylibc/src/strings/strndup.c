/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** duplicate n char
*/

#include <stddef.h>
#include <stdlib.h>
#include "tlcstrings.h"

char *x_strndup(const char *s, int n)
{
    int len = 0;
    char *new = NULL;

    if (s == NULL || n < 0) {
        return (NULL);
    }
    len = x_strlen(s);
    len = (n < len) ? n : len;
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL) {
        return (NULL);
    }
    new[len] = '\0';
    new = x_strncpy(new, s, len);
    return (new);
}
