/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** parse string json
*/

#include <stddef.h>
#include <stdlib.h>
#include "tlcjson.h"
#include "tlcstrings.h"

bool is_tokken(const char *str, char tokken, int global_index, char escape);

static any_t *create_any_string(char *str, int *global_index, int i,
    int offset)
{
    any_t *any = NULL;

    if (str == NULL) {
        return NULL;
    }
    any = malloc(sizeof(any_t));
    if (any == NULL) {
        free(str);
        return NULL;
    }
    any->type = STR;
    any->value.str = str;
    *global_index += i + offset;
    return any;
}

any_t *parse_string(const char *str, int *global_index)
{
    char *new = NULL;
    const int offset = 1;
    int i = offset;

    if (str == NULL || *str == '\0' || *str != '"') {
        return NULL;
    }
    for (; is_tokken(str + i, '"', *global_index + i, '\\') == false; i++);
    new = calloc(i + 1, sizeof(char));
    if (new == NULL) {
        return NULL;
    }
    if (x_strncpy(new, str + offset, i - offset) == NULL) {
        free(new);
        return NULL;
    }
    return create_any_string(new, global_index, i, offset);
}
