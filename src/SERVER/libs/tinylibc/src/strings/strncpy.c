/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** copy n char of src in dest
*/

#include <stddef.h>

char *x_strncpy(char *dest, const char *src, size_t n)
{
    if (dest == src || dest == NULL || src == NULL) {
        return (NULL);
    }
    if (n == 0) {
        return (dest);
    }
    for (size_t i = 0; src[i] != '\0' && i < n; i++) {
        dest[i] = src[i];
    }
    return (dest);
}
