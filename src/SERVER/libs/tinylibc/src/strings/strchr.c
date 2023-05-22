/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** search char in str
*/

#include <stddef.h>

char *x_strchr(const char *s, int c)
{
    if (s == NULL || c == '\0') {
        return (NULL);
    }
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            return ((char *) (s + i));
        }
    }
    return (NULL);
}
