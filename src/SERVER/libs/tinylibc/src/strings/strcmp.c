/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** compare two strings
*/

#include <stddef.h>
#include "tlcstrings.h"

int x_strcmp(const char *s1, const char *s2)
{
    int max_s1 = 0;
    int max_s2 = 0;
    int sub = 0;

    max_s1 = x_strlen(s1);
    max_s2 = x_strlen(s2);
    for (int i = 0; sub == 0 && (i < max_s2 || i < max_s1); i++) {
        sub = ((i < max_s1) ? s1[i] : '\0') - ((i < max_s2) ? s2[i] : '\0');
    }
    return (sub);
}
