/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** copy src in dest
*/

#include <stddef.h>

char *x_strcpy(char *dest, const char *src)
{
    if (dest == src || dest == NULL || src == NULL) {
        return (NULL);
    }
    dest[0] = '\0';
    for (int i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
        dest[i + 1] = '\0';
    }
    return (dest);
}
