/*
** EPITECH PROJECT, 2022
** (my) TinyLibC
** File description:
** reverse a string
*/

#include <stddef.h>
#include "tlcstrings.h"

char *x_strrev(char *str)
{
    char c = '\0';
    int len = 0;

    if (str == NULL) {
        return (NULL);
    }
    len = x_strlen(str) - 1;
    for (int i = 0; i <= len / 2; i++) {
        c = str[i];
        str[i] = str[len - i];
        str[len - i] = c;
    }
    return (str);
}
