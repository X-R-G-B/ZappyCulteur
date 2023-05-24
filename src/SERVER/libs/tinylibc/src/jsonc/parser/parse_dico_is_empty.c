/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** parse dico json check empty
*/

#include <stdbool.h>
#include "tlcjson.h"
#include "tlcstrings.h"

bool parse_dico_is_empty(const char **str, int *global_index)
{
    int i = 0;
    const char *str_tmp = NULL;

    if (str == NULL || *str == NULL || **str == '\0') {
        return true;
    }
    str_tmp = *str;
    if (*str_tmp == '{') {
        str_tmp++;
        i++;
    }
    for (; *str_tmp == ' '; str_tmp++, i++);
    if (*str_tmp == '}') {
        *global_index += i;
        *str = *str + i;
        return true;
    }
    return false;
}
