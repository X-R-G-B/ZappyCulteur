/*
** EPITECH PROJECT, 2022
** (my) Tiny Lib C
** File description:
** search substr in str
*/

#include <stddef.h>
#include "tlcstrings.h"

char *x_strstr(const char *s, const char *substr)
{
    int cur_substr = 0;
    int len_substr = 0;

    if (s == NULL || substr == NULL || x_strlen(substr) == 0 ||
            x_strlen(s) == 0) {
        return (NULL);
    }
    len_substr = x_strlen(substr);
    for (int i = 0; s[i] != '\0'; i++) {
        while (s[i + cur_substr] == substr[cur_substr] &&
                substr[cur_substr] != '\0' && s[i + cur_substr] != '\0') {
            cur_substr += 1;
        }
        if (cur_substr == len_substr) {
            return ((char *) s + i);
        }
        cur_substr = 0;
    }
    return (NULL);
}
