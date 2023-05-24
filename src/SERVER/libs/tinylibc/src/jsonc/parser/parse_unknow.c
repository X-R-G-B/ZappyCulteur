/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** parse unknow json
*/

#include <stddef.h>
#include "tlcjson.h"
#include "tlcstrings.h"

any_t *parse_dico(const char *str, int *global_index);
any_t *parse_array(const char *str, int *global_index);
any_t *parse_string(const char *str, int *global_index);
any_t *parse_number(const char *str, int *global_index);

any_t *parse_unknow(const char *str, int *global_index)
{
    if (str == NULL || *str == '\0') {
        return NULL;
    }
    for (; *str != '\0'; str++, (*global_index)++) {
        switch (*str) {
            case '{':
                return parse_dico(str, global_index);
            case '[':
                return parse_array(str, global_index);
            case '"':
                return parse_string(str, global_index);
            default:
                break;
        }
        if (x_strcontainc("-0123456789", *str) == 1) {
            return parse_number(str, global_index);
        }
    }
    return NULL;
}
