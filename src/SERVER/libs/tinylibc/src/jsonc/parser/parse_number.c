/*
** EPITECH PROJECT, 2023
** (My) Tiny Lib C
** File description:
** parse number json
*/

#include "tlcjson.h"
#include "tlcstrings.h"
#include "tlcstdlibs.h"
#include <stdlib.h>

static any_t *create_any_number(double f)
{
    any_t *any = NULL;

    any = malloc(sizeof(any_t));
    if (any == NULL) {
        return NULL;
    }
    if (f == ((int) f)) {
        any->type = INT;
        any->value.i = (int) f;
    } else {
        any->type = FLOAT;
        any->value.f = (float) f;
    }
    return any;
}

any_t *parse_number(const char *str, int *global_index)
{
    int is_error = 0;
    double f = 0;

    if (str == NULL || *str == '\0' || !x_strcontainc("-0123456789", *str)) {
        return NULL;
    }
    f = x_atodf_err(str, &is_error);
    if (is_error == 1) {
        return NULL;
    }
    for (; *str != '\0' && x_strcontainc("-0123456789.", *str) == 1;
        str++, (*global_index)++);
    return create_any_number(f);
}
