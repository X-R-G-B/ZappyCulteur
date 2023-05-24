/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** duplicate a string
*/

#include <stddef.h>
#include <stdlib.h>
#include "tlcstrings.h"

char *x_strdup(const char *s)
{
    int len = 0;
    char *new = NULL;

    if (s == NULL) {
        return (NULL);
    }
    len = x_strlen(s);
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL) {
        return (NULL);
    }
    new = x_strcpy(new, s);
    return (new);
}
