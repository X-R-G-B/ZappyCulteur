/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** malloc n strings and fill with 0
*/

#include <stdlib.h>

char **x_ccalloc(int n)
{
    char **new = NULL;

    new = malloc(sizeof(char *) * n);
    if (new == NULL) {
        return (NULL);
    }
    for (int i = 0; i < n; i++) {
        new[i] = NULL;
    }
    return (new);
}
